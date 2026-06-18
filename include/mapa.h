#ifndef MAPA_H
#define MAPA_H

#include "raylib.h"

void MapaInicializar(void);
bool MapaColide(Rectangle area);
bool MapaEncostaDadoCorrompido(Rectangle area);
void MapaMoverComFisica(Rectangle *area, float deslocamentoX,
                        float *velocidadeY, bool *noChao);
void MapaDesenhar(Camera2D camera);
void MapaDesenharFundo(Camera2D camera);
void MapaDesenharFundoMenu(void);

#endif
