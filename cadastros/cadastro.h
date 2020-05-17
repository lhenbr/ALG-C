/*Lucas Henrique Braga Martins
11275126*/
#ifndef CADASTROS
#define CADASTROS

struct reg_elem{
    char f_name[16];
    char l_name[16];
    char cpf[12];
    char tel[21];
};
typedef struct reg_elem REG_ELEM;

struct register_list{
    REG_ELEM *first;
    int counter;
};
typedef struct register_list REGISTER_LIST;

//HEADERS

void add_reg(REGISTER_LIST*,REG_ELEM*);
void search_print(char*,REGISTER_LIST*);
void dump(REGISTER_LIST*);
void remove_cpf(char*,REGISTER_LIST*);
void free_list(REGISTER_LIST*);
REG_ELEM* new_reg(REG_ELEM*);

#endif
