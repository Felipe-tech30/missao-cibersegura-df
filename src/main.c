#include "raylib.h"

#include "config.h"
#include "jogo.h"

int main(void)
{
    InitWindow(LARGURA_TELA, ALTURA_TELA, "PCDF: Missao Cibersegura");
    SetTargetFPS(60);
    JogoExecutar();
    CloseWindow();
    return 0;
}
