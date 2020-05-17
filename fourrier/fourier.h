/*Lucas Henrique Braga Martins
11275126*/
#ifndef fourier_h
#define fourier_h
#include <complex.h>


#define SUCCESS 1;

struct mag{
    float value;
    int or_position;
};
typedef struct mag MAG;


int get_values(unsigned char**);
void dft(double complex **,unsigned char**,int);
double complex* select_mag(int,int,double complex**);
void quick_sort( MAG **,int,int);
unsigned char* inverse_dft(double complex *msr,int n);
void create_binary(unsigned char*,int);





#endif
