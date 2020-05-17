#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int **cria_matriz(FILE *arquivo, int *altura, int *largura);
int* busca_captcha(int *altura, int *largura, int ***mascaras, int **imagem,int *captcha);

int main()
{
    char nome_arq[20], nome_mascara[6] = "0.pgm";
    int i, **imagem, **mascaras[10], altura, largura,digitos, *captcha = NULL;
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
    captcha = busca_captcha(&altura, &largura, mascaras, imagem,&digitos);
    
    for (i = 0; i < digitos; i++)
    {
        printf("%d", digitos);
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
int* busca_captcha(int *altura, int *largura, int ***mascaras, int **imagem, int *dig_captcha)
{
    int i, j, k, x, y, px_iguais = 0, *captcha = NULL;

    for (x = 0; x < *largura - 29; x++)
    {
        for (y = 0; y < *altura - 49; y++)
        {
            //garantindo que o 1 seja a quina de um numero
            if (imagem[y][x] == 1 /*&& imagem[y-1][x]==0 && imagem[y][x-1]==0*/)

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
                        if (px_iguais > 1243)
                        {
                            printf("px_igais = %d ", px_iguais);
                            *dig_captcha++;
                            captcha = realloc(captcha, *dig_captcha * sizeof(int));
                            assert(captcha);
                            captcha[*dig_captcha - 1] = i;
                            x = 46 * *dig_captcha;
                        }
                        px_iguais = 0;
                    }

                    //tratamento para a mascara 1, ja que e a unica imagem que o vertice superior esquerdo e um 0 e nao 1
                    if (i == 0)
                    {
                        if (x > 10)
                        {
                            for (j = 0; j < 50; j++)
                            {
                                for (k = 0; k < 30; k++)
                                {
                                    if (mascaras[i][j][k] == imagem[y + j][x + k - 11])
                                    {
                                        px_iguais++;
                                    }
                                }
                            }
                            if (px_iguais > 1243)
                            {
                                printf("px_igais = %d ", px_iguais);
                                *dig_captcha++;
                                captcha = realloc(captcha, *dig_captcha * sizeof(int));
                                assert(captcha);
                                captcha[*dig_captcha - 1] = i;
                                x = 46 * *dig_captcha;
                            }
                            px_iguais = 0;
                        }
                    }
                }
        }
    }
    return captcha;
    }