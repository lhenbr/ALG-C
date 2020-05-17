/* Lucas Henrique Braga Martins
NUSP: 11275126*/
#ifndef anagrama_h_
#define anagrama_h_


typedef struct hashtable{
    int load,size; 
    unsigned char **word;
}HASHTABLE;

typedef struct group{
    int first;
    int length_w;
    int *words;
    int n_words;
}GROUP;

typedef struct c_group{
    int length;
    int number;
    int *index_first;
}C_GROUP;

HASHTABLE* create_hash(int);
void add_hash(HASHTABLE*,unsigned char*);
void free_hash(HASHTABLE*);
void quicksort_char(char*, int, int); 
GROUP* find_anagrams(HASHTABLE *, GROUP *, int *);
void print_group(GROUP ,HASHTABLE *);

int count_groups(HASHTABLE *hash, GROUP *groups, int n, C_GROUP *result);

void print_groups(HASHTABLE *hash, GROUP *groups, C_GROUP *result, int n_results, int n_groups);



#endif