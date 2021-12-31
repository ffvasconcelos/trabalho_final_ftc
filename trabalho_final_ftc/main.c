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
typedef struct
{
    Estado *estados;
    Alfabeto *alfabeto;
    transicao *transicoes;
} AFD;
char *stringFinais(AFD afd, int qtdEstados)
{
    char *str;
    for (int i = 0; i < qtdEstados; i++)
        if (afd.estados[i].final == 1)
        {
            str = (char *)malloc(strlen(afd.estados[i].nomeEstado) * sizeof(char));
            strcat(str, afd.estados[i].nomeEstado);
            strcat(str, " ");
        }
    return str;
}
void lerafd(int *qtdEstados, int *tamAlfabeto, int *qtdTransicoes, int *qtdFinais, AFD *afd)
{
    FILE *fp = fopen("test2.txt", "r");
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
    *qtdEstados = atoi(linha);
    ch = getc(fp);
    //Estado estados[*qtdEstados];
    afd->estados = (Estado *)malloc(*qtdEstados * sizeof(Estado));
    for (int i = 0; i < *qtdEstados; i++)
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
        strcpy(afd->estados[i].nomeEstado, linha);
    }

    //Lê o alfabeto e armaneza em estruturas
    indice = 0;
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    *tamAlfabeto = atoi(linha);
    afd->alfabeto = (Alfabeto *)malloc(*tamAlfabeto * sizeof(Alfabeto));
    for (int i = 0; i < *tamAlfabeto; i++)
    {
        afd->alfabeto[i].elementoAlfabeto = getc(fp);
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
    *qtdTransicoes = atoi(linha);
    afd->transicoes = (transicao *)malloc(*qtdTransicoes * sizeof(transicao));
    indice = 0;
    ch = getc(fp);
    for (int i = 0; i < *qtdTransicoes; i++)
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
        for (int a = 0; a < *qtdEstados; a++)
            if (strcmp(afd->estados[a].nomeEstado, aux) == 0)
                afd->transicoes[i].origem = &afd->estados[a];
        j++;
        k = 0;

        while (linha[j] != ' ')
            aux[k++] = linha[j++];
        aux[k] = '\0';
        for (int a = 0; a < *tamAlfabeto; a++)
            if (afd->alfabeto[a].elementoAlfabeto == aux[0])
                afd->transicoes[i].consumo = &afd->alfabeto[a];
        j++;
        k = 0;

        while (linha[j] != '\0')
            aux[k++] = linha[j++];
        aux[k] = '\0';
        for (int a = 0; a < *qtdEstados; a++)
            if (strcmp(afd->estados[a].nomeEstado, aux) == 0)
                afd->transicoes[i].destino = &afd->estados[a];
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
    for (int i = 0; i < *qtdEstados; i++)
    {
        if (strcmp(afd->estados[i].nomeEstado, linha) == 0)
            afd->estados[i].inicial = 1;
        else
            afd->estados[i].inicial = 0;
    }
    //Lê os estados finais e armaneza em estruturas
    indice = 0;
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    *qtdFinais = atoi(linha);
    indice = 0;
    ch = getc(fp);
    for (int i = 0; i < *qtdFinais; i++)
    {
        while (ch != '\n')
        {
            linha[indice++] = ch;
            ch = getc(fp);
        }
        linha[indice] = '\0';
        for (int i = 0; i < *qtdEstados; i++)
        {
            if (strcmp(afd->estados[i].nomeEstado, linha) == 0)
                afd->estados[i].final = 1;
            else
                afd->estados[i].final = 0;
        }
        indice = 0;
        ch = getc(fp);
    }
}

void escreveDot(char nome[], int qtdTrasicoes, AFD afd, int qtdEstados)
{
    char *str = stringFinais(afd, qtdEstados);
    FILE *arq = fopen(nome, "w");
    if (arq != NULL)
    {
        fprintf(arq, "digraph finite_state_machine {\n"
                     "\trankdir=LR;\n\tsize=\"10\"\n"
                     "\tnode [shape = doublecircle]; %s;",
                str);
        //funçao que escreve valores finais
        fprintf(arq, "\n\tnode [shape = circle]");
        for (int i = 0; i < qtdTrasicoes; i++)
            fprintf(arq, "\n\t%s -> %s [label = %c ];", afd.transicoes[i].origem, afd.transicoes[i].destino, afd.transicoes[i].consumo->elementoAlfabeto);
        fprintf(arq, "\n\t}");
    }
    fclose(arq);
}
char delta(transicao* transicoes, int qtd_transicoes, char *input, int tam, Estado* estado_atual)
{
    int i;
    transicao tran;

    if(tam != 0) {
        for(i = 0; i < qtd_transicoes; i++){
        tran = *(transicoes + i);
        if(tran.origem == estado_atual && tran.consumo == *input) {
            return delta(transicoes, qtd_transicoes, input + 1, tam - 1, tran.destino);
        }
    }
        return '0';
    } else {
        if(estado_atual->final == 1){
            return '1';
        } else {
            return '0';
        }
    }
}

Estado* complemento(Estado* estados, int qtd_estados) {
    int i;
    Estado saida[qtd_estados];
    Estado est;

    for(i = 0;i < qtd_estados; i++) {
        est = *(estados + i);
        strcpy(saida[i].nomeEstado, est.nomeEstado);
        saida[i].inicial = est.inicial;
        if(est.final == 1) {
            saida[i].final = 0;
        } else {
            saida[i].final = 1;
        }
    }

    return saida;
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
    //int matriz[2][3] = {{1, 0, 0}, {1, 0, 1}};
    //char *palavra = "00010";

    //printf("%c", delta(matriz, palavra, strlen(palavra), 0));
    int qtdEstados, tamAlfabeto, qtdTransicoes, qtdFinais;
    AFD afd;
    lerafd(&qtdEstados, &tamAlfabeto, &qtdTransicoes, &qtdFinais, &afd);
    escreveDot("nome.dot", qtdTransicoes, afd, qtdEstados);
    return 0;
}
