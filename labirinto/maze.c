/*Lucas Henrique Braga Martins
11275126*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <maze.h>
#include <math.h>
#include <string.h>

void add_chamber_dot(MAZE *mymaze, int index, int exit)
{
    mymaze->dots[index + 1].chamber = 1;
    mymaze->dots[index + 1].exit = exit;
}
void add_segment(MAZE *mymaze, int start, int end, int i)
{
    float xs, xe, ys, ye, length; //x,y do start e x,y do end
    int pn;
    mymaze->dots[start + 1].pn++;
    pn = mymaze->dots[start + 1].pn;
    mymaze->dots[start + 1].ways = malloc(sizeof(WAY *) * pn);
    mymaze->dots[start + 1].ways[pn - 1]->way_id = i;
    mymaze->dots[start + 1].ways[pn - 1]->target = &(mymaze->dots[end + 1]);

    ys = mymaze->dots[start + 1].y;
    xs = mymaze->dots[start + 1].x;
    ye = mymaze->dots[end + 1].y;
    xe = mymaze->dots[end + 1].x;
    length = sqrt(pow(xe - xs, 2) + pow(ye - ys, 2));
    mymaze->dots[start + 1].ways[pn - 1]->length = length;
}

MAZE *load_maze(int *error)
{
    int dn, cn, sn, i, dot, exit, s1b, s1e, start;
    MAZE *mymaze;
    mymaze = calloc(sizeof(MAZE), 1);
    scanf("%d", &dn);
    mymaze->dots = malloc(sizeof(DOT) * dn);
    for (i = 1; i <= dn; i++)
    {
        scanf("%f %f", &mymaze->dots[i].x, &mymaze->dots[i].y);
        mymaze->dots[i].dot_id = i;
    }
    scanf("%d", &cn);
    for (i = 1; i <= cn; i++)
    {
        scanf("%d %d", &dot, &exit);
        if (0 < dot && dot <= dn) //teste de integridade
            add_chamber_dot(mymaze, dot, exit);
        else
            *error = INVALID_CHAMBER;
    }
    scanf("%d", &sn);
    for (i = 1; i <= sn; i++)
    {
        scanf("%d %d", &s1b, &s1e);
        if (0 < s1b && s1b < dn && 0 < s1e && s1e < dn) //essa verificação impede que portais inativos sejam adicionados;
        {
            add_segment(mymaze, s1b, s1e, i);
        }
        else
            *error = INVALID_SEGMENT;
    }
    scanf("%d", &start);
    if (0 < start && start <= dn && mymaze->dots[start + 1].exit)
        mymaze->start = &(mymaze->dots[start + 1]);
    else
        *error = INVALID_START;
    return mymaze;
}

//STACK
STACK *create_stack()
{
    STACK *stack = malloc(sizeof(STACK) * 1);
    stack->top = -1;
    return stack;
}
int is_empty(STACK *stack)
{
    if (stack->top == -1)
        return 0;
    else
        return 1;
}
void push(STACK *stack, STACK_ELEM *item)
{
    stack->top++;
    stack->array = realloc(stack, sizeof(STACK_ELEM) * (stack->top + 1));
    stack->array[stack->top] = *item;
}
STACK_ELEM *pop(STACK *stack)
{
    STACK_ELEM *pop;
    pop = &(stack->array[stack->top--]);
    return pop;
}

void free_stack(STACK *stack)
{
    free(stack->array);
    free(stack);
}
STACK_ELEM *create_stack_elem_start(WAY *way, DOT *dot)
{
    STACK_ELEM *new = calloc(sizeof(STACK_ELEM), 1);
    new->distance += way->length;
    new->n_dots++;
    new->index = realloc(new->index, sizeof(int) * new->n_dots);
    new->index[new->n_dots - 1] = dot->dot_id;
    new->next = (way->target);
    return new;
}
STACK_ELEM *create_stack_elem(WAY *way, DOT *dot, STACK_ELEM *elem)
{
    elem->n_dots++;
    elem->index = realloc(elem->index, sizeof(int) * elem->n_dots);
    elem->index[elem->n_dots - 1] = dot->dot_id;
    elem->distance += way->length;
    elem->next = way->target;
    return elem;
}
int have_been_here(DOT *dot, STACK_ELEM *elem)
{ //função que evita o programa de andar em circulos, se o resultado já passou por este ponto, ele é descartado
    int i;
    for (i = 0; i < elem->n_dots; i++)
    {
        if (elem->index[i] == dot->dot_id)
            return 1;
    }
    return 0;
}

RESULT *maze_runner(STACK *stack, MAZE *maze, RESULT *result, int *n_result)
{
    int i;
    n_result = 0;
    DOT **p;
    STACK_ELEM *out;
    p = &maze->start;
    for (i = 0; i < (*p)->pn; i++)
    {
        push(stack, create_stack_elem_start((*p)->ways[i], *p));
    }
    while (is_empty(stack))
    {
        out = pop(stack);
        p = &(out->next);
        if (have_been_here((*p), out))
        {
        } //se o caminho volta a um ponto, descarta e vai para o proximo stack elem

        else
        {
            for (i = 0; i < (*p)->pn; i++)
                push(stack, create_stack_elem((*p)->ways[i], (*p),out));
        if((*p)->exit)//se o ponto possui saida,salva o resultado e continua buscando
        {
                    n_result++;
                    result = realloc(result, sizeof(RESULT) * (*n_result));
                    assert(result);
                    result[*n_result - 1].n_dots = out->n_dots;
                    result[*n_result - 1].index = malloc(sizeof(int) * out->n_dots);
                    for (i = 0; i < out->n_dots; i++)
                    {
                        result->index[i] = out->index[i];
                    }
                    result[*n_result - 1].distance = (int)out->distance;

        }
        }
    }
    free_stack(stack);
    return result;
}
//ordenação dos resultados
void swap(RESULT *a, RESULT *b)
{
    RESULT temp = *a;
    *a = *b;
    *b = temp;
}
int partition_distance(RESULT *arr, int low, int high)
{
    RESULT pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].distance < pivot.distance)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort_distance(RESULT *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition_distance(arr, low, high);

        quickSort_distance(arr, low, pi - 1);
        quickSort_distance(arr, pi + 1, high);
    }
}

int partition_n_dots(RESULT *arr, int low, int high)
{
    RESULT pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].n_dots < pivot.n_dots)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort_n_dots(RESULT *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition_n_dots(arr, low, high);

        quickSort_n_dots(arr, low, pi - 1);
        quickSort_n_dots(arr, pi + 1, high);
    }
}
int partition_index(RESULT *arr, int low, int high)
{
    int k;
    RESULT pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        for (k = 0; k < pivot.n_dots; k++)//compara os indices um a um,se pivot maior faz o swap, caso contrario não faz nada 
        {
            if (arr[j].index[k] > pivot.index[k])
                break;

            else if (arr[j].index[k] < pivot.index[k])
            {
                i++;
                swap(&arr[i], &arr[j]);
                break;
            }
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort_index(RESULT *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition_index(arr, low, high);

        quickSort_index(arr, low, pi - 1);
        quickSort_index(arr, pi + 1, high);
    }
}
void print_result(RESULT *result, int n_result){
    int i,j;
    for(i=0;i<n_result;i++){
        printf("%d ",result[i].n_dots);
        for(j=0;j<result[i].n_dots;j++){
            printf("%d ",result[i].index[j]);
        }
        printf("%d",(int)result[i].distance);
    }
}
RESULT* sort_result(RESULT *result,int n_result){
    int i,j,d_count=0;
    quickSort_distance(result,0,n_result-1);
   
    for(i=0;i<n_result;i++){
         d_count=0;
        for(j=0;j<n_result;j++){
            if(result[i].distance == result[j].distance)
                d_count++;
            else
            {
                if(d_count<1){
                    quickSort_n_dots(result,i,j-1);
                }
            }
            
        }
    }

    for(i=0;i<n_result;i++){
         d_count=0;
        for(j=0;j<n_result;j++){
            if(result[i].n_dots == result[j].n_dots)
                d_count++;
            else
            {
                if(d_count<1){
                    quickSort_index(result,i,j-1);
                }
            }
            
        }
    }
return result;
}
//codigos da stack e do quicksort adaptados do site geeksforgeeks.org