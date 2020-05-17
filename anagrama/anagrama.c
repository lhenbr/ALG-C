/* Lucas Henrique Braga Martins
NUSP: 11275126*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "anagrama.h"
#include <assert.h>

//função para calcular hash adaptada do algoritmo djb2 disponivel em http://www.cse.yorku.ca/~oz/hash.html
unsigned long f_hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % 500009; //dividir em modulo o resultado pela capacidade da tabela hash para obter os indices
}
HASHTABLE *create_hash(int size)
{
    HASHTABLE *hash = malloc(sizeof(HASHTABLE));
    assert(hash);
    hash->load = 0;
    hash->size = size;
    hash->word = calloc(sizeof(char *), size);
    assert(hash->word);
    return hash;
}
void free_hash(HASHTABLE *hash)
{
    int i;
    if (hash)
    {
        for (i = 0; i < hash->size; i++)
        {
            if (hash->word[i])
                free(hash->word[i]);
        }
        free(hash->word);
        free(hash);
    }
}
void add_hash(HASHTABLE *hash, unsigned char *str)
{
    int key;
    unsigned char *new;
    new = malloc(sizeof(unsigned char) * strlen(str));
    strcpy(new, str);
    key = f_hash(str);
    while (hash->word[key])
        key++;
    hash->word[key] = new;
    hash->load++;
}
void swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

int partition(char *arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort_char(char *arr, int low, int high) //função para ordernar lexograficamente as palavras e facilitar a comparação
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quicksort_char(arr, low, pi - 1);
        quicksort_char(arr, pi + 1, high);
    }
}
int is_anagram(char *str1, char *str2)//copia os strings,ordena e compara para conferir se é um anagrama
{
    char *t_str1 = malloc(strlen(str1));
    strcpy(t_str1,str1);
    char *t_str2 = malloc(strlen(str2));
    strcpy(t_str2,str2);
    quicksort_char(t_str1, 0, strlen(t_str1) - 1);
    quicksort_char(t_str2, 0, strlen(t_str2) - 1);
    if (!strcmp(t_str1, t_str2))
        return 1;
    return 0;
}
GROUP* create_group(GROUP *groups, int numg, int first,int length) 
//cria um novo grupo de anagramas
{
    groups[numg-1].first = first;
    groups[numg-1].length_w = length;
    groups[numg-1].n_words = 1;
    groups[numg-1].words = malloc(sizeof(int));
    groups[numg-1].words[0] = first;
    return groups;
}
GROUP* add_to_group(GROUP *groups, int group_index,int word) 
//adiciona informaçoes sobre o anagrama em um grupo que já existe 
{
    groups[group_index].n_words++;
    groups[group_index].words=realloc(groups[group_index].words,sizeof(int)*groups[group_index].n_words);
    groups[group_index].words[groups[group_index].n_words-1] = word;
    return groups;
}
GROUP *find_anagrams(HASHTABLE *hash, GROUP *groups, int *n_groups)
//cria um vetor de grupos de anagramas, percorrendo o vetor adicionando palavras em grupos já existentes e criando novos grupos
{
    int i, j, add_flag = 0, numg = 0;
    for (i = 0; i < hash->size; i++)
    { 
        if (hash->word[i])
        {
            add_flag = 0;
            for (j = 0; j < numg; j++){
                if (strlen(hash->word[i]) == strlen(hash->word[groups[j].first])); 
                /*comparar o comprimento é uma operação menos custosa que verificar se é um anagrama,
                esse teste visa acelerar o tempo de execução do código eliminando alguns casos*/
                if (is_anagram(hash->word[i], hash->word[groups[j].first]))
                {
                    groups = add_to_group(groups, j, i); 
                    add_flag = 1;
                    break;
                }
            }
            if (!add_flag)
            {
               numg++;
               groups = realloc(groups,sizeof(GROUP)*numg);
               groups = create_group(groups,numg,i,strlen(hash->word[i]));
            }
            
        }
    }
    *n_groups = numg;
    return groups;
}
void swap_word(int *a,int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition_word(HASHTABLE *hash, int *arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (strcmp(hash->word[arr[j]], hash->word[pivot]) < 0)
        {
            i++;
            swap_word(&arr[i], &arr[j]);
        }
    }
    swap_word(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort_word(HASHTABLE *hash, int *arr, int low, int high) 
//função para ordernar lexograficamente as palavras de um vetor de indices da tabela hash
{
    if (low < high)
    {
        int pi = partition_word(hash, arr, low, high);

        quicksort_word(hash, arr, low, pi - 1);
        quicksort_word(hash, arr, pi + 1, high);
    }
}

int count_groups(HASHTABLE *hash, GROUP *groups, int n, C_GROUP *result) // função que conta quantos grupos de anagramas de cada comprimento há
{
    int i, j, n_results = 0, add_flag;
    for (i = 0; i < n; i++)
    {
        add_flag = 0;
        for (j = 0; j < n_results; j++)
        {
            if (groups[i].length_w == result[j].length)
            {
                (result[j].number)++;
                result[j].index_first = realloc(result[j].index_first, sizeof(int) * result[j].number);
                result[j].index_first[n_results - 1] = groups[i].first;
                add_flag = 1;
                break;
            }
        }
        if (add_flag ==0)
        {
            (n_results)++;
            result = realloc(result, sizeof(C_GROUP) * n_results+1);
            result[n_results - 1].length = groups[i].length_w;
            result[n_results - 1].index_first = malloc(sizeof(int));
            result[n_results - 1].index_first[0] = groups[i].first;
            result[n_results - 1].number = 1;
        }
    }
    return n_results;
}
void print_group(GROUP group, HASHTABLE *hash)//imprime as palavras de um grupo
{
    int i;
    for (i = 0; i < group.n_words - 1; i++)
    {
        printf("%s ", hash->word[group.words[i]]);
    }
    printf("\n");
}
void print_groups(HASHTABLE *hash, GROUP *groups, C_GROUP *result, int n_results, int n_groups)
//imprime a linha de resposta
{
    int bigger = 0, bigger_index, i, j;
    for (i = 0; i < n_results; i++)
    {
        if (bigger < result[i].number)
        {
            bigger = result[i].number;
            bigger_index = i;
        }
    }
    printf("%d\n",bigger);
    //problema ta daqui para baixo
    //quicksort_word(hash, result[bigger_index].index_first, 0, result[bigger_index].number - 1); // ordena as primeiras palavras dos groups alfabeticamente

    for (i = 0; i < result[bigger_index].number; i++)
    {
        for (j = 0; j < n_groups; j++)
        {
            if (result[bigger_index].index_first[i] == groups[j].first)
            {
                //quicksort_word(hash, groups[j].words, 0, groups[j].n_words - 1); //ordena as palavras dentro de groups alfabeticamente
                print_group(groups[j], hash);
                break;
            }
        }
    }
}