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

    /* Galerias subterraneas apenas decorativas. */
    for (y = LINHA_CHAO + 2; y < LINHA_CHAO + 6; y++)
    {
        for (x = 35; x < 45; x++) tiles[y][x] = TILE_AR;
        for (x = 82; x < 93; x++) tiles[y][x] = TILE_AR;
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

void MapaDesenharFundo(Camera2D camera)
{
    int i;
    (void)camera;

    ClearBackground((Color){ 102, 190, 232, 255 });
    DrawCircle(3900, 90, 46, (Color){ 255, 222, 87, 255 });

    for (i = 0; i < 45; i++)
    {
        int x = (i * 181) % LARGURA_MUNDO;
        int y = 45 + ((i * 47) % 135);
        DrawCircle(x, y, 3, Fade(WHITE, 0.75f));
    }

    /* Horizonte de Brasilia em formas simples e cartunescas. */
    DrawRectangle(0, CHAO_Y - 90, LARGURA_MUNDO, 90, (Color){ 84, 145, 151, 255 });

    DesenharPredio(500, 155, 180, (Color){ 118, 160, 181, 255 });
    DesenharPredio(1800, 170, 150, (Color){ 132, 168, 188, 255 });
    DesenharPredio(3050, 150, 190, (Color){ 112, 154, 176, 255 });
    DesenharPredio(4250, 170, 145, (Color){ 135, 173, 191, 255 });

    /* Congresso Nacional estilizado. */
    DrawRectangle(2230, CHAO_Y - 225, 38, 225, (Color){ 225, 235, 237, 255 });
    DrawRectangle(2282, CHAO_Y - 195, 38, 195, (Color){ 225, 235, 237, 255 });
    DrawEllipse(2190, CHAO_Y - 18, 82, 27, (Color){ 238, 244, 244, 255 });
    DrawEllipse(2355, CHAO_Y - 28, 82, 32, (Color){ 238, 244, 244, 255 });
    DrawRectangle(2140, CHAO_Y - 22, 300, 22, (Color){ 210, 224, 228, 255 });

    /* Torre de TV estilizada. */
    DrawTriangle((Vector2){ 3600, CHAO_Y }, (Vector2){ 3650, CHAO_Y - 270 },
                 (Vector2){ 3700, CHAO_Y }, (Color){ 217, 224, 227, 255 });
    DrawRectangle(3608, CHAO_Y - 170, 84, 18, (Color){ 69, 91, 107, 255 });

    /* Base da missao, escola e setor bancario. */
    DrawRectangle(90, CHAO_Y - 145, 250, 145, (Color){ 34, 90, 137, 255 });
    DrawRectangle(112, CHAO_Y - 112, 206, 112, (Color){ 233, 239, 240, 255 });
    DrawText("PCDF", 176, CHAO_Y - 99, 31, (Color){ 20, 63, 105, 255 });
    DrawText("BASE CIBER", 137, CHAO_Y - 60, 22, (Color){ 30, 46, 61, 255 });

    DrawRectangle(1120, CHAO_Y - 115, 270, 115, (Color){ 244, 198, 72, 255 });
    DrawText("ESCOLA DO DF", 1170, CHAO_Y - 72, 24, (Color){ 48, 67, 83, 255 });

    DrawRectangle(2760, CHAO_Y - 130, 270, 130, (Color){ 62, 120, 164, 255 });
    DrawText("SETOR BANCARIO", 2790, CHAO_Y - 78, 23, WHITE);

    DrawText("EIXO DA CIDADANIA DIGITAL", 3900, CHAO_Y - 60, 21,
             (Color){ 35, 65, 82, 255 });

    /* Ipês e postes conectados lembram a paisagem do DF. */
    for (i = 380; i < LARGURA_MUNDO; i += 520)
    {
        Color flores = (i / 520) % 2 == 0 ?
            (Color){ 241, 188, 48, 255 } : (Color){ 193, 110, 202, 255 };
        DrawRectangle(i, CHAO_Y - 82, 18, 82, (Color){ 105, 74, 50, 255 });
        DrawCircle(i + 9, CHAO_Y - 102, 38, flores);
        DrawCircle(i - 16, CHAO_Y - 83, 25, flores);
        DrawCircle(i + 34, CHAO_Y - 83, 25, flores);
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
