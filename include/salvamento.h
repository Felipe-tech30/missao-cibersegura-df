#ifndef SALVAMENTO_H
#define SALVAMENTO_H

#include "tipos.h"

bool SalvamentoSalvar(Vector2 jogador, int integridade, int resolvidas,
                      const Ameaca ameacas[]);
bool SalvamentoCarregar(Vector2 *jogador, int *integridade, int *resolvidas,
                        Ameaca ameacas[]);

#endif
