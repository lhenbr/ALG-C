/*Lucas Henrique Braga Martins
11275126*/

#include <stdlib.h>
#include <stdio.h>
#include "cadastro.h"
#include <string.h>


int main(){
    char *temp;
    REG_ELEM *new;
    REGISTER_LIST *list;
    temp =(char*)malloc(sizeof(char)*20);
    list=(REGISTER_LIST*)calloc(1,sizeof(REGISTER_LIST));
    
while( strcmp(temp,"sair")!=0){
    //printf("entrou no loop");
    scanf("%s",temp);
   if(strcmp(temp,"cadastrar")==0){
       //printf("cadastro");
       new = new_reg(new);
       //printf("criou novo elemneto");
       add_reg(list,new);
   } 
 if(strcmp(temp,"buscar")==0){
  //printf("busca");
     scanf("%s",temp);
     search_print(temp,list);
   } 
 if(strcmp(temp,"dump")==0){
     //printf("dump");
     dump(list);
   } 
 if(strcmp(temp,"remover")==0){
//printf("remove_cpfr");
scanf("%s",temp);
remove_cpf(temp,list);
   } 
}
//printf("saiu");
free_list(list);



    return 0;
}