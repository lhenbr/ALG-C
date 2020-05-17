/*Lucas Henrique Braga Martins
11275126*/
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(){
    char *text = malloc(10001);
    FREQ_TAB *freq;
    LIST* list;
    L_ELEM* elem;
    TREE* tree;
    BIN_TAB* btab; 
    freq = create_freq_tab();
    fgets(text,10001,stdin);
    freq = fill_freq_table(freq,text);// a partir do texto recebido, cria uma tabela de frequencia
    list = list_create();
    list=freq_to_list(list,freq);//transforma a tabela de frequencia em uma lista, para auxiliar na montagem da arvore
    tree = tree_assembly(list);
    btab = tree_way_builder(tree);//gera uma tabela com os binarios(caminhos) de cada digito
    /*Os proximos passos seriam corrigir o segfault na tree_assembly,usar a tabela de frequencia para codificar o texto,
     escrever em bits, criar uma função que decodifica os bits e imprimir os tamanhos      */
    list_free(list);
    free(freq);
    free(text);
    return 0;
}