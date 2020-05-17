/*Lucas Henrique Braga Martins
11275126*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "arraylist.h"

int arraylist_size(ARRAYLIST *arraylist) //retorna o numero de elementos
{
    printf("%d\n", arraylist->elements);
}
int arraylist_add(ARRAYLIST *arraylist, int key, int value) //adiciona um elemento
{
    int i, j, max_cap = 0, jmp_counter = 0, flag_add = 0;
    ARRAY_ELEM **p;
    LIST **l, temp1, temp2;

    for (i = 0; i < arraylist->ar_elements; i++) //calcula a capacidade maxima com os array_elem atuais
        max_cap += 10 * pow(2, i);

    if (arraylist->elements == 0)
    {
        ARRAY_ELEM *new; //cria o novo elemento
        new = (ARRAY_ELEM *)calloc(1, sizeof(ARRAY_ELEM));
        arraylist->first = arraylist->last = new;
        new->max_list = 10;
        new->list = (LIST *)malloc(sizeof(LIST));
        arraylist->ar_elements++;
    }
    //garantir malloc para os outros casos, ultimo e criar um novo elem
    else if (max_cap > arraylist->elements)
    {
        p = &arraylist->last;
        (*p)->list = (LIST *)realloc((*p)->list, sizeof(LIST) * (*p)->counter + 1);
    }
    else if (max_cap == arraylist->elements && max_cap != 0)
    {
        ARRAY_ELEM *new; //cria o novo elemento
        new = (ARRAY_ELEM *)calloc(1, sizeof(ARRAY_ELEM));
        arraylist->last = new;

        p = &arraylist->first;
        while ((*p)->next)
            p = &((*p)->next);
        (*p)->next = new;
        new->list = (LIST *)malloc(sizeof(LIST) * 1);
        new->max_list = 10 * pow(2, arraylist->ar_elements);
        arraylist->ar_elements++;
    }

    p = &arraylist->first;
    while (jmp_counter < arraylist->ar_elements)
    {
        for (i = 0; i < (*p)->counter; i++)
        {
            if ((*p)->list[i].key >= key) //achou a posição
            {
                temp1 = (*p)->list[((*p)->counter - 1)];
                for (j = (*p)->counter - 2; j >= i; j--)
                {
                    (*p)->list[j + 1] = (*p)->list[j];
                }
                (*p)->list[i].key = key;
                (*p)->list[i].value = value;

                if ((*p)->counter == (*p)->max_list)
                {
                    while ((*p)->counter == (*p)->max_list)
                    {
                        p = &((*p)->next);
                        temp2 = (*p)->list[(*p)->counter - 1];
                        for (j = (*p)->counter - 1; j >= 0; j--)
                        {
                            (*p)->list[j + 1] = (*p)->list[j];
                        }
                        (*p)->list[0] = temp1;
                        temp1 = temp2;
                    }

                    /*for (j = (*p)->counter - 1; j >= 0; j--)
                    {
                        (*p)->list[j + 1] = (*p)->list[j];
                    }*/
                    //(*p)->list[0] = temp1;
                }
                else
                {
                    (*p)->list[(*p)->counter] = temp1;
                }

                arraylist->elements++;
                (*p)->counter++;
                return SUCCESS;
                flag_add = 1;
            }
        }
        p = &((*p)->next);
        jmp_counter++;
    }
    if (flag_add == 0)
    { //se a troca nao aconteceu ,adicionar na ultima posicao
        p = &arraylist->last;
        (*p)->list[(*p)->counter].key = key;
        (*p)->list[(*p)->counter].value = value;
        (*p)->counter++;
        arraylist->elements++;
    }

    return SUCCESS;
}
ARRAYLIST *arraylist_sub(ARRAYLIST *arraylist, int pos1, int pos2) // cria uma nova lista incluindo o elemento inicial e excluindo o ultimo elemento
{

    ARRAYLIST *sublist = (ARRAYLIST *)calloc(1, sizeof(ARRAYLIST));
    ARRAY_ELEM **p;
    int jmp_counter = 0, pos_counter = 0, i;

    for (i = pos1; i < pos2; i++)
    {
        pos_counter = 0;
        jmp_counter = 0;
        p = &arraylist->first;
        while (jmp_counter < arraylist->ar_elements)
        {
            if (pos_counter + (*p)->counter > i)
            {
                arraylist_add(sublist, (*p)->list[i - pos_counter].key, (*p)->list[i - pos_counter].value);
                break;
            }
            pos_counter += (*p)->counter;
            p = &((*p)->next);
            jmp_counter++;
        }
    }
    return sublist;
}
int arraylist_set(ARRAYLIST *arraylist, int pos, int key, int value) //muda chave valor do elemento na Posição indicada
{
    if(pos<0 || pos > arraylist->elements-1){
        return INVALID_POS;
    }
    arraylist_delete(arraylist, pos);
    arraylist_add(arraylist, key, value);
    return  SUCCESS;
}
int arraylist_print(ARRAYLIST *arraylist) //printa toda a lista
{
    int i, j = 0, jmp_counter = 0;
    ARRAY_ELEM **p;

    p = &arraylist->first;
    while (jmp_counter < arraylist->ar_elements)
    {
        //printf("max_list: %d\n", (*p)->max_list);
        //printf("counter: %d\n", (*p)->counter);
        for (i = 0; i < (*p)->counter; i++)
        {
            printf("%d: ", j);
            j++;
            printf("%d/%d\n", (*p)->list[i].key, (*p)->list[i].value);
        }
        printf("\n\n");
        p = &((*p)->next);
        jmp_counter++;
    }
    return 0;
}
int arraylist_contains(ARRAYLIST *arraylist, int key) //verifica se tem algum elemento com a CHAVE dada
{
    int jmp_counter = 0, contains = 0, i;
    ARRAY_ELEM **p;
    p = &arraylist->first;
    while (jmp_counter < arraylist->ar_elements)
    {
        for (i = 0; i < (*p)->counter; i++)
        {
            if ((*p)->list[i].key == key)
                contains = 1;
        }

        p = &((*p)->next);
        jmp_counter++;
    }
    printf("%d\n", contains);
    return SUCCESS;
}
int arraylist_index(ARRAYLIST *arraylist, int key) //printa o indice do primeiro elemento que contem a chave
{

    int jmp_counter = 0, pos_counter = 0, i;

    ARRAY_ELEM **p;
    p = &arraylist->first;
    while (jmp_counter < arraylist->ar_elements)
    {
        for (i = 0; i < (*p)->counter; i++)
        {
            if ((*p)->list[i].key == key)
            {
                printf("%d\n", pos_counter);
            }
            pos_counter++;
        }

        p = &((*p)->next);
        jmp_counter++;
    }
    return SUCCESS;
}
int arraylist_empty(ARRAYLIST *arraylist)
{
    if (arraylist->elements == 0)
        printf("1");
    else
        printf("0");
}
int arraylist_delete(ARRAYLIST *arraylist, int pos) //deleta o elemento na POSICAO indicada
{

    int jmp_counter = 0, pos_counter = 0, i;
    LIST temp1, temp2;
    if (pos < 0 || pos > arraylist->elements)
        return INVALID_POS;

    ARRAY_ELEM **p, **next;
    p = &arraylist->first;
    while (jmp_counter < arraylist->ar_elements)
    {
        if (pos_counter + (*p)->counter > pos)
        {
            for (i = pos - pos_counter; i < (*p)->counter - 1; i++)
                (*p)->list[i] = (*p)->list[i + 1];
            if ((*p)->counter == (*p)->max_list)
            {
                while ((*p)->counter == (*p)->max_list)
                {
                    next = p;
                    next = &((*next)->next);
                    (*p)->list[(*p)->counter - 1] = (*next)->list[0];
                    for (i = 0; i < (*next)->counter - 1; i++)
                        (*next)->list[i] = (*next)->list[i + 1];
                    next = p;
                    p = &((*p)->next);
                }
            }
            if ((*p)->counter == 1)
            {
                free((*p)->list);
                free((*p));
                arraylist->last = (*next);
            }
            else
            {
                (*p)->list = (LIST *)realloc((*p)->list, sizeof(LIST) * (*p)->counter - 1);
            }

            (*p)->counter--;
            arraylist->elements--;
            return SUCCESS;
        }
        pos_counter += (*p)->counter;
        p = &((*p)->next);
        jmp_counter++;
    }
    return INVALID_POS;
}
int arraylist_get(ARRAYLIST *arraylist, int pos) //retorna o elemento na POSICAO indicada
{
    int jmp_counter = 0, pos_counter = 0;
    if (pos < 0 || pos > arraylist->elements)
        return INVALID_POS;

    ARRAY_ELEM **p;
    p = &arraylist->first;
    while (jmp_counter < arraylist->ar_elements)
    {
        if (pos_counter + (*p)->counter > pos)
        {
            printf("%d/%d\n", (*p)->list[pos - pos_counter].key, (*p)->list[pos - pos_counter].value);
            return SUCCESS;
        }
        pos_counter += (*p)->counter;
        p = &((*p)->next);
        jmp_counter++;
    }
    return INVALID_POS;
}
void free_arraylist(ARRAYLIST *arraylist)
{
    ARRAY_ELEM **p, **next;

    if (arraylist->first)
    {

        p = &arraylist->first;
        while ((*p)->next)
        {
            next = &((*p)->next);
            free((*p)->list);
            free(*p);
            p=next;
        }
        free(arraylist->last->list);
        free(arraylist->last);
    }
    free(arraylist);
}