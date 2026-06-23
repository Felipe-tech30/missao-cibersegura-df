#include "jogo.h"

#include <stdlib.h>

#include "raylib.h"

#include "ameacas.h"
#include "config.h"
#include "dicas.h"
#include "interface.h"
#include "mapa.h"
#include "personagem.h"
#include "salvamento.h"
#include "tipos.h"

typedef struct Jogo
{
    EstadoJogo estado;
    Vector2 jogador;
    Vector2 tamanhoJogador;
    float velocidadeY;
    bool noChao;
    int direcao;
    int integridade;
    int resolvidas;
    float tempoScanner;
    float tempoDano;
    float tempoRecarga;
    float tempoMensagem;
    const char *mensagem;
    int opcaoMenu;
    int opcaoPausa;
    bool dicaAtiva;
    DicaEducativa dicaAtual;
    Ameaca ameacas[TOTAL_AMEACAS];
    Camera2D camera;
    bool executando;
    bool modoCaptura;
    int quadrosCaptura;
} Jogo;

static void AtualizarCamera(Jogo *jogo)
{
    jogo->camera.target = (Vector2){
        jogo->jogador.x + jogo->tamanhoJogador.x / 2,
        jogo->jogador.y + jogo->tamanhoJogador.y / 2
    };

    if (jogo->camera.target.x < LARGURA_TELA / 2.0f)
        jogo->camera.target.x = LARGURA_TELA / 2.0f;
    if (jogo->camera.target.y < ALTURA_TELA / 2.0f)
        jogo->camera.target.y = ALTURA_TELA / 2.0f;
    if (jogo->camera.target.x > LARGURA_MUNDO - LARGURA_TELA / 2.0f)
        jogo->camera.target.x = LARGURA_MUNDO - LARGURA_TELA / 2.0f;
    if (jogo->camera.target.y > ALTURA_MUNDO - ALTURA_TELA / 2.0f)
        jogo->camera.target.y = ALTURA_MUNDO - ALTURA_TELA / 2.0f;
}

static void ReiniciarMissao(Jogo *jogo)
{
    jogo->jogador = (Vector2){ 300, CHAO_Y - jogo->tamanhoJogador.y };
    jogo->velocidadeY = 0;
    jogo->noChao = true;
    jogo->direcao = 1;
    jogo->integridade = INTEGRIDADE_MAXIMA;
    jogo->resolvidas = 0;
    jogo->tempoScanner = 0;
    jogo->tempoDano = 0;
    jogo->tempoRecarga = 0;
    jogo->dicaAtiva = false;
    AmeacasReiniciar(jogo->ameacas);
    AtualizarCamera(jogo);
}

static void DefinirMensagem(Jogo *jogo, const char *mensagem)
{
    jogo->mensagem = mensagem;
    jogo->tempoMensagem = 2.2f;
}

static void SalvarMissao(Jogo *jogo)
{
    if (SalvamentoSalvar(jogo->jogador, jogo->integridade,
                         jogo->resolvidas, jogo->ameacas))
        DefinirMensagem(jogo, "Missao salva");
    else
        DefinirMensagem(jogo, "Nao foi possivel salvar");
}

static bool CarregarMissao(Jogo *jogo)
{
    AmeacasReiniciar(jogo->ameacas);

    if (!SalvamentoCarregar(&jogo->jogador, &jogo->integridade,
                            &jogo->resolvidas, jogo->ameacas))
    {
        DefinirMensagem(jogo, "Nenhuma missao salva foi encontrada");
        return false;
    }

    jogo->velocidadeY = 0;
    jogo->noChao = true;
    jogo->tempoScanner = 0;
    jogo->tempoDano = 0;
    jogo->tempoRecarga = 0;
    jogo->dicaAtiva = false;
    AtualizarCamera(jogo);
    DefinirMensagem(jogo, "Missao carregada");
    return true;
}

static void MoverSelecao(int *opcao, int quantidade)
{
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
        *opcao = (*opcao + 1) % quantidade;
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
    {
        (*opcao)--;
        if (*opcao < 0) *opcao = quantidade - 1;
    }
}

static void ExecutarOpcaoMenu(Jogo *jogo, int opcao)
{
    switch (opcao)
    {
        case 0:
            ReiniciarMissao(jogo);
            jogo->estado = ESTADO_JOGANDO;
            break;
        case 1:
            jogo->estado = ESTADO_INSTRUCOES;
            break;
        case 2:
            if (CarregarMissao(jogo))
                jogo->estado = jogo->resolvidas == TOTAL_AMEACAS ?
                    ESTADO_VITORIA : ESTADO_JOGANDO;
            break;
        case 3:
            jogo->executando = false;
            break;
    }
}

static void AtualizarMenu(Jogo *jogo)
{
    BotaoUI botoes[4] = {
        { { 505, 319, 270, 54 }, "INICIAR MISSAO" },
        { { 505, 383, 270, 54 }, "COMO JOGAR" },
        { { 505, 447, 270, 54 }, "CONTINUAR" },
        { { 505, 511, 270, 54 }, "SAIR" }
    };
    int i;

    MoverSelecao(&jogo->opcaoMenu, 4);

    for (i = 0; i < 4; i++)
    {
        if (InterfaceAtualizarBotao(botoes[i]))
        {
            jogo->opcaoMenu = i;
            ExecutarOpcaoMenu(jogo, i);
            return;
        }
    }

    if (IsKeyPressed(KEY_ENTER)) ExecutarOpcaoMenu(jogo, jogo->opcaoMenu);
    if (IsKeyPressed(KEY_ESCAPE)) jogo->executando = false;
}

static void AbrirDica(Jogo *jogo, TipoAmeaca tipo)
{
    jogo->dicaAtual = DicasParaAmeaca(tipo);
    jogo->dicaAtiva = true;
}

static void AtualizarJogando(Jogo *jogo, float dt)
{
    Rectangle areaJogador;
    Rectangle areaScanner;
    bool movendo = false;
    bool tocandoAmeaca = false;
    bool emDadoCorrompido;
    bool escaneando;
    float dx = 0;
    int i;

    if (jogo->dicaAtiva)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            jogo->dicaAtiva = false;
            if (jogo->resolvidas == TOTAL_AMEACAS)
                jogo->estado = ESTADO_VITORIA;
        }
        return;
    }

    areaJogador = (Rectangle){ jogo->jogador.x, jogo->jogador.y,
                               jogo->tamanhoJogador.x, jogo->tamanhoJogador.y };

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        dx += 4.5f;
        jogo->direcao = 1;
        movendo = true;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        dx -= 4.5f;
        jogo->direcao = -1;
        movendo = true;
    }
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && jogo->noChao)
    {
        jogo->velocidadeY = -12.0f;
        jogo->noChao = false;
        movendo = true;
    }

    MapaMoverComFisica(&areaJogador, dx, &jogo->velocidadeY, &jogo->noChao);
    jogo->jogador = (Vector2){ areaJogador.x, areaJogador.y };
    AmeacasAtualizar(jogo->ameacas, areaJogador);

    if (IsKeyPressed(KEY_SPACE)) jogo->tempoScanner = 0.28f;
    if (jogo->tempoScanner > 0)
    {
        jogo->tempoScanner -= dt;
        if (jogo->tempoScanner < 0) jogo->tempoScanner = 0;
    }
    escaneando = jogo->tempoScanner > 0;

    if (jogo->direcao >= 0)
        areaScanner = (Rectangle){ jogo->jogador.x + 48, jogo->jogador.y + 13, 102, 72 };
    else
        areaScanner = (Rectangle){ jogo->jogador.x - 96, jogo->jogador.y + 13, 102, 72 };

    if (escaneando)
    {
        for (i = 0; i < TOTAL_AMEACAS; i++)
        {
            if (jogo->ameacas[i].ativa &&
                CheckCollisionRecs(areaScanner, AmeacaPegarHitbox(jogo->ameacas[i])))
            {
                TipoAmeaca tipo = jogo->ameacas[i].tipo;
                jogo->ameacas[i].ativa = false;
                jogo->resolvidas++;
                jogo->tempoScanner = 0;
                AbrirDica(jogo, tipo);
                break;
            }
        }
    }

    if (jogo->tempoDano > 0) jogo->tempoDano -= dt;

    for (i = 0; i < TOTAL_AMEACAS; i++)
    {
        if (jogo->ameacas[i].ativa &&
            CheckCollisionRecs(areaJogador, AmeacaPegarHitbox(jogo->ameacas[i])))
        {
            tocandoAmeaca = true;
            if (jogo->tempoDano <= 0)
            {
                jogo->integridade -= jogo->ameacas[i].dano;
                jogo->tempoDano = 0.85f;
            }
        }
    }

    emDadoCorrompido = MapaEncostaDadoCorrompido(areaJogador);
    if (emDadoCorrompido && jogo->tempoDano <= 0)
    {
        jogo->integridade -= 18;
        jogo->tempoDano = 0.85f;
        DefinirMensagem(jogo, "Cuidado: link corrompido!");
    }

    if (!movendo && jogo->noChao && !escaneando && !tocandoAmeaca && !emDadoCorrompido &&
        jogo->integridade < INTEGRIDADE_MAXIMA)
    {
        jogo->tempoRecarga += dt;
        if (jogo->tempoRecarga >= 1.0f)
        {
            jogo->integridade += 4;
            if (jogo->integridade > INTEGRIDADE_MAXIMA)
                jogo->integridade = INTEGRIDADE_MAXIMA;
            jogo->tempoRecarga = 0;
        }
    }
    else jogo->tempoRecarga = 0;

    if (IsKeyPressed(KEY_F5)) SalvarMissao(jogo);
    if (IsKeyPressed(KEY_F9) && CarregarMissao(jogo) &&
        jogo->resolvidas == TOTAL_AMEACAS)
        jogo->estado = ESTADO_VITORIA;

    if (jogo->integridade <= 0)
    {
        jogo->integridade = 0;
        jogo->estado = ESTADO_FALHA;
    }
    else if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE))
        jogo->estado = ESTADO_PAUSA;

    AtualizarCamera(jogo);
}

static void ExecutarOpcaoPausa(Jogo *jogo, int opcao)
{
    if (opcao == 0) jogo->estado = ESTADO_JOGANDO;
    else if (opcao == 1) SalvarMissao(jogo);
    else if (opcao == 2) jogo->estado = ESTADO_MENU;
}

static void AtualizarPausa(Jogo *jogo)
{
    BotaoUI botoes[3] = {
        { { 500, 302, 280, 56 }, "CONTINUAR" },
        { { 500, 370, 280, 56 }, "SALVAR" },
        { { 500, 438, 280, 56 }, "VOLTAR AO MENU" }
    };
    int i;

    MoverSelecao(&jogo->opcaoPausa, 3);
    for (i = 0; i < 3; i++)
    {
        if (InterfaceAtualizarBotao(botoes[i]))
        {
            jogo->opcaoPausa = i;
            ExecutarOpcaoPausa(jogo, i);
            return;
        }
    }

    if (IsKeyPressed(KEY_ENTER)) ExecutarOpcaoPausa(jogo, jogo->opcaoPausa);
    if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)) jogo->estado = ESTADO_JOGANDO;
    if (IsKeyPressed(KEY_BACKSPACE)) jogo->estado = ESTADO_MENU;
}

static void Atualizar(Jogo *jogo, float dt)
{
    if (jogo->tempoMensagem > 0) jogo->tempoMensagem -= dt;

    if (IsKeyPressed(KEY_F12))
    {
        TakeScreenshot("assets/screenshots/gameplay-missao-cibersegura.png");
        DefinirMensagem(jogo, "Captura salva em assets/screenshots");
    }

    switch (jogo->estado)
    {
        case ESTADO_MENU:
            AtualizarMenu(jogo);
            break;
        case ESTADO_INSTRUCOES:
            if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_ESCAPE))
                jogo->estado = ESTADO_MENU;
            break;
        case ESTADO_JOGANDO:
            AtualizarJogando(jogo, dt);
            break;
        case ESTADO_PAUSA:
            AtualizarPausa(jogo);
            break;
        case ESTADO_FALHA:
            if (IsKeyPressed(KEY_R))
            {
                ReiniciarMissao(jogo);
                jogo->estado = ESTADO_JOGANDO;
            }
            if (IsKeyPressed(KEY_BACKSPACE)) jogo->estado = ESTADO_MENU;
            break;
        case ESTADO_VITORIA:
            if (IsKeyPressed(KEY_R))
            {
                ReiniciarMissao(jogo);
                jogo->estado = ESTADO_JOGANDO;
            }
            if (IsKeyPressed(KEY_BACKSPACE)) jogo->estado = ESTADO_MENU;
            break;
    }
}

static void DesenharMundo(Jogo *jogo, bool escaneando)
{
    BeginMode2D(jogo->camera);
    MapaDesenharFundo(jogo->camera);
    AmeacasDesenhar(jogo->ameacas);
    PersonagemDesenhar(jogo->jogador, jogo->direcao, escaneando);
    EndMode2D();
}

static void Desenhar(Jogo *jogo)
{
    BeginDrawing();

    switch (jogo->estado)
    {
        case ESTADO_MENU:
            InterfaceDesenharMenu(jogo->opcaoMenu, jogo->mensagem,
                                  jogo->tempoMensagem);
            break;
        case ESTADO_INSTRUCOES:
            InterfaceDesenharInstrucoes();
            break;
        case ESTADO_JOGANDO:
            DesenharMundo(jogo, jogo->tempoScanner > 0);
            InterfaceDesenharHUD(jogo->integridade, jogo->resolvidas,
                                 jogo->tempoScanner > 0,
                                 jogo->mensagem, jogo->tempoMensagem);
            if (jogo->dicaAtiva)
                InterfaceDesenharDica(jogo->dicaAtual, jogo->resolvidas);
            break;
        case ESTADO_PAUSA:
            DesenharMundo(jogo, false);
            InterfaceDesenharPausa(jogo->opcaoPausa, jogo->resolvidas,
                                   jogo->mensagem, jogo->tempoMensagem);
            break;
        case ESTADO_FALHA:
            InterfaceDesenharFalha(jogo->resolvidas);
            break;
        case ESTADO_VITORIA:
            InterfaceDesenharVitoria();
            break;
    }

    EndDrawing();
}

void JogoExecutar(void)
{
    Jogo jogo = { 0 };

    jogo.estado = ESTADO_MENU;
    jogo.tamanhoJogador = (Vector2){ 55, 95 };
    jogo.mensagem = "";
    jogo.camera.offset = (Vector2){ LARGURA_TELA / 2.0f, ALTURA_TELA / 2.0f };
    jogo.camera.zoom = 1.0f;
    jogo.executando = true;

    MapaInicializar();
    ReiniciarMissao(&jogo);

    if (getenv("PCDF_MODO_CAPTURA") != NULL)
    {
        jogo.estado = ESTADO_JOGANDO;
        jogo.modoCaptura = true;
        jogo.jogador = (Vector2){ 2260, CHAO_Y - jogo.tamanhoJogador.y };
        AtualizarCamera(&jogo);
    }

    while (jogo.executando && !WindowShouldClose())
    {
        Atualizar(&jogo, GetFrameTime());
        Desenhar(&jogo);

        if (jogo.modoCaptura && ++jogo.quadrosCaptura >= 90)
        {
            TakeScreenshot("assets/screenshots/gameplay-missao-cibersegura.png");
            jogo.executando = false;
        }
    }
}
