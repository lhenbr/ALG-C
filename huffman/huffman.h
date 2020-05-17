/*Lucas Henrique Braga Martins
11275126*/
#ifndef _huffman_
#define _huffman_

typedef struct freq_tab {
    char digit;
    int occurrency;
}FREQ_TAB;

typedef struct bin_tab{
    int counter;
    struct bin_elem* first;
}BIN_TAB;

typedef struct bin_elem{
    char digit;
    char *bin;
}BIN_ELEM;

typedef struct list_elem{
    char* digit;
    int occurrency;
    int dflag;
    struct leaf *subtree;
}L_ELEM;

typedef struct list{
    L_ELEM *first;
    int counter;
}LIST;

typedef struct leaf{
    char* digit;
    char* way;
    int ocurrency;
    int dflag;
    struct leaf *left,*right;
}LEAF;

typedef struct tree
{
    LEAF* root;
    int size;
}TREE;

//funçoes da tabela de frequencia
FREQ_TAB* fill_freq_table(FREQ_TAB* tab,char* text);
FREQ_TAB* create_freq_tab();
//funçoes da lista que ajuda a montar a arvore
LIST* list_create();
void list_add(LIST*,char*,int,int,LEAF*);
void list_sort(LIST*);
L_ELEM* list_get_first(LIST*);
void list_remove_first(LIST*);
void list_free(LIST*);
LIST* freq_to_list(LIST*list,FREQ_TAB*freq);
//funçoes da arvore de codificação
TREE* tree_create();
TREE* tree_assembly(LIST*);
BIN_TAB* tree_way_builder(TREE *tree);

#endif // !1_huffman_
