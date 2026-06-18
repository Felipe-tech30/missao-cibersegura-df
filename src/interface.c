#include "interface.h"

#include "config.h"
#include "mapa.h"

static const Color AZUL_PCDF = { 24, 72, 119, 255 };
static const Color AZUL_ESCURO = { 8, 31, 58, 255 };
static const Color CIANO = { 55, 229, 193, 255 };
static const Color AMARELO = { 250, 195, 45, 255 };
static const Color VERMELHO = { 215, 54, 79, 255 };

static void DesenharPainel(Rectangle area, float opacidade)
{
    DrawRectangleRounded(area, 0.08f, 8, Fade(AZUL_ESCURO, opacidade));
    DrawRectangleRoundedLinesEx(area, 0.08f, 8, 3, Fade(CIANO, 0.85f));
}

bool InterfaceAtualizarBotao(BotaoUI botao)
{
    return CheckCollisionPointRec(GetMousePosition(), botao.area) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void InterfaceDesenharBotao(BotaoUI botao, bool selecionado)
{
    bool hover = CheckCollisionPointRec(GetMousePosition(), botao.area);
    Color fundo = selecionado || hover ? CIANO : AZUL_PCDF;
    Color texto = selecionado || hover ? AZUL_ESCURO : WHITE;
    int tamanhoFonte = 27;
    int larguraTexto = MeasureText(botao.texto, tamanhoFonte);

    DrawRectangleRounded(botao.area, 0.22f, 7, fundo);
    DrawRectangleRoundedLinesEx(botao.area, 0.22f, 7, 3,
                                selecionado || hover ? WHITE : CIANO);
    DrawText(botao.texto,
             (int)(botao.area.x + botao.area.width / 2 - larguraTexto / 2),
             (int)(botao.area.y + botao.area.height / 2 - tamanhoFonte / 2),
             tamanhoFonte, texto);
}

void InterfaceDesenharMenu(int opcao, const char *mensagem, float tempoMensagem)
{
    BotaoUI botoes[4] = {
        { { 505, 319, 270, 54 }, "INICIAR MISSAO" },
        { { 505, 383, 270, 54 }, "COMO JOGAR" },
        { { 505, 447, 270, 54 }, "CONTINUAR" },
        { { 505, 511, 270, 54 }, "SAIR" }
    };
    int i;

    MapaDesenharFundoMenu();
    DesenharPainel((Rectangle){ 285, 48, 710, 610 }, 0.88f);

    DrawText("PCDF: MISSAO CIBERSEGURA", 345, 88, 42, CIANO);
    DrawText("Proteja o DF dos golpes digitais", 438, 147, 26, WHITE);
    DrawText("Projeto educativo ficticio - nao e um produto oficial", 408, 189, 19, AMARELO);

    DrawRectangleRounded((Rectangle){ 375, 229, 530, 58 }, 0.20f, 5,
                         Fade(AZUL_PCDF, 0.82f));
    DrawText(TextFormat("OBJETIVO: investigar %d alertas e aprender a se proteger", TOTAL_AMEACAS),
             397, 247, 19, WHITE);

    for (i = 0; i < 4; i++) InterfaceDesenharBotao(botoes[i], opcao == i);

    DrawText("W/S: navegar  |  ENTER: confirmar  |  Mouse: clicar",
             392, 596, 19, (Color){ 189, 214, 226, 255 });

    if (tempoMensagem > 0)
        DrawText(mensagem, LARGURA_TELA / 2 - MeasureText(mensagem, 20) / 2,
                 627, 20, AMARELO);
}

void InterfaceDesenharInstrucoes(void)
{
    MapaDesenharFundoMenu();
    DesenharPainel((Rectangle){ 170, 35, 940, 650 }, 0.93f);

    DrawText("BRIEFING DA MISSAO", 414, 68, 40, CIANO);
    DrawText("Voce integra uma equipe educativa de investigacao digital no DF.",
             257, 125, 23, WHITE);
    DrawText("Explore o mapa, encontre os alertas e use o scanner para conte-los.",
             235, 157, 23, WHITE);

    DrawText("CONTROLES", 235, 210, 26, AMARELO);
    DrawText("A / D", 260, 250, 22, CIANO);
    DrawText("mover", 365, 250, 22, WHITE);
    DrawText("W", 260, 284, 22, CIANO);
    DrawText("pular", 365, 284, 22, WHITE);
    DrawText("ESPACO", 260, 318, 22, CIANO);
    DrawText("acionar o scanner (nao ha armas)", 365, 318, 22, WHITE);
    DrawText("P / ESC", 260, 352, 22, CIANO);
    DrawText("pausar", 365, 352, 22, WHITE);
    DrawText("F5 / F9", 260, 386, 22, CIANO);
    DrawText("salvar / carregar", 365, 386, 22, WHITE);

    DrawText("RISCOS PRESENTES NA MISSAO", 235, 435, 26, AMARELO);
    DrawText("Phishing", 245, 478, 19, VERMELHO);
    DrawText("links enganosos", 245, 503, 17, WHITE);
    DrawText("Malware", 465, 478, 19, VERMELHO);
    DrawText("arquivos maliciosos", 465, 503, 17, WHITE);
    DrawText("Perfil falso", 685, 478, 19, VERMELHO);
    DrawText("imitacao de identidade", 685, 503, 17, WHITE);
    DrawText("Ransomware", 905, 478, 19, VERMELHO);
    DrawText("sequestro de dados", 905, 503, 17, WHITE);
    DrawText("Golpe de pagamento", 245, 545, 19, VERMELHO);
    DrawText("PIX e QR suspeitos", 245, 570, 17, WHITE);
    DrawText("Violencia digital", 510, 545, 19, VERMELHO);
    DrawText("ameaca e perseguicao", 510, 570, 17, WHITE);
    DrawText("Invasao de conta", 785, 545, 19, VERMELHO);
    DrawText("roubo de acesso", 785, 570, 17, WHITE);

    DrawText("Leia cada alerta: informacao tambem e protecao.", 350, 615, 22, CIANO);
    DrawText("BACKSPACE ou ESC: voltar", 490, 658, 18, (Color){ 189, 214, 226, 255 });
}

static void DesenharBarraIntegridade(int integridade)
{
    float proporcao = integridade / (float)INTEGRIDADE_MAXIMA;
    Color cor = integridade > 55 ? CIANO : (integridade > 25 ? AMARELO : VERMELHO);

    DrawText("PROTECAO", 24, 17, 18, WHITE);
    DrawRectangleRounded((Rectangle){ 24, 42, 260, 27 }, 0.35f, 7,
                         (Color){ 32, 45, 58, 255 });
    DrawRectangleRounded((Rectangle){ 24, 42, 260 * proporcao, 27 }, 0.35f, 7, cor);
    DrawRectangleRoundedLinesEx((Rectangle){ 24, 42, 260, 27 }, 0.35f, 7, 2, WHITE);
    DrawText(TextFormat("%d%%", integridade), 129, 45, 19, AZUL_ESCURO);
}

void InterfaceDesenharHUD(int integridade, int resolvidas, bool escaneando,
                          const char *mensagem, float tempoMensagem)
{
    DrawRectangle(0, 0, LARGURA_TELA, 92, Fade(AZUL_ESCURO, 0.88f));
    DesenharBarraIntegridade(integridade);

    DrawText("PCDF | OPERACAO EDUCATIVA", 324, 18, 21, CIANO);
    DrawText("A/D mover | W pular | ESPACO scanner | P pausar", 324, 50, 17, WHITE);
    DrawText(TextFormat("ALERTAS RESOLVIDOS  %d/%d", resolvidas, TOTAL_AMEACAS),
             927, 21, 20, AMARELO);
    DrawText(escaneando ? "SCANNER ATIVO" : "Pare um instante para recarregar a protecao",
             795, 53, 17, escaneando ? CIANO : (Color){ 189, 214, 226, 255 });

    if (tempoMensagem > 0)
    {
        int largura = MeasureText(mensagem, 21) + 36;
        DrawRectangleRounded((Rectangle){ LARGURA_TELA / 2.0f - largura / 2.0f, 105,
                                          (float)largura, 42 }, 0.3f, 6, Fade(AZUL_ESCURO, 0.92f));
        DrawText(mensagem, LARGURA_TELA / 2 - MeasureText(mensagem, 21) / 2,
                 116, 21, AMARELO);
    }
}

void InterfaceDesenharPausa(int opcao, int resolvidas,
                            const char *mensagem, float tempoMensagem)
{
    BotaoUI botoes[3] = {
        { { 500, 302, 280, 56 }, "CONTINUAR" },
        { { 500, 370, 280, 56 }, "SALVAR" },
        { { 500, 438, 280, 56 }, "VOLTAR AO MENU" }
    };
    int i;

    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade(AZUL_ESCURO, 0.78f));
    DesenharPainel((Rectangle){ 385, 135, 510, 485 }, 0.92f);
    DrawText("MISSAO PAUSADA", 438, 177, 43, CIANO);
    DrawText(TextFormat("Alertas resolvidos: %d/%d", resolvidas, TOTAL_AMEACAS),
             488, 238, 23, AMARELO);

    for (i = 0; i < 3; i++) InterfaceDesenharBotao(botoes[i], opcao == i);

    DrawText("W/S + ENTER ou mouse", 511, 527, 20, WHITE);
    DrawText("P/ESC: continuar | BACKSPACE: menu", 455, 563, 18,
             (Color){ 189, 214, 226, 255 });

    if (tempoMensagem > 0)
        DrawText(mensagem, LARGURA_TELA / 2 - MeasureText(mensagem, 21) / 2,
                 594, 21, AMARELO);
}

void InterfaceDesenharFalha(int resolvidas)
{
    MapaDesenharFundoMenu();
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade(AZUL_ESCURO, 0.82f));
    DesenharPainel((Rectangle){ 300, 135, 680, 445 }, 0.94f);

    DrawText("MISSAO INTERROMPIDA", 381, 186, 45, VERMELHO);
    DrawText("Sua protecao digital chegou a zero.", 439, 258, 25, WHITE);
    DrawText(TextFormat("Alertas resolvidos: %d/%d", resolvidas, TOTAL_AMEACAS),
             483, 311, 24, AMARELO);
    DrawText("Na internet, parar e verificar e melhor que agir com pressa.",
             357, 367, 22, CIANO);
    DrawText("R: reiniciar a missao", 493, 447, 24, WHITE);
    DrawText("BACKSPACE: voltar ao menu", 461, 492, 22, (Color){ 189, 214, 226, 255 });
}

void InterfaceDesenharVitoria(void)
{
    MapaDesenharFundoMenu();
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade(AZUL_ESCURO, 0.78f));
    DesenharPainel((Rectangle){ 230, 72, 820, 575 }, 0.95f);

    DrawText("MISSAO CUMPRIDA!", 405, 112, 48, CIANO);
    DrawText(TextFormat("Os %d alertas digitais do DF foram investigados.", TOTAL_AMEACAS),
             357, 180, 25, WHITE);

    DrawText("SEU PROTOCOLO DE SEGURANCA", 357, 235, 28, AMARELO);
    DrawText("1. Desconfie da urgencia e confira remetentes e links.", 315, 286, 22, WHITE);
    DrawText("2. Use senhas diferentes e ative a verificacao em duas etapas.", 315, 326, 22, WHITE);
    DrawText("3. Atualize dispositivos e mantenha copias de seguranca.", 315, 366, 22, WHITE);
    DrawText("4. Confirme pedidos de dinheiro por outro canal.", 315, 406, 22, WHITE);
    DrawText("5. Guarde evidencias e procure ajuda quando houver um crime.", 315, 446, 22, WHITE);

    DrawRectangleRounded((Rectangle){ 319, 498, 642, 62 }, 0.22f, 6, Fade(AZUL_PCDF, 0.95f));
    DrawText("Pensar antes de clicar e sua melhor ferramenta.", 372, 518, 23, CIANO);
    DrawText("R: jogar novamente  |  BACKSPACE: menu", 427, 598, 21, WHITE);
}

void InterfaceDesenharDica(DicaEducativa dica, int resolvidas)
{
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade(AZUL_ESCURO, 0.66f));
    DesenharPainel((Rectangle){ 170, 185, 940, 350 }, 0.98f);

    DrawText(dica.titulo, LARGURA_TELA / 2 - MeasureText(dica.titulo, 32) / 2,
             225, 32, AMARELO);
    DrawText(dica.linha1, LARGURA_TELA / 2 - MeasureText(dica.linha1, 22) / 2,
             299, 22, WHITE);
    DrawText(dica.linha2, LARGURA_TELA / 2 - MeasureText(dica.linha2, 22) / 2,
             341, 22, WHITE);
    DrawText(dica.linha3, LARGURA_TELA / 2 - MeasureText(dica.linha3, 22) / 2,
             383, 22, WHITE);
    DrawText(TextFormat("Progresso da investigacao: %d/%d", resolvidas, TOTAL_AMEACAS),
             467, 442, 21, CIANO);
    DrawText("ENTER: registrar aprendizado e continuar", 424, 486, 20,
             (Color){ 189, 214, 226, 255 });
}
