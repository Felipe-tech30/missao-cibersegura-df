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

static void DesenharTextoCentralizado(const char *texto, int centroX, int y,
                                      int tamanhoFonte, Color cor)
{
    DrawText(texto, centroX - MeasureText(texto, tamanhoFonte) / 2,
             y, tamanhoFonte, cor);
}

static void DesenharTextoDireita(const char *texto, int direita, int y,
                                 int tamanhoFonte, Color cor)
{
    DrawText(texto, direita - MeasureText(texto, tamanhoFonte),
             y, tamanhoFonte, cor);
}

static const char *InterfaceFaseAtual(int resolvidas)
{
    if (resolvidas < 4) return "FASE 1 - Base PCDF e escola";
    if (resolvidas < 8) return "FASE 2 - Golpes financeiros";
    if (resolvidas < 12) return "FASE 3 - Esplanada digital";
    if (resolvidas < 16) return "FASE 4 - Lago e redes abertas";
    return "FASE 5 - Operacao final";
}

static void DesenharChipAmeaca(int x, int y, int largura,
                               const char *titulo, const char *subtitulo)
{
    DrawRectangleRounded((Rectangle){ x, y, largura, 45 }, 0.18f, 6,
                         Fade(AZUL_PCDF, 0.82f));
    DrawRectangleRoundedLinesEx((Rectangle){ x, y, largura, 45 }, 0.18f, 6, 1,
                                Fade(CIANO, 0.70f));
    DrawText(titulo, x + 10, y + 7, 15, AMARELO);
    DrawText(subtitulo, x + 10, y + 26, 12, (Color){ 220, 236, 241, 255 });
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

    DesenharTextoCentralizado("PCDF: MISSAO CIBERSEGURA", LARGURA_TELA / 2, 88, 42, CIANO);
    DesenharTextoCentralizado("Proteja o DF dos golpes digitais", LARGURA_TELA / 2, 147, 26, WHITE);
    DesenharTextoCentralizado("Projeto educativo ficticio - nao e um produto oficial",
                              LARGURA_TELA / 2, 189, 19, AMARELO);

    DrawRectangleRounded((Rectangle){ 375, 229, 530, 58 }, 0.20f, 5,
                         Fade(AZUL_PCDF, 0.82f));
    DesenharTextoCentralizado(
        TextFormat("OBJETIVO: investigar %d alertas em 5 fases do DF", TOTAL_AMEACAS),
        LARGURA_TELA / 2, 247, 19, WHITE);

    for (i = 0; i < 4; i++) InterfaceDesenharBotao(botoes[i], opcao == i);

    DesenharTextoCentralizado("W/S: navegar  |  ENTER: confirmar  |  Mouse: clicar",
                              LARGURA_TELA / 2, 596, 19,
                              (Color){ 189, 214, 226, 255 });

    if (tempoMensagem > 0)
        DrawText(mensagem, LARGURA_TELA / 2 - MeasureText(mensagem, 20) / 2,
                 627, 20, AMARELO);
}

void InterfaceDesenharInstrucoes(void)
{
    MapaDesenharFundoMenu();
    DesenharPainel((Rectangle){ 170, 35, 940, 650 }, 0.93f);

    DesenharTextoCentralizado("BRIEFING DA MISSAO", LARGURA_TELA / 2, 64, 40, CIANO);
    DesenharTextoCentralizado("Voce integra uma equipe educativa de investigacao digital no DF.",
                              LARGURA_TELA / 2, 121, 23, WHITE);
    DesenharTextoCentralizado("Explore 5 fases, encontre 20 alertas e use o scanner para conte-los.",
                              LARGURA_TELA / 2, 153, 23, WHITE);

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

    DrawText("RISCOS PRESENTES NA MISSAO", 235, 424, 24, AMARELO);
    DesenharChipAmeaca(235, 462, 198, "Phishing", "links enganosos");
    DesenharChipAmeaca(447, 462, 198, "Malware", "arquivos maliciosos");
    DesenharChipAmeaca(659, 462, 198, "Perfil falso", "identidade falsa");
    DesenharChipAmeaca(871, 462, 198, "Ransomware", "dados sequestrados");
    DesenharChipAmeaca(235, 513, 198, "Pagamento/QR", "PIX suspeito");
    DesenharChipAmeaca(447, 513, 198, "Violencia digital", "ameaca online");
    DesenharChipAmeaca(659, 513, 198, "Invasao de conta", "acesso roubado");
    DesenharChipAmeaca(871, 513, 198, "Vazamento dados", "exposicao indevida");
    DesenharChipAmeaca(235, 564, 198, "Engenharia social", "manipulacao");
    DesenharChipAmeaca(447, 564, 198, "Wi-Fi falso", "rede armadilha");
    DesenharChipAmeaca(659, 564, 198, "Loja falsa", "compra fraudulenta");
    DesenharChipAmeaca(871, 564, 198, "Deepfake/IA", "midia manipulada");
    DesenharChipAmeaca(235, 615, 198, "Doxxing", "dados publicados");
    DesenharChipAmeaca(447, 615, 198, "Suporte falso", "acesso remoto");
    DesenharChipAmeaca(659, 615, 198, "Aliciamento", "pressao e segredo");

    DrawText("BACKSPACE ou ESC: voltar", 490, 666, 18, (Color){ 189, 214, 226, 255 });
}

static void DesenharBarraIntegridade(int integridade)
{
    float proporcao = integridade / (float)INTEGRIDADE_MAXIMA;
    Color cor = integridade > 55 ? CIANO : (integridade > 25 ? AMARELO : VERMELHO);
    int larguraTexto;

    DrawText("PROTECAO", 28, 15, 18, WHITE);
    DrawRectangleRounded((Rectangle){ 28, 42, 248, 27 }, 0.35f, 7,
                         (Color){ 32, 45, 58, 255 });
    DrawRectangleRounded((Rectangle){ 28, 42, 248 * proporcao, 27 }, 0.35f, 7, cor);
    DrawRectangleRoundedLinesEx((Rectangle){ 28, 42, 248, 27 }, 0.35f, 7, 2, WHITE);
    larguraTexto = MeasureText(TextFormat("%d%%", integridade), 19);
    DrawText(TextFormat("%d%%", integridade), 152 - larguraTexto / 2, 45, 19, AZUL_ESCURO);
}

void InterfaceDesenharHUD(int integridade, int resolvidas, bool escaneando,
                          const char *mensagem, float tempoMensagem)
{
    const char *fase = InterfaceFaseAtual(resolvidas);
    const char *progresso;
    float proporcao = resolvidas / (float)TOTAL_AMEACAS;

    DrawRectangle(0, 0, LARGURA_TELA, 104, Fade(AZUL_ESCURO, 0.90f));
    DrawRectangle(0, 96, LARGURA_TELA, 8, Fade(CIANO, 0.55f));
    DesenharBarraIntegridade(integridade);
    progresso = TextFormat("ALERTAS  %d/%d", resolvidas, TOTAL_AMEACAS);

    DrawText("PCDF | OPERACAO EDUCATIVA", 318, 16, 21, CIANO);
    DrawText(fase, 318, 43, 18, AMARELO);
    DrawText("A/D mover | W pular | ESPACO scanner | P pausar | F5/F9 save",
             318, 70, 15, WHITE);

    DesenharTextoDireita(progresso, 1248, 17, 20, AMARELO);
    DrawRectangleRounded((Rectangle){ 912, 50, 334, 15 }, 0.45f, 8,
                         (Color){ 32, 45, 58, 255 });
    DrawRectangleRounded((Rectangle){ 912, 50, 334 * proporcao, 15 }, 0.45f, 8,
                         CIANO);
    DrawRectangleRoundedLinesEx((Rectangle){ 912, 50, 334, 15 }, 0.45f, 8, 1,
                                WHITE);
    DesenharTextoDireita(escaneando ? "SCANNER ATIVO" : "Recarregue parado para recuperar protecao",
                         1248, 72, 15,
                         escaneando ? CIANO : (Color){ 189, 214, 226, 255 });

    if (tempoMensagem > 0)
    {
        int largura = MeasureText(mensagem, 21) + 36;
        DrawRectangleRounded((Rectangle){ LARGURA_TELA / 2.0f - largura / 2.0f, 116,
                                          (float)largura, 42 }, 0.3f, 6, Fade(AZUL_ESCURO, 0.92f));
        DrawText(mensagem, LARGURA_TELA / 2 - MeasureText(mensagem, 21) / 2,
                 127, 21, AMARELO);
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
    DesenharTextoCentralizado("MISSAO PAUSADA", LARGURA_TELA / 2, 177, 43, CIANO);
    DesenharTextoCentralizado(TextFormat("Alertas resolvidos: %d/%d", resolvidas, TOTAL_AMEACAS),
                              LARGURA_TELA / 2, 238, 23, AMARELO);

    for (i = 0; i < 3; i++) InterfaceDesenharBotao(botoes[i], opcao == i);

    DesenharTextoCentralizado("W/S + ENTER ou mouse", LARGURA_TELA / 2, 527, 20, WHITE);
    DesenharTextoCentralizado("P/ESC: continuar | BACKSPACE: menu",
                              LARGURA_TELA / 2, 563, 18,
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

    DesenharTextoCentralizado("MISSAO INTERROMPIDA", LARGURA_TELA / 2, 186, 45, VERMELHO);
    DesenharTextoCentralizado("Sua protecao digital chegou a zero.",
                              LARGURA_TELA / 2, 258, 25, WHITE);
    DesenharTextoCentralizado(TextFormat("Alertas resolvidos: %d/%d", resolvidas, TOTAL_AMEACAS),
                              LARGURA_TELA / 2, 311, 24, AMARELO);
    DesenharTextoCentralizado("Na internet, parar e verificar e melhor que agir com pressa.",
                              LARGURA_TELA / 2, 367, 22, CIANO);
    DesenharTextoCentralizado("R: reiniciar a missao", LARGURA_TELA / 2, 447, 24, WHITE);
    DesenharTextoCentralizado("BACKSPACE: voltar ao menu", LARGURA_TELA / 2, 492, 22,
                              (Color){ 189, 214, 226, 255 });
}

void InterfaceDesenharVitoria(void)
{
    MapaDesenharFundoMenu();
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade(AZUL_ESCURO, 0.78f));
    DesenharPainel((Rectangle){ 230, 72, 820, 575 }, 0.95f);

    DesenharTextoCentralizado("MISSAO CUMPRIDA!", LARGURA_TELA / 2, 112, 48, CIANO);
    DesenharTextoCentralizado(TextFormat("Os %d alertas digitais do DF foram investigados.", TOTAL_AMEACAS),
                              LARGURA_TELA / 2, 180, 25, WHITE);

    DesenharTextoCentralizado("SEU PROTOCOLO DE SEGURANCA", LARGURA_TELA / 2, 235, 28, AMARELO);
    DrawText("1. Desconfie da urgencia e confira remetentes e links.", 315, 286, 22, WHITE);
    DrawText("2. Use senhas diferentes e ative a verificacao em duas etapas.", 315, 326, 22, WHITE);
    DrawText("3. Atualize dispositivos e mantenha copias de seguranca.", 315, 366, 22, WHITE);
    DrawText("4. Confirme pedidos de dinheiro por outro canal.", 315, 406, 22, WHITE);
    DrawText("5. Guarde evidencias e procure ajuda quando houver um crime.", 315, 446, 22, WHITE);

    DrawRectangleRounded((Rectangle){ 319, 498, 642, 62 }, 0.22f, 6, Fade(AZUL_PCDF, 0.95f));
    DesenharTextoCentralizado("Pensar antes de clicar e sua melhor ferramenta.",
                              LARGURA_TELA / 2, 518, 23, CIANO);
    DesenharTextoCentralizado("R: jogar novamente  |  BACKSPACE: menu",
                              LARGURA_TELA / 2, 598, 21, WHITE);
}

void InterfaceDesenharDica(DicaEducativa dica, int resolvidas)
{
    int fonteTitulo = MeasureText(dica.titulo, 32) > 850 ? 27 : 32;
    int fonteLinha1 = MeasureText(dica.linha1, 22) > 860 ? 19 : 22;
    int fonteLinha2 = MeasureText(dica.linha2, 22) > 860 ? 19 : 22;
    int fonteLinha3 = MeasureText(dica.linha3, 22) > 860 ? 19 : 22;

    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade(AZUL_ESCURO, 0.66f));
    DesenharPainel((Rectangle){ 170, 185, 940, 350 }, 0.98f);

    DesenharTextoCentralizado(dica.titulo, LARGURA_TELA / 2, 225, fonteTitulo, AMARELO);
    DesenharTextoCentralizado(dica.linha1, LARGURA_TELA / 2, 299, fonteLinha1, WHITE);
    DesenharTextoCentralizado(dica.linha2, LARGURA_TELA / 2, 341, fonteLinha2, WHITE);
    DesenharTextoCentralizado(dica.linha3, LARGURA_TELA / 2, 383, fonteLinha3, WHITE);
    DesenharTextoCentralizado(TextFormat("Progresso da investigacao: %d/%d", resolvidas, TOTAL_AMEACAS),
                              LARGURA_TELA / 2, 442, 21, CIANO);
    DesenharTextoCentralizado("ENTER: registrar aprendizado e continuar",
                              LARGURA_TELA / 2, 486, 20,
                              (Color){ 189, 214, 226, 255 });
}
