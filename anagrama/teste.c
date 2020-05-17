#include <stdio.h>
#include <string.h>

void quicksort_char(char *arr, int low, int high); //função para ordernar lexograficamente as palavras e facilitar a comparação
int main(){
char str1[10] ="baceda",str2[10] = "aabcde";

    quicksort_char(str1, 0, strlen(str1) - 1);
    if (strcmp(str1, str2))
    {
        printf("0");
    }
    else
    printf("1");
}
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