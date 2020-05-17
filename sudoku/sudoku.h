/*Lucas Henrique Braga Martins
11275126*/
#ifndef _sudoku
#define _sudoku


char** le_mat();
void printa_mat(char**);
void free_mat(char**);
int n_valido(int linha, int coluna, char **mat, char verificar);
int preenchimento(char**);
int qtd_validos(int linha, int coluna,char** mat,char*);
void resolve_sudoku(char*** mat);



#endif