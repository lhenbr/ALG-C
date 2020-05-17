#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

int partition(char *arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort_char(char *arr, int low, int high) //função para ordernar lexograficamente as palavras e facilitar a comparação
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quicksort_char(arr, low, pi - 1);
        quicksort_char(arr, pi + 1, high);
    }
}
int main()
{
    char *str1="abcd",*str2= "abdc";
    char *t_str1 = malloc(strlen(str1));
    strcpy(t_str1,str1);
    char *t_str2 = malloc(strlen(str2));
    strcpy(t_str2,str2);
    quicksort_char(t_str1, 0, strlen(t_str1) - 1);
    quicksort_char(t_str2, 0, strlen(t_str2) - 1);
    if (!strcmp(t_str1, t_str2))
    {
        printf("1");
    }
    else
    printf("0");
    return 1;
}