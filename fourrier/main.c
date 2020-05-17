/*Lucas Henrique Braga Martins
11275126*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <complex.h>
#include <fourier.h>

int main()
{
  unsigned char *result;
  double complex *complexes;
  double complex *msr;
  int n_values,C;
  unsigned char *values;
  n_values = get_values(&values);
  scanf("%d",&C);
  dft(&complexes,&values,n_values);
  msr = select_mag(n_values,C,&complexes);
  result = inverse_dft(msr,n_values);
  create_binary(result,n_values);
  //printf("%f",creal(msr[0]));
  return 0;
}