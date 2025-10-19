#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

void bubble_sort(int X[], int n) {
    int i, j, aux;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (X[j] > X[j + 1]) {
                aux = X[j];
                X[j] = X[j + 1];
                X[j + 1] = aux;
            }
        }
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

    bubble_sort(vetor, tamanhoVetor); 

    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempoExecucao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("%f\n", tempoExecucao);

    free(vetor);
    return 0;
}