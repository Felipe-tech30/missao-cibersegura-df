#ifndef TIPOS_H
#define TIPOS_H

#include "raylib.h"

typedef enum EstadoJogo
{
    ESTADO_MENU,
    ESTADO_JOGANDO,
    ESTADO_INSTRUCOES,
    ESTADO_PAUSA,
    ESTADO_FALHA,
    ESTADO_VITORIA
} EstadoJogo;

typedef enum TipoTile
{
    TILE_AR = 0,
    TILE_GRAMA,
    TILE_TERRA,
    TILE_CONCRETO,
    TILE_DADO_CORROMPIDO
} TipoTile;

typedef enum TipoAmeaca
{
    AMEACA_PHISHING,
    AMEACA_MALWARE,
    AMEACA_PERFIL_FALSO,
    AMEACA_RANSOMWARE,
    AMEACA_GOLPE_PAGAMENTO,
    AMEACA_VIOLENCIA_DIGITAL,
    AMEACA_INVASAO_CONTA
} TipoAmeaca;

typedef struct Ameaca
{
    TipoAmeaca tipo;
    Vector2 posicao;
    Vector2 tamanho;
    float velocidade;
    float velocidadeY;
    bool noChao;
    bool ativa;
    int dano;
} Ameaca;

typedef struct BotaoUI
{
    Rectangle area;
    const char *texto;
} BotaoUI;

typedef struct DicaEducativa
{
    const char *titulo;
    const char *linha1;
    const char *linha2;
    const char *linha3;
} DicaEducativa;

#endif
