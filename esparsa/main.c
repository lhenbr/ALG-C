#include <esparsa.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(){
    int nrows,ncols,row,col,erro;
    char op;
    double value;
    SPARSE *s1 = NULL,*s2 = NULL;
    

    scanf("%c",&op);
    scanf(" %d",&nrows);
    if( nrows == -1) 
        scanf(" %d %d",&nrows,&ncols);

    s1 = sparse_create(nrows,ncols,0);
    assert(s1);

    while(1){
        scanf(" %d",&row);
        if(row == -1)
        break;
        scanf("%d %le",&col,&value);
        erro = sparse_put(s1,row,col,value);
    }
    
    scanf(" %d %d",&nrows,&ncols);

    s2 = sparse_create(nrows,ncols,0);
    assert(s2);

    while(!feof(stdin)){
        scanf(" %d",&row);
        if(row == -1)
        break;
        scanf("%d %le",&col,&value);
        erro = sparse_put(s2,row,col,value);
    }
    
    if(op =='A')
    erro = sum_sparse(s1,s2);
    
    else if(op =='M')
    erro = mult_sparse(s1,s2);



sparse_free(s1);
sparse_free(s2);
}