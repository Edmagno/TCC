#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <stdint.h> 

void troca(int X[], int i, int j) {
    int aux;
    aux = X[i]; 
    X[i] = X[j]; 
    X[j] = aux; 
}


int particao(int X[], int p, int r) {
    int pivo , i,  j;
    pivo = X[(p + r) / 2];
    i = p - 1; 
    j = r + 1; 

    while (i < j) { 
        do {
            j = j - 1;
        } while (X[j] > pivo);
        do {
            i = i + 1;
        } while (X[i] < pivo);

        if (i < j)
        troca(X, i, j);
    }
    return j;
}

void quicksort(int X[], int p, int r) {
    int q;
    if (p < r) {
        q = particao(X, p, r);
        quicksort(X, p, q);
        quicksort(X, q + 1, r);
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
    quicksort(vetor, 0, tamanhoVetor - 1);
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempoExecucao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("%f\n", tempoExecucao);

    free(vetor); 
    return 0; 
}