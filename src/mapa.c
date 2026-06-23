#include "mapa.h"

#include "config.h"
#include "tipos.h"

static int tiles[MAPA_LINHAS][MAPA_COLUNAS];

static bool TileSolido(int tile)
{
    return tile == TILE_GRAMA || tile == TILE_TERRA ||
           tile == TILE_CONCRETO || tile == TILE_DADO_CORROMPIDO;
}

void MapaInicializar(void)
{
    int x;
    int y;

    for (y = 0; y < MAPA_LINHAS; y++)
    {
        for (x = 0; x < MAPA_COLUNAS; x++)
        {
            if (y < LINHA_CHAO) tiles[y][x] = TILE_AR;
            else if (y == LINHA_CHAO) tiles[y][x] = TILE_GRAMA;
            else if (y < LINHA_CHAO + 4) tiles[y][x] = TILE_TERRA;
            else tiles[y][x] = TILE_CONCRETO;
        }
    }

    /* Trechos corrompidos representam links e arquivos perigosos. */
    for (x = 22; x <= 27; x++) tiles[LINHA_CHAO][x] = TILE_DADO_CORROMPIDO;
    for (x = 62; x <= 68; x++) tiles[LINHA_CHAO][x] = TILE_DADO_CORROMPIDO;
    for (x = 104; x <= 110; x++) tiles[LINHA_CHAO][x] = TILE_DADO_CORROMPIDO;
    for (x = 146; x <= 152; x++) tiles[LINHA_CHAO][x] = TILE_DADO_CORROMPIDO;
    for (x = 188; x <= 194; x++) tiles[LINHA_CHAO][x] = TILE_DADO_CORROMPIDO;

    /* Plataformas e passarelas aumentam a exploracao sem bloquear o caminho principal. */
    for (x = 42; x <= 50; x++) tiles[LINHA_CHAO - 3][x] = TILE_CONCRETO;
    for (x = 75; x <= 84; x++) tiles[LINHA_CHAO - 4][x] = TILE_CONCRETO;
    for (x = 118; x <= 128; x++) tiles[LINHA_CHAO - 3][x] = TILE_CONCRETO;
    for (x = 158; x <= 168; x++) tiles[LINHA_CHAO - 5][x] = TILE_CONCRETO;
    for (x = 198; x <= 206; x++) tiles[LINHA_CHAO - 4][x] = TILE_CONCRETO;

    /* Galerias subterraneas apenas decorativas. */
    for (y = LINHA_CHAO + 2; y < LINHA_CHAO + 6; y++)
    {
        for (x = 35; x < 45; x++) tiles[y][x] = TILE_AR;
        for (x = 82; x < 93; x++) tiles[y][x] = TILE_AR;
        for (x = 130; x < 142; x++) tiles[y][x] = TILE_AR;
        for (x = 174; x < 186; x++) tiles[y][x] = TILE_AR;
    }
}

bool MapaColide(Rectangle area)
{
    int inicioX = (int)(area.x / TAMANHO_TILE);
    int fimX = (int)((area.x + area.width - 1) / TAMANHO_TILE);
    int inicioY = (int)(area.y / TAMANHO_TILE);
    int fimY = (int)((area.y + area.height - 1) / TAMANHO_TILE);
    int x;
    int y;

    if (inicioX < 0) inicioX = 0;
    if (fimX >= MAPA_COLUNAS) fimX = MAPA_COLUNAS - 1;
    if (inicioY < 0) inicioY = 0;
    if (fimY >= MAPA_LINHAS) fimY = MAPA_LINHAS - 1;

    for (y = inicioY; y <= fimY; y++)
    {
        for (x = inicioX; x <= fimX; x++)
        {
            if (TileSolido(tiles[y][x])) return true;
        }
    }

    return false;
}

bool MapaEncostaDadoCorrompido(Rectangle area)
{
    Rectangle pes = { area.x + 5, area.y + area.height,
                      area.width - 10, 6 };
    int inicioX = (int)(pes.x / TAMANHO_TILE);
    int fimX = (int)((pes.x + pes.width - 1) / TAMANHO_TILE);
    int tileY = (int)(pes.y / TAMANHO_TILE);
    int x;

    if (tileY < 0 || tileY >= MAPA_LINHAS) return false;
    if (inicioX < 0) inicioX = 0;
    if (fimX >= MAPA_COLUNAS) fimX = MAPA_COLUNAS - 1;

    for (x = inicioX; x <= fimX; x++)
    {
        if (tiles[tileY][x] == TILE_DADO_CORROMPIDO) return true;
    }

    return false;
}

void MapaMoverComFisica(Rectangle *area, float deslocamentoX,
                        float *velocidadeY, bool *noChao)
{
    area->x += deslocamentoX;

    if (MapaColide(*area))
    {
        if (deslocamentoX > 0)
        {
            while (MapaColide(*area)) area->x -= 1;
        }
        else if (deslocamentoX < 0)
        {
            while (MapaColide(*area)) area->x += 1;
        }
    }

    *velocidadeY += 0.55f;
    if (*velocidadeY > 14.0f) *velocidadeY = 14.0f;

    area->y += *velocidadeY;
    *noChao = false;

    if (MapaColide(*area))
    {
        if (*velocidadeY > 0)
        {
            while (MapaColide(*area)) area->y -= 1;
            *noChao = true;
        }
        else if (*velocidadeY < 0)
        {
            while (MapaColide(*area)) area->y += 1;
        }

        *velocidadeY = 0;
    }

    if (area->x < 0) area->x = 0;
    if (area->x + area->width > LARGURA_MUNDO)
        area->x = LARGURA_MUNDO - area->width;

    if (area->y > ALTURA_MUNDO)
    {
        area->y = CHAO_Y - area->height;
        *velocidadeY = 0;
        *noChao = true;
    }
}

static void DesenharTilemap(Camera2D camera)
{
    int inicioX = (int)((camera.target.x - camera.offset.x) / TAMANHO_TILE) - 2;
    int fimX = (int)((camera.target.x + camera.offset.x) / TAMANHO_TILE) + 3;
    int x;
    int y;

    if (inicioX < 0) inicioX = 0;
    if (fimX >= MAPA_COLUNAS) fimX = MAPA_COLUNAS - 1;

    for (y = 0; y < MAPA_LINHAS; y++)
    {
        for (x = inicioX; x <= fimX; x++)
        {
            int tile = tiles[y][x];
            Rectangle r = { (float)(x * TAMANHO_TILE), (float)(y * TAMANHO_TILE),
                            TAMANHO_TILE, TAMANHO_TILE };

            if (tile == TILE_AR) continue;

            if (tile == TILE_GRAMA)
            {
                DrawRectangleRec(r, (Color){ 66, 156, 86, 255 });
                DrawRectangle((int)r.x, (int)r.y + 9, TAMANHO_TILE,
                              TAMANHO_TILE - 9, (Color){ 138, 91, 58, 255 });
                DrawRectangleLinesEx(r, 1, (Color){ 37, 96, 57, 255 });
            }
            else if (tile == TILE_TERRA)
            {
                DrawRectangleRec(r, (Color){ 138, 91, 58, 255 });
                DrawCircle((int)r.x + 12, (int)r.y + 14, 3, (Color){ 105, 67, 45, 255 });
                DrawRectangleLinesEx(r, 1, (Color){ 93, 57, 39, 255 });
            }
            else if (tile == TILE_CONCRETO)
            {
                DrawRectangleRec(r, (Color){ 83, 94, 108, 255 });
                DrawLine((int)r.x + 7, (int)r.y + 12, (int)r.x + 22,
                         (int)r.y + 7, (Color){ 116, 128, 140, 255 });
                DrawRectangleLinesEx(r, 1, (Color){ 51, 59, 69, 255 });
            }
            else
            {
                Color pulso = ((x + y) % 2 == 0) ?
                    (Color){ 215, 44, 78, 255 } : (Color){ 151, 28, 73, 255 };
                DrawRectangleRec(r, pulso);
                DrawText("101", (int)r.x + 5, (int)r.y + 11, 17, (Color){ 255, 213, 66, 255 });
                DrawRectangleLinesEx(r, 2, (Color){ 255, 107, 102, 255 });
            }
        }
    }
}

static void DesenharPredio(int x, int largura, int altura, Color cor)
{
    int y = CHAO_Y - altura;
    int janelaX;
    int janelaY;

    DrawRectangle(x, y, largura, altura, cor);
    DrawRectangleLines(x, y, largura, altura, (Color){ 46, 68, 84, 255 });

    for (janelaY = y + 16; janelaY < CHAO_Y - 16; janelaY += 26)
    {
        for (janelaX = x + 14; janelaX < x + largura - 12; janelaX += 30)
            DrawRectangle(janelaX, janelaY, 12, 9, (Color){ 255, 221, 92, 255 });
    }
}

static void DesenharNuvem(int x, int y, float escala)
{
    Color sombra = (Color){ 192, 224, 237, 255 };
    Color luz = (Color){ 245, 252, 255, 255 };

    DrawEllipse(x + (int)(32 * escala), y + (int)(20 * escala),
                36 * escala, 17 * escala, sombra);
    DrawCircle(x + (int)(18 * escala), y + (int)(18 * escala),
               17 * escala, luz);
    DrawCircle(x + (int)(39 * escala), y + (int)(10 * escala),
               22 * escala, luz);
    DrawCircle(x + (int)(64 * escala), y + (int)(19 * escala),
               18 * escala, luz);
    DrawEllipse(x + (int)(44 * escala), y + (int)(28 * escala),
                42 * escala, 12 * escala, luz);
}

static void DesenharPlacaSetor(int x, const char *titulo, const char *subtitulo)
{
    int y = CHAO_Y - 128;
    int largura = 250;
    int larguraTitulo = MeasureText(titulo, 18);
    int larguraSubtitulo = MeasureText(subtitulo, 14);

    DrawRectangle(x + 116, y + 66, 12, 66, (Color){ 72, 84, 97, 255 });
    DrawRectangleRounded((Rectangle){ x, y, largura, 66 }, 0.18f, 6,
                         (Color){ 20, 63, 105, 245 });
    DrawRectangleRoundedLinesEx((Rectangle){ x, y, largura, 66 }, 0.18f, 6, 2,
                                (Color){ 55, 229, 193, 255 });
    DrawText(titulo, x + largura / 2 - larguraTitulo / 2, y + 12, 18,
             (Color){ 255, 244, 208, 255 });
    DrawText(subtitulo, x + largura / 2 - larguraSubtitulo / 2, y + 38, 14,
             (Color){ 205, 230, 238, 255 });
}

static void DesenharCongresso(int x)
{
    int baseY = CHAO_Y;

    DrawRectangle(x + 115, baseY - 242, 42, 242, (Color){ 233, 240, 241, 255 });
    DrawRectangle(x + 182, baseY - 208, 42, 208, (Color){ 233, 240, 241, 255 });
    DrawRectangleLines(x + 115, baseY - 242, 42, 242, (Color){ 174, 193, 199, 255 });
    DrawRectangleLines(x + 182, baseY - 208, 42, 208, (Color){ 174, 193, 199, 255 });
    DrawEllipse(x + 74, baseY - 22, 92, 29, (Color){ 244, 247, 247, 255 });
    DrawEllipse(x + 276, baseY - 36, 92, 35, (Color){ 244, 247, 247, 255 });
    DrawRectangleRounded((Rectangle){ x + 20, baseY - 31, 330, 31 }, 0.12f, 6,
                         (Color){ 210, 224, 228, 255 });
    DrawText("CONGRESSO NACIONAL", x + 70, baseY - 72, 19,
             (Color){ 44, 77, 96, 255 });
}

static void DesenharCatedral(int x)
{
    int baseY = CHAO_Y;
    int i;

    DrawEllipse(x + 96, baseY - 5, 110, 22, (Color){ 210, 224, 228, 255 });
    for (i = 0; i < 8; i++)
    {
        int baseX = x + 25 + i * 20;
        DrawLineEx((Vector2){ baseX, baseY - 6 },
                   (Vector2){ x + 96, baseY - 192 }, 5,
                   (Color){ 236, 242, 244, 255 });
    }
    DrawCircle(x + 96, baseY - 111, 38, Fade((Color){ 126, 199, 226, 255 }, 0.40f));
    DrawText("CATEDRAL", x + 54, baseY - 61, 18, (Color){ 44, 77, 96, 255 });
}

static void DesenharPonteJK(int x)
{
    int baseY = CHAO_Y - 35;
    int i;

    DrawRectangle(x - 40, CHAO_Y - 34, 540, 34, Fade((Color){ 73, 168, 205, 255 }, 0.82f));
    for (i = 0; i < 3; i++)
    {
        int arcoX = x + i * 145;
        DrawCircleLines(arcoX + 80, baseY, 76, (Color){ 236, 242, 244, 255 });
        DrawLineEx((Vector2){ arcoX + 16, baseY + 44 },
                   (Vector2){ arcoX + 144, baseY + 44 }, 5,
                   (Color){ 236, 242, 244, 255 });
    }
    DrawRectangle(x - 18, baseY + 38, 476, 9, (Color){ 236, 242, 244, 255 });
    DrawText("PONTE JK / LAGO PARANOA", x + 96, baseY - 33, 18,
             (Color){ 44, 77, 96, 255 });
}

static void DesenharIpe(int x, Color flores)
{
    DrawRectangle(x, CHAO_Y - 82, 18, 82, (Color){ 105, 74, 50, 255 });
    DrawCircle(x + 9, CHAO_Y - 102, 38, flores);
    DrawCircle(x - 16, CHAO_Y - 83, 25, flores);
    DrawCircle(x + 34, CHAO_Y - 83, 25, flores);
    DrawCircle(x + 12, CHAO_Y - 116, 20, Fade(WHITE, 0.20f));
}

void MapaDesenharFundo(Camera2D camera)
{
    int i;
    (void)camera;

    ClearBackground((Color){ 112, 202, 239, 255 });
    DrawRectangleGradientV(0, 0, LARGURA_MUNDO, CHAO_Y,
                           (Color){ 94, 188, 232, 255 },
                           (Color){ 184, 232, 240, 255 });
    DrawCircle(7000, 88, 58, (Color){ 255, 222, 87, 255 });
    DrawCircleLines(7000, 88, 72, Fade((Color){ 255, 244, 179, 255 }, 0.78f));

    for (i = 0; i < 70; i++)
    {
        int x = (i * 241) % LARGURA_MUNDO;
        int y = 42 + ((i * 53) % 138);
        DrawCircle(x, y, 2 + (i % 3), Fade(WHITE, 0.48f));
    }

    DesenharNuvem(250, 78, 0.90f);
    DesenharNuvem(940, 44, 1.12f);
    DesenharNuvem(1680, 94, 0.78f);
    DesenharNuvem(2580, 54, 1.02f);
    DesenharNuvem(3700, 96, 0.86f);
    DesenharNuvem(4850, 52, 1.05f);
    DesenharNuvem(6020, 86, 0.92f);
    DesenharNuvem(7450, 48, 1.10f);

    /* Horizonte de Brasilia em formas simples e cartunescas. */
    DrawRectangle(0, CHAO_Y - 100, LARGURA_MUNDO, 100, (Color){ 92, 157, 156, 255 });
    DrawRectangle(0, CHAO_Y - 34, LARGURA_MUNDO, 34, Fade((Color){ 68, 143, 111, 255 }, 0.55f));
    DrawRectangle(5750, CHAO_Y - 55, 1250, 55, Fade((Color){ 73, 168, 205, 255 }, 0.68f));

    DesenharPredio(500, 155, 180, (Color){ 118, 160, 181, 255 });
    DesenharPredio(1800, 170, 150, (Color){ 132, 168, 188, 255 });
    DesenharPredio(3050, 150, 190, (Color){ 112, 154, 176, 255 });
    DesenharPredio(4250, 170, 145, (Color){ 135, 173, 191, 255 });
    DesenharPredio(7220, 185, 170, (Color){ 128, 164, 184, 255 });

    /* Congresso Nacional estilizado. */
    DesenharCongresso(2185);

    /* Torre de TV estilizada. */
    DrawTriangle((Vector2){ 3600, CHAO_Y }, (Vector2){ 3650, CHAO_Y - 270 },
                 (Vector2){ 3700, CHAO_Y }, (Color){ 217, 224, 227, 255 });
    DrawRectangle(3608, CHAO_Y - 170, 84, 18, (Color){ 69, 91, 107, 255 });

    /* Base da missao, escola e setor bancario. */
    DrawRectangle(90, CHAO_Y - 150, 270, 150, (Color){ 34, 90, 137, 255 });
    DrawRectangle(114, CHAO_Y - 116, 222, 116, (Color){ 233, 239, 240, 255 });
    DrawRectangleRounded((Rectangle){ 142, CHAO_Y - 137, 166, 34 }, 0.24f, 6,
                         (Color){ 20, 63, 105, 255 });
    DrawText("PCDF", 179, CHAO_Y - 96, 33, (Color){ 20, 63, 105, 255 });
    DrawText("BASE CIBER", 142, CHAO_Y - 57, 22, (Color){ 30, 46, 61, 255 });

    DrawRectangle(1120, CHAO_Y - 122, 290, 122, (Color){ 244, 198, 72, 255 });
    DrawRectangle(1152, CHAO_Y - 92, 226, 92, (Color){ 245, 236, 205, 255 });
    DrawText("ESCOLA DO DF", 1195, CHAO_Y - 70, 24, (Color){ 48, 67, 83, 255 });

    DrawRectangle(2760, CHAO_Y - 136, 280, 136, (Color){ 62, 120, 164, 255 });
    DrawRectangle(2794, CHAO_Y - 101, 212, 101, (Color){ 232, 241, 244, 255 });
    DrawText("SETOR BANCARIO", 2788, CHAO_Y - 80, 23, (Color){ 30, 64, 93, 255 });

    DesenharCatedral(4860);
    DesenharPonteJK(6100);

    DrawText("EIXO DA CIDADANIA DIGITAL", 7390, CHAO_Y - 60, 21,
             (Color){ 35, 65, 82, 255 });

    DesenharPlacaSetor(430, "FASE 1", "Base PCDF e escola");
    DesenharPlacaSetor(1910, "FASE 2", "Golpes financeiros");
    DesenharPlacaSetor(3610, "FASE 3", "Esplanada digital");
    DesenharPlacaSetor(5530, "FASE 4", "Lago e redes abertas");
    DesenharPlacaSetor(7460, "FASE 5", "Operacao final");

    /* Ipês e postes conectados lembram a paisagem do DF. */
    for (i = 380; i < LARGURA_MUNDO; i += 430)
    {
        Color flores = (i / 430) % 2 == 0 ?
            (Color){ 241, 188, 48, 255 } : (Color){ 193, 110, 202, 255 };
        DesenharIpe(i, flores);
    }

    DesenharTilemap(camera);
}

void MapaDesenharFundoMenu(void)
{
    Camera2D camera = { 0 };
    camera.target = (Vector2){ LARGURA_TELA / 2.0f, ALTURA_TELA / 2.0f };
    camera.offset = (Vector2){ LARGURA_TELA / 2.0f, ALTURA_TELA / 2.0f };
    camera.zoom = 1.0f;
    MapaDesenharFundo(camera);
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade((Color){ 5, 20, 42, 255 }, 0.58f));
}
