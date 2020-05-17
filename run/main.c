/*Lucas Henrique Braga Martins
11275126*/
#include <stdio.h>
#include <stdlib.h>
#include "run_length.h"
#include <string.h>

int main()
{
    char *type;
    int width,height,gray_max,**matrix; 
    scanf(" %s ", type);
    scanf(" %d ", &width);
    scanf(" %d ", &height);
    scanf(" %d ", &gray_max);
    if (!strcmp(type, "P2"))
    {
        printf("P8\n%d %d\n%d\n", width, height, gray_max);
        read_image(&matrix,height,width);
        compress(&matrix,height, width);
        free_matrix(&matrix,height,width);
    }
    else
    {
        printf("P2\n%d %d\n%d\n", width, height, gray_max);
        decompress(height, width);
    }
    return 0;
}