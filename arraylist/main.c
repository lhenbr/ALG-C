/*Lucas Henrique Braga Martins
11275126*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "arraylist.h"

int main()
{
    int key, value,error,pos;
    char *cmd;
    ARRAYLIST *mylist = (ARRAYLIST *)calloc(1, sizeof(ARRAYLIST));
    while (strcmp(cmd, "sair"))
    {
        scanf("%s",cmd);
        if (!strcmp(cmd, "tamanho"))
        {
            arraylist_size(mylist);
        }
        if (!strcmp(cmd, "add"))
        {
            scanf("%d %d", &key, &value);
            arraylist_add(mylist, key, value);
        }
        if (!strcmp(cmd, "sub"))
        {
            scanf("%d %d", &key, &value);
            arraylist_print(arraylist_sub(mylist, key, value));
            
        }
        if (!strcmp(cmd, "set"))
        {
            scanf("%d %d %d",&pos, &key, &value);
            arraylist_set(mylist,pos, key, value);
            
        }
        if (!strcmp(cmd, "vazia"))
        {
            arraylist_empty(mylist);
        }if (!strcmp(cmd, "print"))
        {
            arraylist_print(mylist);
        }
        if (!strcmp(cmd, "contem"))
        {
            scanf("%d", &key);
        error = arraylist_contains(mylist, key);
        }
        if (!strcmp(cmd, "get"))
        {
            scanf("%d", &key);
        error = arraylist_get(mylist, key);
        }
        if (!strcmp(cmd, "indice"))
        {
            scanf("%d", &key);
        error = arraylist_index(mylist, key);
        }
        if (!strcmp(cmd, "remover"))
        {
            scanf("%d", &key);
        error = arraylist_delete(mylist, key);
        }
    }
    free_arraylist(mylist);
    return 0;
}
