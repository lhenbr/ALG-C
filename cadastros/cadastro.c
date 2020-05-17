/*Lucas Henrique Braga Martins
11275126*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cadastro.h>
#include <assert.h>

void add_reg(REGISTER_LIST *list, REG_ELEM *new)
{
    list->counter++;
    list->first = (REG_ELEM *)realloc(list->first, sizeof(REG_ELEM) * (list->counter));
    list->first[list->counter - 1] = *new;
}
void search_print(char *s_cpf, REGISTER_LIST *list)
{
    int i;
    for (i = 0; i < list->counter; i++)
    {
        if (strcmp(list->first[i].cpf, s_cpf) == 0)
        {
            printf("Primeiro Nome: %s\n", list->first[i].f_name);
            printf("Ultimo Nome: %s\n", list->first[i].l_name);
            printf("CPF: %s\n", list->first[i].cpf);
            printf("Telefone: %s\n", list->first[i].tel);
            printf("-----------------------------\n");
        }
    }
}
void dump(REGISTER_LIST *list)
{
    int i;
    for (i = 0; i < list->counter; i++)
    {
        printf("Primeiro Nome: %s\n", list->first[i].f_name);
        printf("Ultimo Nome: %s\n", list->first[i].l_name);
        printf("CPF: %s\n", list->first[i].cpf);
        printf("Telefone: %s\n", list->first[i].tel);
        printf("-----------------------------\n");
    }
}
void remove_cpf(char *s_cpf, REGISTER_LIST *list)
{
    int i, j;
    for (i = 0; i < list->counter; i++)
    {
        if (strcmp(list->first[i].cpf, s_cpf) == 0)
        { 
              list->counter--;
            memcpy(&list->first[i],&list->first[i+1],sizeof(REG_ELEM)*list->counter-i);
            
     }
    }
}
void free_list(REGISTER_LIST *list)
{
    free(list->first);
}

REG_ELEM *new_reg(REG_ELEM *new)
{
    new = (REG_ELEM *)malloc(sizeof(REG_ELEM));
    assert(new);
    scanf("%s", new->f_name);
    scanf("%s", new->l_name);
    scanf("%s", new->cpf);
    scanf("%s", new->tel);
    return new;
}