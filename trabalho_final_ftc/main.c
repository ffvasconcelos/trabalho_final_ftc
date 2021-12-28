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
    char elementoAlfabeto[20];
} Alfabeto;
typedef struct
{
    char origem[20];
    char consumo[20];
    char destino[20];
} transicao;

void lerafd()
{
    int qtdEstados, tamAlfabeto, qtdTransicoes, qtdFinais;
    Estado estados[qtdEstados];
    Alfabeto alfabeto[tamAlfabeto];
    transicao transicoes[qtdTransicoes];
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
    indice = 0;
    ch = getc(fp);
    for (int i = 0; i < qtdEstados; i++)
    {
        while (ch != '\n')
        {
            linha[indice++] = ch;
            ch = getc(fp);
        }
        linha[indice] = '\0';
        strcpy(estados[i].nomeEstado, linha);
        indice = 0;
        ch = getc(fp);
    }

    //Lê o alfabeto e armaneza em estruturas
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    tamAlfabeto = atoi(linha);
    indice = 0;
    ch = getc(fp);
    for (int i = 0; i < tamAlfabeto; i++)
    {
        while (ch != '\n')
        {
            linha[indice++] = ch;
            ch = getc(fp);
        }
        linha[indice] = '\0';
        strcpy(alfabeto[i].elementoAlfabeto, linha);
        indice = 0;
        ch = getc(fp);
    }

    //Lê transicoes e armazena nas estruturas
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    qtdTransicoes = atoi(linha);
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
        while (linha[j] != ' ')
            transicoes[i].origem[k++] = linha[j++];
        transicoes[i].origem[k] = '\0';
        j++;
        k = 0;
        while (linha[j] != ' ')
            transicoes[i].consumo[k++] = linha[j++];
        transicoes[i].consumo[k] = '\0';
        j++;
        k = 0;
        while (linha[j] != '\0')
            transicoes[i].destino[k++] = linha[j++];
        transicoes[i].destino[k] = '\0';
    }

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
        if (estados[i].inicial == 0)
            printf("\n%s", estados[i].nomeEstado);

    //Lê os estados finais e armaneza em estruturas
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
            if (strcmp(estados[i].nomeEstado, linha) == 0)
                estados[i].final = 1;
        indice = 0;
        ch = getc(fp);
    }
}

int main()
{
    lerafd();
    return 0;
}
