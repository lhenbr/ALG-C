//o processo para identificar os digitos do captcha consiste em comparar partes da matriz com as mascaras dos digitos previamente carregadas no programa, para não haver interferencia do desfoque, 
//é considerado igual uma similariedade menor que 100%



#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int **cria_matriz(FILE *arquivo, int *altura, int *largura);
void busca_captcha(int *altura, int *largura, int ***mascaras, int **imagem);

int main()
{
    char nome_arq[20], nome_mascara[6] = "0.pgm";
    int i, **imagem, **mascaras[10], altura, largura;
    FILE *arquivo;
    //salva as mascaras dos digitos em um vetor*** para comparacoes futuras
    for (i = 0; i <= 9; i++)
    {

        arquivo = fopen(nome_mascara, "r");
        assert(arquivo);

        mascaras[i] = cria_matriz(arquivo, &altura, &largura);
        nome_mascara[0] = i + 1 + '0';
        assert(mascaras[i]);
        fclose(arquivo);
    }

    scanf(" %s", nome_arq);

    arquivo = fopen(nome_arq, "r");
    assert(arquivo);
    imagem = cria_matriz(arquivo, &altura, &largura);
    assert(imagem);
    busca_captcha(&altura, &largura, mascaras, imagem);
    for(i=0;i<altura;i++){
    free(imagem[i]);
    }
    for(i=0;i<=9;i++){
        free(mascaras[i]);
    }
    return 0;
}

int **cria_matriz(FILE *arquivo, int *altura, int *largura)
{
    char tipo[2];
    int i, j, temp;
    fscanf(arquivo, "%s ", tipo);
    fscanf(arquivo, "%d ", &*largura);
    fscanf(arquivo, "%d ", &*altura);
    int **vetor = malloc(*altura * sizeof(int *));
    assert(vetor);
    for (i = 0; i < *altura; i++)
    {
        vetor[i] = malloc(*largura * sizeof(int));
        assert(vetor[i]);
    }

    for (i = 0; i < *altura; i++)
    {
        for (j = 0; j < *largura; j++)
        {
            fscanf(arquivo, " %d", &temp);
            vetor[i][j] = temp;
        }
    }
    return vetor;
}
void busca_captcha(int *altura, int *largura, int ***mascaras, int **imagem)
{
    int i, j, k, x, y, px_iguais = 0, *captcha = NULL, dig_captcha = 0;

   //optei pela leitura da largura primeiro,pois com excessão do 1 ,todos os numeros tem 1 no vertice superior esquerdo
    for (x = 0; x < *largura - 29; x++)
    {
        for (y = 0; y < *altura - 49; y++)
        {
            //quando encontrar 1, comparar com as mascaras
            if (imagem[y][x] == 1 )

                for (i = 0; i <= 9; i++)
                {
                    if (i != 1)
                    {
                        for (j = 0; j < 50; j++)
                        {
                            for (k = 0; k < 30; k++)
                            {
                                if (mascaras[i][j][k] == imagem[y + j][x + k])
                                {
                                    px_iguais++;
                                }
                            }
                        }
                        if (px_iguais > 1329)
                        {
                            //printf("px_igais = %d ", px_iguais);
                            dig_captcha++;
                            captcha = realloc(captcha, dig_captcha * sizeof(int));
                            assert(captcha);
                            captcha[dig_captcha - 1] = i;
                            x = 46 * dig_captcha;
                        }
                        px_iguais = 0;
                    }

                    //tratamento para a mascara 1, ja que e a unica imagem que o vertice superior esquerdo e um 0 e nao 1
                    if (i == 1)
                    {
                        if (x > 10)
                        
                       {
                           
                            for (j = 0; j < 50; j++)
                            {
                                for (k = 0; k < 30; k++)
                                {
                                    //leitura da imagem deslocada para compensar os zeros em volta do um
                                    if (mascaras[i][j][k] == imagem[y + j][x + k-10])
                                    {
                                        px_iguais++;
                                    }
                                }
                            }
                            if (px_iguais > 1300)
                            {
                                
                                dig_captcha++;
                                captcha = realloc(captcha, dig_captcha * sizeof(int));
                                assert(captcha);
                                captcha[dig_captcha - 1] = i;
                                x = 46 * dig_captcha;
                            }
                            px_iguais = 0;
                        }
                    }
                }
        }
    }

    for (i = 0; i < dig_captcha; i++)
    {
        printf("%d", captcha[i]);
    }
    free(captcha);
}