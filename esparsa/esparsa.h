#ifndef _esparca
#define _esparca

#define SUCCESS          0
#define INVALID_SPARSE  -1
#define INVALID_POS     -2
#define NOT_FOUND       -3

typedef struct sparse_elem {
    int row,col;
    double elem;
    struct sparse_elem *rigth,*bottom;
}S_ELEM;

typedef struct sparse {
    int nrows, ncols;
    double constant;
    S_ELEM **row_index,**col_index;
}SPARSE;

SPARSE* sparse_create(int,int,double);
int sparse_put(SPARSE* ,int,int,double);
double sparse_get(SPARSE*,int,int);
int sparse_free(SPARSE*);
int sum_sparse(SPARSE*,SPARSE*);
int mult_sparse(SPARSE*,SPARSE*);

#endif //_esparca
