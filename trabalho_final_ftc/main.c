#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char nomeEstado[20];
    int inicial; //1 para sim, 0 para nao
    int final;   //1 para sim, 0 para nao
} Estado;
typedef struct
{
    char elementoAlfabeto;
} Alfabeto;
typedef struct
{
    Estado *origem;
    Alfabeto *consumo;
    Estado *destino;
} transicao;

void lerafd()
{
    int qtdEstados, tamAlfabeto, qtdTransicoes, qtdFinais;
    FILE *fp = fopen("test.txt", "r");
    char ch = getc(fp);
    char linha[200];
    int indice = 0;

    //Lê os estados e armazena em estruturas
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    qtdEstados = atoi(linha);
    ch = getc(fp);
    Estado estados[qtdEstados];
    for (int i = 0; i < qtdEstados; i++)
    {
        indice = 0;
        while (ch != '\n')
        {
            linha[indice++] = ch;
            ch = getc(fp);
        }
        linha[++indice] = '\0';
        indice = 0;
        ch = getc(fp);
        strcpy(estados[i].nomeEstado, linha);
    }

    //Lê o alfabeto e armaneza em estruturas
    indice = 0;
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    tamAlfabeto = atoi(linha);
    Alfabeto alfabeto[tamAlfabeto];
    for (int i = 0; i < tamAlfabeto; i++)
    {
        alfabeto[i].elementoAlfabeto = getc(fp);
        ch = getc(fp);
    }
    ch = getc(fp);

    //Lê transicoes e armazena nas estruturas
    indice = 0;
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    qtdTransicoes = atoi(linha);
    transicao transicoes[qtdTransicoes];
    indice = 0;
    ch = getc(fp);
    for (int i = 0; i < qtdTransicoes; i++)
    {
        //Lê a linha inteira
        indice = 0;
        while (ch != '\n')
        {
            linha[indice++] = ch;
            ch = getc(fp);
        }
        linha[indice] = '\0';
        ch = getc(fp);

        //Particiona
        int j = 0;
        int k = 0;
        char aux[20];

        while (linha[j] != ' ')
            aux[k++] = linha[j++];
        aux[k] = '\0';
        for (int a = 0; a < qtdEstados; a++)
            if (strcmp(estados[a].nomeEstado, aux) == 0)
                transicoes[i].origem = &estados[a];
        j++;
        k = 0;

        while (linha[j] != ' ')
            aux[k++] = linha[j++];
        aux[k] = '\0';
        for (int a = 0; a < tamAlfabeto; a++)
            if (alfabeto[a].elementoAlfabeto == aux[0])
                transicoes[i].consumo = &alfabeto[a];
        j++;
        k = 0;

        while (linha[j] != '\0')
            aux[k++] = linha[j++];
        aux[k] = '\0';
        for (int a = 0; a < qtdEstados; a++)
            if (strcmp(estados[a].nomeEstado, aux) == 0)
                transicoes[i].destino = &estados[a];
    }

    //for (int b = 0; b < qtdEstados; b++)
    //  printf("\n%s\n", estados[b].nomeEstado);
    //for (int b = 0; b < tamAlfabeto; b++)
    //  printf("\n%c", alfabeto[b].elementoAlfabeto);
    //for (int b = 0; b < qtdTransicoes; b++)
    //  printf("\n%s - %c - %s", transicoes[b].origem->nomeEstado, transicoes[b].consumo->elementoAlfabeto, transicoes[b].destino->nomeEstado);

    //Lê o estado inicial e armaneza em estruturas
    indice = 0;
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    ch = getc(fp);
    for (int i = 0; i < qtdEstados; i++)
    {
        if (strcmp(estados[i].nomeEstado, linha) == 0)
            estados[i].inicial = 1;
        else
            estados[i].inicial = 0;
    }
    for (int i = 0; i < qtdEstados; i++)
        if (estados[i].inicial == 1)
            printf("\n%s", estados[i].nomeEstado);

    //Lê os estados finais e armaneza em estruturas
    indice = 0;
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    qtdFinais = atoi(linha);
    indice = 0;
    ch = getc(fp);
    for (int i = 0; i < qtdFinais; i++)
    {
        while (ch != '\n')
        {
            linha[indice++] = ch;
            ch = getc(fp);
        }
        linha[indice] = '\0';
        for (int i = 0; i < qtdEstados; i++)
        {
            if (strcmp(estados[i].nomeEstado, linha) == 0)
                estados[i].final = 1;
            else
                estados[i].final = 0;
        }
        indice = 0;
        ch = getc(fp);
    }
}
char delta(int transicoes[][3], char *input, int tam, int estado_atual)
{
    int letra = *input - '0';

    if (transicoes[estado_atual][letra] == -1)
    {
        return '0';
    }
    else
    {
        if (tam != 0)
        {
            return delta(transicoes, input + 1, tam - 1, transicoes[estado_atual][letra]);
        }
        else
        {
            if (transicoes[estado_atual][2] == 1)
            {
                return '1';
            }
            else
            {
                return '0';
            }
        }
    }
}

// int **complemento(int transicoes[][3], int qtd_estados)
// {
//     int i;
//     int afd_complemento[qtd_estados][3];

//     for (i = 0; i++; i < qtd_estados)
//     {
//         afd_complemento[i][0] = transicoes[i][0];
//         afd_complemento[i][1] = transicoes[i][1];
//         if (transicoes[i][2] == 1)
//         {
//             afd_complemento[i][2] == 0;
//         }
//         else
//         {
//             afd_complemento[i][2] == 1;
//         }
//     }
//     return afd_complemento;
// }

void ler_palavra(char *palavras, char *saida, int **afd)
{

    //Abertura de arquivos para leitura das palavras e saída de resultados
    FILE *arq = fopen(palavras, "rt");
    FILE *resultados = fopen(saida, "wt");

    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo com as palavras");
        return;
    }

    //Fazer um while que tem uma chamada da funcao delta, que pega cada palavra do arquivo, aplica nela e escreve o resultado na saida
}

int main(int argc, char *argv[])
{
    int matriz[2][3] = {{1, 0, 0}, {1, 0, 1}};
    char *palavra = "00010";

    //printf("%c", delta(matriz, palavra, strlen(palavra), 0));
    lerafd();
    return 0;
}
