#include <stdlib.h>
#include <stdio.h>
#include <esparsa.h>

SPARSE *sparse_create(int nrows, int ncols, double constant)
{
    SPARSE *new = malloc(sizeof(SPARSE));
    new->ncols = ncols;
    new->nrows = nrows;
    new->constant = constant;

    new->col_index = malloc(sizeof(S_ELEM) * ncols);
    new->row_index = malloc(sizeof(S_ELEM) * nrows);
    return new;
}

int sparse_put(SPARSE *sparse, int row, int col, double elem)
{
    if (!sparse)
    {
        return INVALID_SPARSE;
    }
    if (row < 0 || col < 0)
    {
        return INVALID_POS;
    }
    S_ELEM **rp = &(sparse->row_index[row]);
    S_ELEM **cp = &(sparse->col_index[col]);

    while (*rp && (*rp)->col < col && (rp = &(*rp)->rigth))
        ;
    while (*cp && (*cp)->row < row && (cp = &(*cp)->bottom))
        ;

    if (*cp && *rp && (*cp)->col == col && (*rp)->row == row)
    {
        (*cp)->elem = elem;
    }

    {
        S_ELEM *new = malloc(sizeof(S_ELEM));
        new->row = row;
        new->col = col;
        new->elem = elem;
        new->bottom = *cp;
        new->rigth = *rp;
        *rp = *cp = new;
    }
    return SUCCESS;
}
double sparse_get(SPARSE *sparse, int row, int col)
{
    S_ELEM **rp = &sparse->row_index[row];
    S_ELEM **cp = &sparse->col_index[col];

    /*if (!sparse)
        return INVALID_SPARSE;
    if (row < 0 || col < 0 || col >= sparse->ncols || row >= sparse->nrows)
        return INVALID_POS;*/

    while (*rp && ((*rp)->col < col))
        rp = &(*rp)->rigth;
    while (*cp && ((*cp)->row < row))
        cp = &(*cp)->bottom;

    if (*rp && *cp && (*cp)->col == col && (*rp)->row == row)
        return (*rp)->elem;
    else
        return sparse->constant;
}
int sparse_free(SPARSE *sparse)
{
    int i;
    if (!sparse)
        return INVALID_SPARSE;
    S_ELEM *p;

    for (i = 0; i < sparse->nrows; i++) //observar
    {
        while (p = sparse->row_index[i])
        {
            sparse->row_index[i] = p->rigth;
            free(p);
        }
    }
    free(sparse->col_index);
    free(sparse->row_index);
    free(sparse);
    return SUCCESS;
}
int sum_sparse(SPARSE *s1, SPARSE *s2)
{
    int i, j;
    int result = 0;

    printf("-1 %d %d\n", s1->nrows, s1->ncols);

    for (i = 0; i < s1->nrows; i++)
    {
        for (j = 0; j < s1->ncols; j++)
        {
            result = (int)sparse_get(s1, i, j) + (int)sparse_get(s2, i, j);
            if (result)
            {
                printf("%d %d %d\n", i, j, result);
            }
        }
    }
    return SUCCESS;
}

int mult_sparse(SPARSE *s1, SPARSE *s2)
{
    int i, j, k;
    double result = 0;

    printf("-1 %d %d\n", s1->nrows, s1->ncols);

    for (i = 0; i < s1->nrows; i++)
    {
        for (j = 0; j < s1->ncols; j++)
        {
            //calcular elemento
            for (k = 0; k < s1->ncols; k++)
            {
                result += sparse_get(s1, i, k) * sparse_get(s2, k, j);
            }
            if (result)
            {
                printf("%d %d %d\n", i, j, (int)result);
                result = 0;
            }
        }
    }

    return SUCCESS;
}
