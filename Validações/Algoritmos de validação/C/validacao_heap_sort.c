#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ajustarHeap(int X[], int i, int tamanho) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    int aux;

    if (esq < tamanho && X[esq] > X[maior]) {
        maior = esq;
    }
    if (dir < tamanho && X[dir] > X[maior]) {
        maior = dir;
    }
    if (maior != i) {
        aux = X[i];
        X[i] = X[maior];
        X[maior] = aux;
        ajustarHeap(X, maior, tamanho);
    }
}

void construirHeap(int X[], int tamanho) {
    for (int i = (tamanho / 2) - 1; i >= 0; i--) {
        ajustarHeap(X, i, tamanho);
    }
}

void heapsort(int X[], int tamanho) {
    int aux;
    construirHeap(X, tamanho);
    for (int i = tamanho - 1; i > 0; i--) {
        aux = X[0];
        X[0] = X[i];
        X[i] = aux;
        ajustarHeap(X, 0, i);
    }
}

int* lerVetor(const char* nomeArquivo, int* tamanho) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", nomeArquivo);
        *tamanho = 0;
        return NULL;
    }
    int contador = 0;
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) contador++;
    int* vetor = (int*)malloc(contador * sizeof(int));
    if (vetor == NULL) {
        fclose(arquivo);
        *tamanho = 0;
        return NULL;
    }
    rewind(arquivo);
    for (int i = 0; i < contador; i++) fscanf(arquivo, "%d", &vetor[i]);
    fclose(arquivo);
    *tamanho = contador;
    return vetor;
}

void escreverVetor(const char* nomeArquivo, int vetor[], int tamanho) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) return;
    for (int i = 0; i < tamanho; i++) fprintf(arquivo, "%d\n", vetor[i]);
    fclose(arquivo);
}

int main() {
    char* caminhoEntradaBase = "../../../Vetores/tamanho_100/";
    char* caminhoSaidaBase = "../../Vetores ordenados/C/Heap sort/";
    char nomeArquivoEntrada[256];
    char nomeArquivoSaida[256];

    printf("Iniciando processo de ordenacao em lote com Heapsort (C)...\n");

    for (int i = 1; i <= 100; i++) {
        sprintf(nomeArquivoEntrada, "%svetor_100_%d.txt", caminhoEntradaBase, i);
        sprintf(nomeArquivoSaida, "%svetor_100_%d.txt", caminhoSaidaBase, i);
        int tamanhoVetor;
        int* vetor = lerVetor(nomeArquivoEntrada, &tamanhoVetor);
        if (vetor != NULL && tamanhoVetor > 0) {
            heapsort(vetor, tamanhoVetor);
            escreverVetor(nomeArquivoSaida, vetor, tamanhoVetor);
            printf("Arquivo vetor_100_%d.txt processado com sucesso.\n", i);
            free(vetor);
        }
    }

    printf("Processo concluido!\n");
    return 0;
}