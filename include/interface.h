#ifndef INTERFACE_H
#define INTERFACE_H

#include "tipos.h"

bool InterfaceAtualizarBotao(BotaoUI botao);
void InterfaceDesenharBotao(BotaoUI botao, bool selecionado);

void InterfaceDesenharMenu(int opcao, const char *mensagem, float tempoMensagem);
void InterfaceDesenharInstrucoes(void);
void InterfaceDesenharHUD(int integridade, int resolvidas, bool escaneando,
                          const char *mensagem, float tempoMensagem);
void InterfaceDesenharPausa(int opcao, int resolvidas,
                            const char *mensagem, float tempoMensagem);
void InterfaceDesenharFalha(int resolvidas);
void InterfaceDesenharVitoria(void);
void InterfaceDesenharDica(DicaEducativa dica, int resolvidas);

#endif
