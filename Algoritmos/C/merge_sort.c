#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

void intercala(int X[], int inicio, int meio, int fim) {
    int i;
    int inicio_vetor1, inicio_vetor2, poslivre;
    int tamanho = fim - inicio + 1;
    int *aux = (int*) malloc(tamanho * sizeof(int));

    inicio_vetor1 = inicio;
    inicio_vetor2 = meio + 1;
    poslivre = 0;


    while (inicio_vetor1 <= meio && inicio_vetor2 <= fim) {
        if (X[inicio_vetor1] <= X[inicio_vetor2]) {
            aux[poslivre] = X[inicio_vetor1];
            inicio_vetor1 = inicio_vetor1 + 1;
        } else {
            aux[poslivre] = X[inicio_vetor2];
            inicio_vetor2 = inicio_vetor2 + 1;
        }
        poslivre = poslivre + 1;
    }

    while (inicio_vetor1 <= meio) {
        aux[poslivre] = X[inicio_vetor1];
        poslivre = poslivre + 1;
        inicio_vetor1 = inicio_vetor1 + 1;
    }

    while (inicio_vetor2 <= fim) {
        aux[poslivre] = X[inicio_vetor2];
        poslivre = poslivre + 1;
        inicio_vetor2 = inicio_vetor2 + 1;
    }
    
    for (i = 0; i < tamanho; i++) {
        X[inicio + i] = aux[i];
    }
    
    free(aux);
}


void merge_sort(int X[], int inicio, int fim) {
    int meio;
    if (inicio < fim) {
        meio = inicio + (fim - inicio) / 2; 
        merge_sort(X, inicio, meio);
        
        merge_sort(X, meio + 1, fim);
        
        intercala(X, inicio, meio, fim);
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

    merge_sort(vetor, 0, tamanhoVetor - 1);

    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempoExecucao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("%f\n", tempoExecucao);

    free(vetor);
    return 0;
}
