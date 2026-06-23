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

static void DesenharVazamentoDados(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color ciano = (Color){ 36, 198, 198, 255 };
    Color azul = (Color){ 30, 78, 124, 255 };

    DrawEllipse((int)x + 38, (int)y + 18, 31, 13, ciano);
    DrawRectangleRounded((Rectangle){ x + 7, y + 18, 62, 47 }, 0.16f, 6, azul);
    DrawEllipse((int)x + 38, (int)y + 65, 31, 13, (Color){ 24, 58, 95, 255 });
    DrawEllipseLines((int)x + 38, (int)y + 18, 31, 13, WHITE);
    DrawText("CPF", (int)x + 21, (int)y + 32, 18, WHITE);
    DrawCircle((int)x + 63, (int)y + 62, 8, (Color){ 250, 195, 45, 255 });
    DrawText("!", (int)x + 60, (int)y + 54, 17, (Color){ 76, 45, 18, 255 });
}

static void DesenharEngenhariaSocial(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color roxo = (Color){ 116, 72, 190, 255 };

    DrawRectangleRounded((Rectangle){ x + 5, y + 10, 72, 47 }, 0.28f, 7, roxo);
    DrawTriangle((Vector2){ x + 21, y + 52 }, (Vector2){ x + 36, y + 52 },
                 (Vector2){ x + 18, y + 72 }, roxo);
    DrawCircle((int)x + 26, (int)y + 31, 10, (Color){ 246, 215, 177, 255 });
    DrawCircle((int)x + 55, (int)y + 31, 10, (Color){ 246, 215, 177, 255 });
    DrawText("?", (int)x + 35, (int)y + 20, 26, WHITE);
    DrawLine((int)x + 38, (int)y + 44, (int)x + 48, (int)y + 44, WHITE);
}

static void DesenharWifiFalso(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color azul = (Color){ 38, 111, 166, 255 };
    Color vermelho = (Color){ 220, 55, 77, 255 };

    DrawRectangleRounded((Rectangle){ x + 6, y + 52, 72, 30 }, 0.18f, 6,
                         (Color){ 35, 52, 70, 255 });
    DrawText("FREE", (int)x + 20, (int)y + 58, 17, WHITE);
    DrawCircleLines((int)x + 42, (int)y + 51, 12, azul);
    DrawCircleLines((int)x + 42, (int)y + 51, 25, azul);
    DrawCircleLines((int)x + 42, (int)y + 51, 38, azul);
    DrawCircle((int)x + 42, (int)y + 51, 5, azul);
    DrawLineEx((Vector2){ x + 11, y + 14 }, (Vector2){ x + 74, y + 78 }, 6, vermelho);
}

static void DesenharLojaFalsa(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color laranja = (Color){ 239, 128, 63, 255 };

    DrawRectangleRounded((Rectangle){ x + 8, y + 28, 70, 53 }, 0.14f, 5,
                         (Color){ 245, 239, 220, 255 });
    DrawRectangle((int)x + 8, (int)y + 28, 70, 12, laranja);
    DrawTriangle((Vector2){ x + 8, y + 28 }, (Vector2){ x + 43, y + 4 },
                 (Vector2){ x + 78, y + 28 }, (Color){ 220, 72, 83, 255 });
    DrawRectangle((int)x + 18, (int)y + 52, 17, 29, (Color){ 55, 78, 98, 255 });
    DrawRectangle((int)x + 48, (int)y + 50, 19, 13, (Color){ 105, 188, 215, 255 });
    DrawCircle((int)x + 68, (int)y + 20, 13, (Color){ 250, 195, 45, 255 });
    DrawText("50%", (int)x + 53, (int)y + 13, 13, (Color){ 76, 45, 18, 255 });
}

static void DesenharDeepfake(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color azul = (Color){ 41, 130, 190, 255 };
    Color rosa = (Color){ 216, 76, 146, 255 };

    DrawCircle((int)x + 40, (int)y + 35, 30, (Color){ 241, 214, 174, 255 });
    DrawRectangle((int)x + 40, (int)y + 5, 31, 61, Fade(rosa, 0.85f));
    DrawLine((int)x + 40, (int)y + 7, (int)x + 40, (int)y + 66, (Color){ 52, 68, 83, 255 });
    DrawCircle((int)x + 29, (int)y + 29, 4, (Color){ 35, 35, 40, 255 });
    DrawCircle((int)x + 52, (int)y + 29, 4, WHITE);
    DrawRectangleRounded((Rectangle){ x + 15, y + 67, 51, 18 }, 0.24f, 5, azul);
    DrawText("IA?", (int)x + 27, (int)y + 67, 17, WHITE);
    DrawCircleLines((int)x + 68, (int)y + 12, 11, azul);
}

static void DesenharDoxxing(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color vermelho = (Color){ 220, 55, 77, 255 };

    DrawRectangleRounded((Rectangle){ x + 10, y + 7, 57, 72 }, 0.12f, 5,
                         (Color){ 245, 247, 239, 255 });
    DrawRectangle((int)x + 18, (int)y + 20, 37, 4, (Color){ 71, 88, 105, 255 });
    DrawRectangle((int)x + 18, (int)y + 32, 30, 4, (Color){ 71, 88, 105, 255 });
    DrawRectangle((int)x + 18, (int)y + 44, 35, 4, (Color){ 71, 88, 105, 255 });
    DrawCircle((int)x + 58, (int)y + 62, 16, vermelho);
    DrawCircle((int)x + 58, (int)y + 58, 6, WHITE);
    DrawTriangle((Vector2){ x + 49, y + 69 }, (Vector2){ x + 67, y + 69 },
                 (Vector2){ x + 58, y + 86 }, vermelho);
    DrawText("DOC", (int)x + 18, (int)y + 56, 16, vermelho);
}

static void DesenharSuporteFalso(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color verde = (Color){ 65, 171, 111, 255 };
    Color escuro = (Color){ 35, 52, 70, 255 };

    DrawRectangleRounded((Rectangle){ x + 7, y + 20, 70, 47 }, 0.12f, 5, escuro);
    DrawRectangle((int)x + 14, (int)y + 28, 56, 26, (Color){ 231, 244, 238, 255 });
    DrawText("SUP?", (int)x + 21, (int)y + 32, 18, verde);
    DrawRectangle((int)x + 33, (int)y + 67, 19, 7, escuro);
    DrawCircleLines((int)x + 42, (int)y + 15, 18, verde);
    DrawRectangle((int)x + 22, (int)y + 15, 7, 17, verde);
    DrawRectangle((int)x + 55, (int)y + 15, 7, 17, verde);
    DrawLine((int)x + 57, (int)y + 32, (int)x + 69, (int)y + 41, verde);
}

static void DesenharAliciamentoOnline(Ameaca ameaca)
{
    float x = ameaca.posicao.x;
    float y = ameaca.posicao.y;
    Color vermelho = (Color){ 220, 55, 77, 255 };
    Color ciano = (Color){ 55, 229, 193, 255 };

    DrawRectangleRounded((Rectangle){ x + 6, y + 8, 74, 52 }, 0.28f, 7,
                         (Color){ 40, 62, 86, 255 });
    DrawTriangle((Vector2){ x + 18, y + 55 }, (Vector2){ x + 32, y + 55 },
                 (Vector2){ x + 18, y + 75 }, (Color){ 40, 62, 86, 255 });
    DrawText("SEGREDO?", (int)x + 13, (int)y + 20, 13, WHITE);
    DrawCircle((int)x + 68, (int)y + 13, 12, vermelho);
    DrawText("!", (int)x + 65, (int)y + 4, 19, WHITE);
    DrawRectangleRounded((Rectangle){ x + 27, y + 42, 32, 30 }, 0.18f, 5, ciano);
    DrawTriangle((Vector2){ x + 43, y + 48 }, (Vector2){ x + 33, y + 62 },
                 (Vector2){ x + 53, y + 62 }, (Color){ 20, 63, 82, 255 });
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
        case AMEACA_VAZAMENTO_DADOS: return "Vazamento de dados";
        case AMEACA_ENGENHARIA_SOCIAL: return "Engenharia social";
        case AMEACA_WIFI_FALSO: return "Wi-Fi falso";
        case AMEACA_LOJA_FALSA: return "Loja falsa";
        case AMEACA_DEEPFAKE: return "Deepfake/IA";
        case AMEACA_DOXXING: return "Doxxing";
        case AMEACA_SUPORTE_FALSO: return "Suporte falso";
        case AMEACA_ALICIAMENTO_ONLINE: return "Aliciamento online";
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
    ameacas[1] = (Ameaca){ AMEACA_MALWARE, { 980, CHAO_Y - 62 }, { 68, 62 }, 1.30f, 0, false, true, 10 };
    ameacas[2] = (Ameaca){ AMEACA_GOLPE_PAGAMENTO, { 1340, CHAO_Y - 82 }, { 70, 82 }, 1.10f, 0, false, true, 12 };
    ameacas[3] = (Ameaca){ AMEACA_PERFIL_FALSO, { 1700, CHAO_Y - 78 }, { 66, 78 }, 1.10f, 0, false, true, 12 };
    ameacas[4] = (Ameaca){ AMEACA_VIOLENCIA_DIGITAL, { 2060, CHAO_Y - 76 }, { 80, 76 }, 1.20f, 0, false, true, 10 };
    ameacas[5] = (Ameaca){ AMEACA_RANSOMWARE, { 2420, CHAO_Y - 98 }, { 74, 98 }, 1.40f, 0, false, true, 20 };
    ameacas[6] = (Ameaca){ AMEACA_INVASAO_CONTA, { 2780, CHAO_Y - 84 }, { 72, 84 }, 1.35f, 0, false, true, 16 };
    ameacas[7] = (Ameaca){ AMEACA_VAZAMENTO_DADOS, { 3140, CHAO_Y - 88 }, { 82, 88 }, 1.10f, 0, false, true, 12 };
    ameacas[8] = (Ameaca){ AMEACA_ENGENHARIA_SOCIAL, { 3500, CHAO_Y - 82 }, { 84, 82 }, 1.25f, 0, false, true, 14 };
    ameacas[9] = (Ameaca){ AMEACA_WIFI_FALSO, { 3860, CHAO_Y - 86 }, { 84, 86 }, 1.15f, 0, false, true, 12 };
    ameacas[10] = (Ameaca){ AMEACA_LOJA_FALSA, { 4220, CHAO_Y - 86 }, { 86, 86 }, 1.10f, 0, false, true, 12 };
    ameacas[11] = (Ameaca){ AMEACA_DEEPFAKE, { 4580, CHAO_Y - 88 }, { 82, 88 }, 1.30f, 0, false, true, 15 };
    ameacas[12] = (Ameaca){ AMEACA_DOXXING, { 4940, CHAO_Y - 88 }, { 78, 88 }, 1.20f, 0, false, true, 14 };
    ameacas[13] = (Ameaca){ AMEACA_SUPORTE_FALSO, { 5300, CHAO_Y - 86 }, { 84, 86 }, 1.25f, 0, false, true, 12 };
    ameacas[14] = (Ameaca){ AMEACA_ALICIAMENTO_ONLINE, { 5660, CHAO_Y - 82 }, { 86, 82 }, 1.10f, 0, false, true, 16 };
    ameacas[15] = (Ameaca){ AMEACA_PHISHING, { 6220, CHAO_Y - 65 }, { 70, 65 }, 1.05f, 0, false, true, 8 };
    ameacas[16] = (Ameaca){ AMEACA_MALWARE, { 6600, CHAO_Y - 62 }, { 68, 62 }, 1.30f, 0, false, true, 10 };
    ameacas[17] = (Ameaca){ AMEACA_GOLPE_PAGAMENTO, { 7000, CHAO_Y - 82 }, { 70, 82 }, 1.10f, 0, false, true, 12 };
    ameacas[18] = (Ameaca){ AMEACA_RANSOMWARE, { 7400, CHAO_Y - 98 }, { 74, 98 }, 1.40f, 0, false, true, 20 };
    ameacas[19] = (Ameaca){ AMEACA_INVASAO_CONTA, { 7800, CHAO_Y - 84 }, { 72, 84 }, 1.35f, 0, false, true, 16 };
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

        const char *nome = AmeacaNome(ameacas[i].tipo);
        int larguraNome = MeasureText(nome, 15);
        DrawRectangleRounded((Rectangle){ ameacas[i].posicao.x - 4,
                                          ameacas[i].posicao.y - 26,
                                          larguraNome + 12, 21 }, 0.35f, 5,
                             Fade((Color){ 255, 250, 235, 255 }, 0.88f));
        DrawText(nome, (int)ameacas[i].posicao.x + 2,
                 (int)ameacas[i].posicao.y - 23, 15, (Color){ 118, 20, 47, 255 });

        switch (ameacas[i].tipo)
        {
            case AMEACA_PHISHING: DesenharPhishing(ameacas[i]); break;
            case AMEACA_MALWARE: DesenharMalware(ameacas[i]); break;
            case AMEACA_PERFIL_FALSO: DesenharPerfilFalso(ameacas[i]); break;
            case AMEACA_RANSOMWARE: DesenharRansomware(ameacas[i]); break;
            case AMEACA_GOLPE_PAGAMENTO: DesenharGolpePagamento(ameacas[i]); break;
            case AMEACA_VIOLENCIA_DIGITAL: DesenharViolenciaDigital(ameacas[i]); break;
            case AMEACA_INVASAO_CONTA: DesenharInvasaoConta(ameacas[i]); break;
            case AMEACA_VAZAMENTO_DADOS: DesenharVazamentoDados(ameacas[i]); break;
            case AMEACA_ENGENHARIA_SOCIAL: DesenharEngenhariaSocial(ameacas[i]); break;
            case AMEACA_WIFI_FALSO: DesenharWifiFalso(ameacas[i]); break;
            case AMEACA_LOJA_FALSA: DesenharLojaFalsa(ameacas[i]); break;
            case AMEACA_DEEPFAKE: DesenharDeepfake(ameacas[i]); break;
            case AMEACA_DOXXING: DesenharDoxxing(ameacas[i]); break;
            case AMEACA_SUPORTE_FALSO: DesenharSuporteFalso(ameacas[i]); break;
            case AMEACA_ALICIAMENTO_ONLINE: DesenharAliciamentoOnline(ameacas[i]); break;
        }
    }
}
