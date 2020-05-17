/*Lucas Henrique Braga Martins
11275126*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "sudoku.h"

int main(){
char **mat;
mat = le_mat();
resolve_sudoku(&mat);
printa_mat(mat);
free_mat(mat);
return 0;
}