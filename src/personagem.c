#include "personagem.h"

void PersonagemDesenhar(Vector2 posicao, int direcao, bool escaneando)
{
    int x = (int)posicao.x;
    int y = (int)posicao.y;
    Color pele = (Color){ 196, 137, 93, 255 };
    Color cabelo = (Color){ 55, 38, 31, 255 };
    Color azul = (Color){ 24, 72, 119, 255 };
    Color azulEscuro = (Color){ 15, 43, 78, 255 };
    Color amarelo = (Color){ 250, 195, 45, 255 };

    /* Agente cartunesco da equipe de investigacao digital. */
    DrawCircle(x + 27, y + 19, 19, pele);
    DrawRectangle(x + 9, y + 4, 36, 8, cabelo);
    DrawRectangle(x + 7, y + 8, 7, 16, cabelo);
    DrawCircle(x + 21, y + 18, 2, BLACK);
    DrawCircle(x + 34, y + 18, 2, BLACK);
    DrawLine(x + 23, y + 29, x + 32, y + 29, (Color){ 105, 57, 48, 255 });

    DrawRectangleRounded((Rectangle){ x + 7, y + 38, 40, 37 }, 0.22f, 5, azul);
    DrawRectangle(x + 12, y + 75, 13, 17, azulEscuro);
    DrawRectangle(x + 30, y + 75, 13, 17, azulEscuro);
    DrawRectangle(x + 9, y + 90, 17, 5, (Color){ 34, 37, 43, 255 });
    DrawRectangle(x + 29, y + 90, 17, 5, (Color){ 34, 37, 43, 255 });

    DrawRectangle(x - 1, y + 42, 9, 30, azul);
    DrawCircle(x + 3, y + 72, 5, pele);
    DrawRectangle(x + 47, y + 42, 9, 30, azul);
    DrawCircle(x + 52, y + 72, 5, pele);

    DrawCircle(x + 27, y + 54, 12, amarelo);
    DrawText("PCDF", x + 14, y + 49, 11, azulEscuro);
    DrawRectangleLines(x + 7, y + 38, 40, 37, azulEscuro);

    /* O scanner substitui armas: a missao e identificar e conter riscos. */
    if (direcao >= 0)
    {
        DrawRectangleRounded((Rectangle){ x + 52, y + 48, 24, 17 }, 0.25f, 4, azulEscuro);
        DrawCircle(x + 69, y + 56, 4, (Color){ 55, 229, 193, 255 });
        if (escaneando)
        {
            DrawTriangle((Vector2){ x + 75, y + 42 }, (Vector2){ x + 75, y + 70 },
                         (Vector2){ x + 135, y + 56 }, Fade((Color){ 55, 229, 193, 255 }, 0.38f));
            DrawCircleLines(x + 112, y + 56, 22, (Color){ 55, 229, 193, 255 });
        }
    }
    else
    {
        DrawRectangleRounded((Rectangle){ x - 21, y + 48, 24, 17 }, 0.25f, 4, azulEscuro);
        DrawCircle(x - 14, y + 56, 4, (Color){ 55, 229, 193, 255 });
        if (escaneando)
        {
            DrawTriangle((Vector2){ x - 20, y + 42 }, (Vector2){ x - 20, y + 70 },
                         (Vector2){ x - 80, y + 56 }, Fade((Color){ 55, 229, 193, 255 }, 0.38f));
            DrawCircleLines(x - 57, y + 56, 22, (Color){ 55, 229, 193, 255 });
        }
    }
}
