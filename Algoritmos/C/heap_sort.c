#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h> 

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

void heap_sort(int X[], int tamanho) {
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

    int contador = 0;
    char linha[100]; 
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        contador++;
    }

    int* vetor = (int*)malloc(contador * sizeof(int));

    rewind(arquivo); 

    for (int i = 0; i < contador; i++) {
        fscanf(arquivo, "%d", &vetor[i]);
    }

    fclose(arquivo);
    *tamanho = contador;
    return vetor;
}

int main(int argc, char* argv[]) {
    
    char* nomeArquivo = argv[1];

    int tamanhoVetor;
    int* vetor = lerVetor(nomeArquivo, &tamanhoVetor);

    if (vetor == NULL) {
        return 1;
    }

    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    heap_sort(vetor, tamanhoVetor);

    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempoExecucao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("%f\n", tempoExecucao);

    free(vetor);
    return 0;
}