/*Lucas Henrique Braga Martins
11275126*/
#ifndef maze_h_
#define maze_h_

#define INVALID_CHAMBER -1
#define INVALID_SEGMENT -2
#define INVALID_START -3

typedef struct way{
    int way_id;
    struct dot *target;
    float length;
}WAY;

typedef struct dot{
    float x,y;
    int dot_id;
    int chamber;
    int exit;
    int pn; // numero de portais
    WAY **ways;
}DOT;

typedef struct maze{

DOT *dots,*start;
}MAZE;
typedef struct stack_elem{
    int n_dots;
    int *index;
    float distance;    
    DOT *next;
}STACK_ELEM;


typedef struct stack{
    int top;
    STACK_ELEM *array;
}STACK;

typedef struct result{
    int n_dots;
    int distance;
    int *index;
}RESULT;

    STACK* create_stack();
    MAZE* load_maze(int*);
    RESULT* maze_runner(STACK*,MAZE*,RESULT*,int*);
    RESULT* sort_result(RESULT*,int);
    void print_result(RESULT*,int);
    void free_stack(STACK*);
#endif