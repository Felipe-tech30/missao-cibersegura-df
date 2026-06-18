#include "salvamento.h"

#include <stdio.h>
#include <string.h>

#include "config.h"

bool SalvamentoSalvar(Vector2 jogador, int integridade, int resolvidas,
                      const Ameaca ameacas[])
{
    FILE *arquivo = fopen(ARQUIVO_SAVE, "w");
    int i;

    if (!arquivo) return false;

    fprintf(arquivo, "PCDF_SAVE_V1\n");
    fprintf(arquivo, "%f %f %d %d\n", jogador.x, jogador.y, integridade, resolvidas);

    for (i = 0; i < TOTAL_AMEACAS; i++)
        fprintf(arquivo, "%d %f %f\n", ameacas[i].ativa ? 1 : 0,
                ameacas[i].posicao.x, ameacas[i].posicao.y);

    fclose(arquivo);
    return true;
}

bool SalvamentoCarregar(Vector2 *jogador, int *integridade, int *resolvidas,
                        Ameaca ameacas[])
{
    FILE *arquivo = fopen(ARQUIVO_SAVE, "r");
    char versao[32];
    int i;

    if (!arquivo) return false;
    if (!fgets(versao, sizeof(versao), arquivo) || strncmp(versao, "PCDF_SAVE_V1", 12) != 0)
    {
        fclose(arquivo);
        return false;
    }

    if (fscanf(arquivo, "%f %f %d %d", &jogador->x, &jogador->y,
               integridade, resolvidas) != 4)
    {
        fclose(arquivo);
        return false;
    }

    for (i = 0; i < TOTAL_AMEACAS; i++)
    {
        int ativa;
        if (fscanf(arquivo, "%d %f %f", &ativa,
                   &ameacas[i].posicao.x, &ameacas[i].posicao.y) != 3)
        {
            fclose(arquivo);
            return false;
        }
        ameacas[i].ativa = ativa != 0;
    }

    fclose(arquivo);

    if (*integridade < 1 || *integridade > INTEGRIDADE_MAXIMA ||
        *resolvidas < 0 || *resolvidas > TOTAL_AMEACAS)
        return false;

    return true;
}
