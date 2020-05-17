/*Lucas Henrique Braga Martins
11275126*/
#ifndef arraylist_
#define arraylist_

//DEFINES
#define SUCCESS 1
#define INVALID_POS -1



struct list{//elementos do vetor
    int key;
    int value;
};
typedef struct list LIST;

struct array_elem{ //descreve um no, e aponta para um vetor de elementos
    int max_list;
    int counter;
    struct array_elem *next;
    LIST *list;
};
typedef struct array_elem ARRAY_ELEM;

struct arraylist{ //descritor da lista
    int elements;
    int ar_elements;
    ARRAY_ELEM *first;
    ARRAY_ELEM *last;
};
typedef struct  arraylist ARRAYLIST;

//funcoes
int arraylist_size(ARRAYLIST*);//retorna o numero de elementos 
int arraylist_add(ARRAYLIST*,int, int); //adiciona um elemento
ARRAYLIST* arraylist_sub(ARRAYLIST*,int,int);// cria uma nova lista incluindo o elemento inicial e excluindo o ultimo elemento
int arraylist_set(ARRAYLIST*,int,int,int);//muda chave valor do elemento na Posição indicada
int arraylist_print(ARRAYLIST*);//printa toda a lista
int arraylist_contains(ARRAYLIST*,int);//verifica se tem algum elemento com a CHAVE dada
int arraylist_index(ARRAYLIST*,int);//printa o indice do primeiro elemento que contem a chave
int arraylist_empty(ARRAYLIST*);
int arraylist_delete(ARRAYLIST*,int);//deleta o elemento na POSICAO indicada
int arraylist_get(ARRAYLIST*,int);//retorna o elemento na POSICAO indicada
void free_arraylist(ARRAYLIST *);
#endif