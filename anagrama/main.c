/* Lucas Henrique Braga Martins
NUSP: 11275126*/

#include <stdio.h>
#include <stdlib.h>
#include "anagrama.h"
#include <assert.h>
#include <string.h>

int main()
{
    int n_groups =0,n_results;
    char str[20], filename[20];
    HASHTABLE *hash;
    GROUP *group = NULL;
    C_GROUP  *result;
    hash = create_hash(500009);
    //load from txt
    FILE *file;
    scanf(" %s", filename);
    file = fopen(filename, "r");
    assert(file);
    while (1==fscanf(file," %s", str))
    {
        add_hash(hash, str);
    }
    fclose(file);
    group = find_anagrams(hash,group,&n_groups);
    n_results = count_groups(hash,group,n_groups,result);
    //print_groups(hash,group,result,n_results,n_groups);
    //free_hash(hash);
   // free(group);
   // free(result);
    return 0;
}