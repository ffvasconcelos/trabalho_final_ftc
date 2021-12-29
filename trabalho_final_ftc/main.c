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

char delta(int transicoes[][3], char* input, int tam, int estado_atual) {
    int letra = *input - '0';

    if(transicoes[estado_atual][letra] == -1) {
        return '0';
    } else {
        if(tam != 0) {
            return delta(transicoes, input + 1, tam - 1, transicoes[estado_atual][letra]);
        } else {
            if(transicoes[estado_atual][2] == 1) {
                return '1';
            } else {
                return '0';
            }
        }
    }
}

int** complemento(int transicoes[][3], int qtd_estados) {
    int i;
    int afd_complemento[qtd_estados][3];

    for(i = 0; i++; i < qtd_estados){
        afd_complemento[i][0] = transicoes[i][0];
        afd_complemento[i][1] = transicoes[i][1];
        if(transicoes[i][2] == 1) {
            afd_complemento[i][2] == 0;
        } else {
            afd_complemento[i][2] == 1;
        }
    }
    return afd_complemento;
}

void ler_palavra(char* palavras, char* saida, int** afd) {

    //Abertura de arquivos para leitura das palavras e saída de resultados
    FILE *arq = fopen(palavras, "rt");
    FILE *resultados = fopen(saida, "wt");

    if(arq == NULL){
        printf("Erro ao abrir arquivo com as palavras");
        return;
    }

    //Fazer um while que tem uma chamada da funcao delta, que pega cada palavra do arquivo, aplica nela e escreve o resultado na saida

}

int main(int argc, char* argv[])
{
    int matriz[2][3] = {{1, 0, 0}, {1, 0, 1}};
    char* palavra = "00010";

    //printf("%c", delta(matriz, palavra, strlen(palavra), 0));
    //lerafd();
    return 0;
}
