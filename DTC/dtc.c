#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>


int main(){
    int k,i,tam;
    double *vetor1,*vetor2;
    
    scanf(" %d ",&tam);

    vetor1=malloc(tam*sizeof(double));
    assert(vetor1);

    vetor2=calloc(tam,sizeof(double));
    assert(vetor2);

    for(i=0;i<tam;i++){
        scanf(" %lf",&vetor1[i]);
        
    }
    // primeiro for calcula o elemento, e o segundo faz a somatorio
    for(k=0;k<tam;k++){
        for(i=0;i<tam;i++){
            vetor2[k] += vetor1[i]*cos(M_PI*(i+0.5)*k/tam);
        }
    }
    for(i=0;i<tam;i++){
        printf("%lf\n",vetor2[i]);
    }
    return 0;
}
