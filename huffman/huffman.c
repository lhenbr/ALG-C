/*Lucas Henrique Braga Martins
11275126*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include <assert.h>

FREQ_TAB *create_freq_tab()
{
    int i;
    FREQ_TAB *tab = calloc(sizeof(FREQ_TAB), 90);
    for (i = 0; i <= 90; i++)
        tab[i].digit = i + 32;
    for (i = 0; i <= 90; i++)
        return tab;
}
FREQ_TAB *fill_freq_table(FREQ_TAB *tab, char *text)
{
    int i, length = strlen(text) - 1;
    for (i = 0; i < length; i++)
    {
        tab[text[i] - 32].occurrency++;
    }
    return tab;
}

LIST *list_create()
{
    LIST *list = calloc(1, sizeof(LIST));
    return list;
}
void list_add(LIST *list, char *digit, int occurrency, int dflag, LEAF *leaf)
{
    list->first = realloc(list->first, sizeof(L_ELEM) * (list->counter + 2));
    list->first[list->counter].occurrency = occurrency;
    list->first[list->counter].digit = malloc(strlen(digit));
    strcpy(list->first[list->counter].digit, digit);
    list->counter++;
    list->first[list->counter].dflag = dflag;
    list->first[list->counter].subtree = leaf;
    
    list_sort(list);
}
void list_sort(LIST *list)
{
    int i, j;
    L_ELEM aux;
    for (i = 0; i < list->counter; i++)
    {
        for (j = i + 1; j < list->counter; j++)
        {
            if (list->first[i].occurrency > list->first[j].occurrency)
            {
                aux = list->first[j];
                list->first[j] = list->first[i];
                list->first[i] = aux;
            }
        }
    }
}
L_ELEM *list_get_first(LIST *list)
{
    L_ELEM *aux = malloc(sizeof(L_ELEM));
    aux = &(list->first[0]);
    return aux;
}
void list_remove_first(LIST *list)
{
    memcmp(&(list->first[0]), &(list->first[1]), sizeof(L_ELEM) * (list->counter - 1));

    list->first = realloc(list->first, sizeof(L_ELEM) * (list->counter - 1));
    assert(list->first);
    list->counter--;
}
void list_free(LIST *list)
{
    while (list->counter)
    {
        list_remove_first(list);
    }
    free(list);
}
LIST *freq_to_list(LIST *list, FREQ_TAB *freq)
{
    int i;
    for (i = 0; i <= 90; i++)
    {
        if (freq[i].occurrency)
            list_add(list, &freq[i].digit, freq[i].occurrency, 1, NULL);
        list_sort(list);
    }
    return list;
}

TREE *tree_assembly(LIST *list)
{
    LEAF *left, *right, *new;
    L_ELEM *aux;
    TREE *tree = calloc(1, sizeof(TREE));
    while (list->counter > 1)
    {
        // cria elemento a direita

        aux = list_get_first(list);
        list_remove_first(list);

        if (aux->dflag)//se for uma letra cria o elemnto
        {
            right = calloc(1, sizeof(LEAF));
            assert(right);
            right->digit = malloc(strlen(aux->digit));
            strcpy(right->digit, aux->digit);
            right->ocurrency = aux->occurrency;
            right->dflag = aux->dflag;
        }
        else//se não, associa o ponteiro de uma subarvore existente
        {
            //right = aux->subtree;
        }

        // cria elemento a esquerda

        aux = list_get_first(list);
        list_remove_first(list);

        if (aux->dflag)
        {
            left = calloc(1, sizeof(LEAF));
            assert(left);
            left->digit = malloc(strlen(aux->digit));
            strcpy(left->digit, aux->digit);
            left->ocurrency = aux->occurrency;
            left->dflag = aux->dflag;
        }
        else
        {
            //left = aux->subtree;
        }
        //cria o pai
        new = calloc(1, sizeof(LEAF));
        assert(new);
        new->ocurrency = left->ocurrency + right->ocurrency;
        new->digit = malloc(strlen(left->digit) + strlen(right->digit));
        strcpy(new->digit,right->digit);
        strcat(new->digit,left->digit);
        new->right = right;
        new->left = left;

        //reinsere o elemento na lista
        list_add(list, new->digit, new->ocurrency, 0, new);
    }

    aux = list_get_first(list);
    tree->root = aux->subtree;
    return tree;
}
void bin_tab_add(BIN_TAB* btab,char digit,char *way){
    btab->first = realloc(btab,sizeof(BIN_ELEM)*(btab->counter+1));
    btab->first[btab->counter].digit = digit;
    btab->first[btab->counter].bin = malloc(strlen(way));
    strcpy(btab->first[btab->counter].bin,way);
    btab->counter++;
}
void __tree_way_builder(LEAF *node,BIN_TAB* btab,char *way) {
	if (node) {
        if(node->dflag){
            bin_tab_add(btab,node->digit[0],way);
        }
        node->way = malloc(strlen(way)+1);
        strcpy(node->way,way);
        way = realloc(way,strlen(way)+1);
		__tree_way_builder(node->left,btab,strcat(way,"0"));
		__tree_way_builder(node->right,btab,strcat(way,"1"));
	}
}BIN_TAB* tree_way_builder(TREE *tree) {//preenche e retorna os caminhos que vão ser usados na codificação
	BIN_TAB* btab;
    btab = calloc(1,sizeof(BIN_TAB));
    char *way;
    __tree_way_builder(tree->root,btab,way);
}
