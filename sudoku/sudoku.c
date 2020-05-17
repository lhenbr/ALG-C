/*Lucas Henrique Braga Martins
11275126*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sudoku.h>

char **aloca_mat(int linhas, int colunas)
{
    int i;
    char **new;
    new = (char **)malloc(sizeof(char *) * (linhas + 3));
    assert(new);
    for (i = 0; i < linhas; i++)
    {
        new[i] = (char *)malloc(sizeof(char) * (colunas + 3));
        assert(new[i]);
    }
    return new;
}
char **le_mat()
{
    int i;
    char **mat;
    mat = aloca_mat(16, 16);

    for (i = 0; i < 16; i++)
    {
            fscanf(stdin, " %s",mat[i]); // _ _ _ \0   ***sge fault
    }
    return mat;
}
void printa_mat(char **mat)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        printf("%s", mat[i]);
        printf("\n");
    }
}
void free_mat(char **mat)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        free(mat[i]);
    }
    free(mat);
}
int n_valido(int linha, int coluna, char **mat, char verificar)
{
    int i, j, col_quad, lin_quad;
    for (i = 0; i < 16; i++)
    {
        if (mat[linha][i] == verificar)
            return 0; //verifica linha

        if (mat[i][coluna] == verificar)
            return 0; //verifica coluna
    }
    lin_quad = (linha / 4) * 4;
    col_quad = (coluna / 4) * 4;

    for (i = lin_quad; i < lin_quad + 4; i++)
    {
        for (j = col_quad; j < col_quad + 4; j++)
        {
            if (mat[i][j] == verificar)
            {
                return 0;
            }
        }
    }
    return 1;
}
int qtd_validos(int linha, int coluna, char **mat, char *ult_valid)
{
    int i, validos = 0;
    char carac;
    *ult_valid = 0;
    for (i = 0; i < 16; i++)
    {
        if (i < 10)
        {
            carac = i + '0';
            if (n_valido(linha, coluna, mat, carac) == 1)
            {
                validos++;
                *ult_valid = carac;
            }
        }
        else
        {
            carac = 'A' + (i - 10);
            if (n_valido(linha, coluna, mat, carac) == 1)
            {
                validos++;
                *ult_valid = carac;
            }
        }
    }
    return validos;
}
int preenchimento(char **mat)
{
    int i, j, preenchidos = 0;
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
        {
            if (mat[i][j] != '.')
                preenchidos++;
        }
    }
    return preenchidos;
}
void resolve_sudoku(char ***mat)
{
    int i, j, qtd, preenchidos;
    char ultimo_valido;
    preenchidos = preenchimento(*mat);

    while (preenchidos < 256)
    {
        for (j = 0; j < 16; j++)
        {
            for (i = 0; i < 16; i++)
            {
                if ((*mat)[i][j] == '.')
                {
                    qtd = qtd_validos(i, j, *mat, &ultimo_valido);
                    if (qtd && qtd == 1)
                    {
                        (*mat)[i][j] = ultimo_valido;
                        preenchidos++;
                    }
                }
            }
        }
    }
}
