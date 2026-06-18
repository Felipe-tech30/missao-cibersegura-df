#include "ameacas.h"

#include "config.h"
#include "mapa.h"

static void DesenharPhishing(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color vermelho = (Color){ 219, 65, 84, 255 };

    DrawRectangleRounded((Rectangle){ x + 5, y + 17, 58, 42 }, 0.18f, 5, (Color){ 250, 245, 231, 255 });
    DrawTriangle((Vector2){ x + 7, y + 20 }, (Vector2){ x + 62, y + 20 },
                 (Vector2){ x + 34, y + 43 }, (Color){ 221, 229, 232, 255 });
    DrawRectangleLinesEx((Rectangle){ x + 5, y + 17, 58, 42 }, 3, vermelho);
    DrawText("?", (int)x + 27, (int)y + 24, 28, vermelho);
    DrawLineEx((Vector2){ x + 58, y + 8 }, (Vector2){ x + 69, y + 24 }, 4, (Color){ 53, 72, 86, 255 });
    DrawCircleLines((int)x + 57, (int)y + 4, 8, (Color){ 53, 72, 86, 255 });
}

static void DesenharMalware(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    int i;
    Color roxo = (Color){ 132, 67, 186, 255 };

    for (i = 0; i < 3; i++)
    {
        int py = (int)y + 17 + i * 15;
        DrawLine((int)x + 8, py, (int)x - 4, py - 8, roxo);
        DrawLine((int)x + 54, py, (int)x + 66, py - 8, roxo);
    }
    DrawCircle((int)x + 31, (int)y + 33, 27, roxo);
    DrawCircle((int)x + 22, (int)y + 27, 4, (Color){ 255, 223, 76, 255 });
    DrawCircle((int)x + 40, (int)y + 27, 4, (Color){ 255, 223, 76, 255 });
    DrawText("01", (int)x + 20, (int)y + 39, 16, WHITE);
}

static void DesenharPerfilFalso(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color laranja = (Color){ 239, 128, 63, 255 };

    DrawRectangleRounded((Rectangle){ x + 4, y + 3, 57, 72 }, 0.18f, 6, (Color){ 36, 49, 69, 255 });
    DrawRectangleRounded((Rectangle){ x + 9, y + 9, 47, 59 }, 0.16f, 5, (Color){ 239, 244, 245, 255 });
    DrawCircle((int)x + 32, (int)y + 29, 11, laranja);
    DrawEllipse((int)x + 32, (int)y + 52, 18, 11, laranja);
    DrawText("!", (int)x + 49, (int)y + 1, 25, (Color){ 223, 55, 70, 255 });
}

static void DesenharRansomware(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color vermelho = (Color){ 173, 37, 69, 255 };

    DrawRectangleRounded((Rectangle){ x + 5, y + 38, 62, 57 }, 0.16f, 6, vermelho);
    DrawCircleLines((int)x + 36, (int)y + 38, 25, (Color){ 62, 36, 55, 255 });
    DrawCircleLines((int)x + 36, (int)y + 38, 19, (Color){ 62, 36, 55, 255 });
    DrawCircle((int)x + 36, (int)y + 64, 7, (Color){ 255, 205, 70, 255 });
    DrawRectangle((int)x + 33, (int)y + 67, 7, 15, (Color){ 255, 205, 70, 255 });
    DrawText("LOCK", (int)x + 13, (int)y + 85, 13, WHITE);
}

static void DesenharGolpePagamento(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color amarelo = (Color){ 247, 184, 49, 255 };

    DrawRectangleRounded((Rectangle){ x + 5, y + 3, 58, 76 }, 0.18f, 6,
                         (Color){ 35, 52, 70, 255 });
    DrawRectangle((int)x + 11, (int)y + 10, 46, 54, (Color){ 238, 244, 244, 255 });
    DrawRectangle((int)x + 16, (int)y + 15, 11, 11, BLACK);
    DrawRectangle((int)x + 41, (int)y + 15, 11, 11, BLACK);
    DrawRectangle((int)x + 16, (int)y + 40, 11, 11, BLACK);
    DrawRectangle((int)x + 31, (int)y + 30, 7, 7, BLACK);
    DrawRectangle((int)x + 43, (int)y + 40, 9, 9, BLACK);
    DrawCircle((int)x + 58, (int)y + 12, 13, (Color){ 218, 52, 74, 255 });
    DrawText("$", (int)x + 53, (int)y + 3, 22, amarelo);
    DrawText("PIX?", (int)x + 18, (int)y + 64, 14, amarelo);
}

static void DesenharViolenciaDigital(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color rosa = (Color){ 214, 65, 119, 255 };

    DrawRectangleRounded((Rectangle){ x + 4, y + 8, 72, 54 }, 0.28f, 7, rosa);
    DrawTriangle((Vector2){ x + 15, y + 57 }, (Vector2){ x + 28, y + 57 },
                 (Vector2){ x + 13, y + 73 }, rosa);
    DrawText("#!", (int)x + 15, (int)y + 18, 28, WHITE);
    DrawText("...", (int)x + 42, (int)y + 22, 22, (Color){ 69, 32, 65, 255 });
    DrawCircle((int)x + 68, (int)y + 10, 11, (Color){ 250, 195, 45, 255 });
    DrawText("!", (int)x + 65, (int)y + 1, 19, (Color){ 69, 32, 65, 255 });
}

static void DesenharInvasaoConta(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color azul = (Color){ 38, 111, 166, 255 };
    Color vermelho = (Color){ 220, 55, 77, 255 };

    DrawCircle((int)x + 35, (int)y + 22, 17, (Color){ 223, 231, 233, 255 });
    DrawCircle((int)x + 35, (int)y + 18, 7, azul);
    DrawEllipse((int)x + 35, (int)y + 33, 13, 8, azul);
    DrawRectangleRounded((Rectangle){ x + 4, y + 43, 62, 38 }, 0.18f, 6,
                         (Color){ 35, 52, 70, 255 });
    DrawText("LOGIN", (int)x + 12, (int)y + 54, 17, WHITE);
    DrawLineEx((Vector2){ x + 4, y + 7 }, (Vector2){ x + 68, y + 76 }, 6, vermelho);
    DrawCircle((int)x + 62, (int)y + 12, 12, vermelho);
    DrawText("X", (int)x + 56, (int)y + 3, 20, WHITE);
}

const char *AmeacaNome(TipoAmeaca tipo)
{
    switch (tipo)
    {
        case AMEACA_PHISHING: return "Phishing";
        case AMEACA_MALWARE: return "Malware";
        case AMEACA_PERFIL_FALSO: return "Perfil falso";
        case AMEACA_RANSOMWARE: return "Ransomware";
        case AMEACA_GOLPE_PAGAMENTO: return "Golpe de pagamento";
        case AMEACA_VIOLENCIA_DIGITAL: return "Violencia digital";
        case AMEACA_INVASAO_CONTA: return "Invasao de conta";
        default: return "Ameaca desconhecida";
    }
}

Rectangle AmeacaPegarHitbox(Ameaca ameaca)
{
    return (Rectangle){ ameaca.posicao.x, ameaca.posicao.y,
                        ameaca.tamanho.x, ameaca.tamanho.y };
}

void AmeacasReiniciar(Ameaca ameacas[])
{
    ameacas[0] = (Ameaca){ AMEACA_PHISHING, { 620, CHAO_Y - 65 }, { 70, 65 }, 1.05f, 0, false, true, 8 };
    ameacas[1] = (Ameaca){ AMEACA_MALWARE, { 940, CHAO_Y - 62 }, { 68, 62 }, 1.30f, 0, false, true, 10 };
    ameacas[2] = (Ameaca){ AMEACA_GOLPE_PAGAMENTO, { 1260, CHAO_Y - 82 }, { 70, 82 }, 1.10f, 0, false, true, 12 };
    ameacas[3] = (Ameaca){ AMEACA_PERFIL_FALSO, { 1580, CHAO_Y - 78 }, { 66, 78 }, 1.10f, 0, false, true, 12 };
    ameacas[4] = (Ameaca){ AMEACA_VIOLENCIA_DIGITAL, { 1900, CHAO_Y - 76 }, { 80, 76 }, 1.20f, 0, false, true, 10 };
    ameacas[5] = (Ameaca){ AMEACA_RANSOMWARE, { 2220, CHAO_Y - 98 }, { 74, 98 }, 1.40f, 0, false, true, 20 };
    ameacas[6] = (Ameaca){ AMEACA_INVASAO_CONTA, { 2570, CHAO_Y - 84 }, { 72, 84 }, 1.35f, 0, false, true, 16 };
    ameacas[7] = (Ameaca){ AMEACA_PHISHING, { 2920, CHAO_Y - 65 }, { 70, 65 }, 1.05f, 0, false, true, 8 };
    ameacas[8] = (Ameaca){ AMEACA_MALWARE, { 3270, CHAO_Y - 62 }, { 68, 62 }, 1.30f, 0, false, true, 10 };
    ameacas[9] = (Ameaca){ AMEACA_GOLPE_PAGAMENTO, { 3620, CHAO_Y - 82 }, { 70, 82 }, 1.10f, 0, false, true, 12 };
    ameacas[10] = (Ameaca){ AMEACA_VIOLENCIA_DIGITAL, { 3970, CHAO_Y - 76 }, { 80, 76 }, 1.20f, 0, false, true, 10 };
    ameacas[11] = (Ameaca){ AMEACA_INVASAO_CONTA, { 4320, CHAO_Y - 84 }, { 72, 84 }, 1.35f, 0, false, true, 16 };
}

void AmeacasAtualizar(Ameaca ameacas[], Rectangle jogador)
{
    int i;

    for (i = 0; i < TOTAL_AMEACAS; i++)
    {
        float centroAmeaca;
        float centroJogador;
        float distancia;
        float distanciaAbsoluta;
        float dx = 0;
        Rectangle area;

        if (!ameacas[i].ativa) continue;

        centroAmeaca = ameacas[i].posicao.x + ameacas[i].tamanho.x / 2;
        centroJogador = jogador.x + jogador.width / 2;
        distancia = centroJogador - centroAmeaca;
        distanciaAbsoluta = distancia < 0 ? -distancia : distancia;

        if (distanciaAbsoluta < 620)
            dx = distancia > 0 ? ameacas[i].velocidade : -ameacas[i].velocidade;

        area = AmeacaPegarHitbox(ameacas[i]);
        MapaMoverComFisica(&area, dx, &ameacas[i].velocidadeY, &ameacas[i].noChao);
        ameacas[i].posicao.x = area.x;
        ameacas[i].posicao.y = area.y;
    }
}

void AmeacasDesenhar(const Ameaca ameacas[])
{
    int i;

    for (i = 0; i < TOTAL_AMEACAS; i++)
    {
        if (!ameacas[i].ativa) continue;

        DrawText(AmeacaNome(ameacas[i].tipo), (int)ameacas[i].posicao.x,
                 (int)ameacas[i].posicao.y - 21, 16, (Color){ 118, 20, 47, 255 });

        switch (ameacas[i].tipo)
        {
            case AMEACA_PHISHING: DesenharPhishing(ameacas[i]); break;
            case AMEACA_MALWARE: DesenharMalware(ameacas[i]); break;
            case AMEACA_PERFIL_FALSO: DesenharPerfilFalso(ameacas[i]); break;
            case AMEACA_RANSOMWARE: DesenharRansomware(ameacas[i]); break;
            case AMEACA_GOLPE_PAGAMENTO: DesenharGolpePagamento(ameacas[i]); break;
            case AMEACA_VIOLENCIA_DIGITAL: DesenharViolenciaDigital(ameacas[i]); break;
            case AMEACA_INVASAO_CONTA: DesenharInvasaoConta(ameacas[i]); break;
        }
    }
}
