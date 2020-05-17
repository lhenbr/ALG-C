
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "sudoku.h"

int main(){
char **mat,*filename = malloc(300);
scanf("%s",filename);
mat = le_mat(filename);

printf("valido %d\n",n_valido(0,0,mat,'1'));
//printf("%d %d\n",qtd_validos(14,1,mat,&ult),ult);
//printa_mat(mat);

free_mat(mat);
return 0;
}