#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

void insertion_sort(int X[], int n) {
    int i, j, eleito;
    for (i = 1; i < n; i++) {
        eleito = X[i];
        j = i - 1;

        while (j >= 0 && X[j] > eleito) {
            X[j + 1] = X[j];
            j = j - 1;
        }
        X[j + 1] = eleito;
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

int main(int, char* argv[]) {
   
    char* nomeArquivo = argv[1];

    int tamanhoVetor;
    int* vetor = lerVetor(nomeArquivo, &tamanhoVetor);

    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    insertion_sort(vetor, tamanhoVetor); 

    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempoExecucao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("%f\n", tempoExecucao);

    free(vetor);
    return 0;
}