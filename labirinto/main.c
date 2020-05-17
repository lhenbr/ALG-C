/*Lucas Henrique Braga Martins
11275126*/

#include <stdio.h>
#include <stdlib.h>
#include <maze.h>

int main(){
    int error=0,n_result;
    RESULT *result =malloc(sizeof(RESULT));
    STACK *stack = create_stack();
    MAZE *mymaze;
    mymaze = load_maze(&error);
    result = maze_runner(stack,mymaze,result,&n_result);
    result = sort_result(result,n_result);
    print_result(result,n_result);
    free_stack(stack);
    return 0; 
}