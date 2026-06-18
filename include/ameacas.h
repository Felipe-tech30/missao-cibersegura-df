#ifndef AMEACAS_H
#define AMEACAS_H

#include "tipos.h"

void AmeacasReiniciar(Ameaca ameacas[]);
void AmeacasAtualizar(Ameaca ameacas[], Rectangle jogador);
void AmeacasDesenhar(const Ameaca ameacas[]);
Rectangle AmeacaPegarHitbox(Ameaca ameaca);
const char *AmeacaNome(TipoAmeaca tipo);

#endif
