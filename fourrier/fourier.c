/*Lucas Henrique Braga Martins
11275126*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <complex.h>
#include <fourier.h>

int get_values(unsigned char **values)
{
    char *filename = malloc(20);
    FILE *file;
    int i = 0, n_elem;

    scanf(" %s", filename);
    //printf("%s", filename);

    file = fopen(filename, "rb");
    assert(file);

    *values = (unsigned char *)malloc(sizeof(unsigned char));
    while (fread(&((*values)[i]), 1, 1, file))
    {
        (*values) = (unsigned char *)realloc((*values), sizeof(unsigned char) * (i + 2));
        assert(*values);
        //printf("%u\n",(*values)[i]);
        i++;
    }
    printf("%d\n",i);
    n_elem = i;

    return n_elem;
}
void dft(double complex **complexes, unsigned char **values, int n)
{
    int i, j;
    float E, x;
    double complex ck;
    *complexes = malloc(sizeof(complex) * (n / 2) + 2);

    for (i = 0; i < (n / 2) + 1; i++)
    {
        ck = 0;
        for (j = 0; j < n; j++)
        {
            x = (2 * M_PI * i * j) / n;
            ck += ((*values)[j] * cos(x)) - ((*values)[j] * sin(x)) * I;
        }
        E = 2;
        if (i == 0)
            E = 1;
        E = E / n;
        ck = ck * E;
        (*complexes)[i] = ck;
        //printf("%f %fi\n", creal((*complexes)[i]), cimag((*complexes)[i]));
        //printf("%d", (*values)[i])
    }
}

double complex *select_mag(int n, int C, double complex **complexes)
{
    int i,rel_mag=0;
    double complex *most_significant_range = calloc((n / 2) + 1, sizeof(double complex));
    MAG *mag_vector = malloc(sizeof(MAG) * (n / 2) + 1);

    for (i = 0; i < (n / 2) + 1; i++)
    {
        mag_vector[i].value = cabsf((*complexes)[i]);
        mag_vector[i].or_position = i;
        if(mag_vector[i].value >= 0.1)
            rel_mag ++;
        //printf("...%f\n",mag_vector[i].value);
    }
    printf("%d\n",rel_mag);

    quick_sort(&mag_vector, 0, (n / 2) + 1);

    for (i = 0; i < ((n / 2) + 1) - C; i++)
    {
        //printf("%f\n",mag_vector[i].value);
        mag_vector[i].value = -1;
    }


    for (i = ((n / 2) + 1) - C; i < ((n / 2) + 1); i++)
    {
            most_significant_range[mag_vector[i].or_position] = (*complexes)[mag_vector[i].or_position];
    }

    for (i = ((n / 2) + 1);i > ((n / 2) + 1) - C; i--)
    {
       printf("%d ",(int)mag_vector[i].value);
    }
    printf("\n");
    return most_significant_range;
}
void quick_sort(MAG **mag, int left, int right)
{
    int i, j;
    float x;
    MAG y;

    i = left;
    j = right;
    x = (*mag)[(left + right) / 2].value;

    while (i <= j)
    {
        while ((*mag)[i].value < x && i < right)
        {
            i++;
        }
        while ((*mag)[j].value > x && j > left)
        {
            j--;
        }
        if (i <= j)
        {
            y = (*mag)[i];
            (*mag)[i] = (*mag)[j];
            (*mag)[j] = y;
            i++;
            j--;
        }
    }

    if (j > left)
    {
        quick_sort(mag, left, j);
    }
    if (i < right)
    {
        quick_sort(mag, i, right);
    }
}

unsigned char *inverse_dft(double complex *msr, int n)
{
    int i, j;
    unsigned char *result = malloc(sizeof(unsigned char) * n+1);
    double x, temp;
    double aux;
    for (i = 0; i < n; i++)
    {
        temp = 0;
        aux = 0;
        for (j = 0; j<(n / 2)+1; j++)
        {
            x = (i*2.0*M_PI *j)/n;
            aux += creal(msr[j])*cos(x);
            temp += cimag(msr[j])*sin(x);
        }
        aux = aux - temp;
        result[i] = round(aux);
        printf("%d\n",result[i]);
    }
    return result;
}
void create_binary(unsigned char *result,int n){
    FILE *file;
    file =fopen("r_audio.raw","wb");
    assert(file);
    
    fwrite(&result,sizeof(unsigned char),n+1,file);
    
    fclose(file);
}