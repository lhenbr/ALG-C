/*Lucas Henrique Braga Martins
11275126*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void read_image(int ***matrix, int height, int width)
{
    int i, j;
    *matrix = (int **)malloc(sizeof(int *) * height);
    assert(*matrix);

    for (i = 0; i < height; i++)
    {
        (*matrix)[i] = (int *)malloc(sizeof(int) * width + 1);
        assert((*matrix)[i]);
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            scanf(" %d", &(*matrix)[i][j]);
        }
        (*matrix)[i][width] = -44; //adiciona um ponto de parada para a função compress
    }
}
void compress(int ***matrix, int height, int width)
{
    int reps = 1;
    int i, j, k;
    for (i = 0; i < height; i++)
    {
        //printf("linha");
        for (j = 0; j < width; j++)
        {
            if ((*matrix)[i][j] == (*matrix)[i][j + 1])
            {
                reps++;
            }
            if ((*matrix)[i][j] != (*matrix)[i][j + 1])
            {
                if (reps > 3)
                {
                    if( j-reps+1==0)
                    printf("@ %d %d", (*matrix)[i][j], reps);
                    else
                    printf(" @ %d %d", (*matrix)[i][j], reps);
                }
                else
                {
                    for (k = reps - 1; k >= 0; k--)
                    {
                        if (j-k == 0)
                        {
                            printf("%d", (*matrix)[i][j - k]);
                        }
                        else
                            printf(" %d", (*matrix)[i][j - k]);
                    }
                }
                reps = 1;
            }
        }
        printf("\n");
    }
}
void decompress(int heigth, int width)
{
    char digit[5];
    int line = 0, reps, cor, i, cmp, j;

    for (j = 0; j < heigth; j++)
    {
        while (line < width)
        {
            scanf("%s ", digit);

            if (strcmp(digit, "@"))
            {
                if (line == 0)
                    printf("%s", digit);
                else
                    printf(" %s", digit);
                line++;
            }
            else
            {
                scanf("%d %d", &cor, &reps);
                for (i = 0; i < reps; i++)
                {
                    if (line == 0)
                        printf("%d", cor);
                    else
                        printf(" %d", cor);
                    line++;
                }
            }
        }
        line = 0;
        printf("\n");
    }
}
void free_matrix(int ***matrix, int height, int width){
int i;
for(i=0;i<height;i++)
    free((*matrix)[i]);
free(*matrix);
}