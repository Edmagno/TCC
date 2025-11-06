#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

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
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", nomeArquivo);
        *tamanho = 0;
        return NULL;
    }

    int contador = 0;
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        contador++;
    }

    int* vetor = (int*)malloc(contador * sizeof(int));
    if (vetor == NULL) {
        printf("Erro de alocacao de memoria.\n");
        fclose(arquivo);
        *tamanho = 0;
        return NULL;
    }

    rewind(arquivo);

    for (int i = 0; i < contador; i++) {
        fscanf(arquivo, "%d", &vetor[i]);
    }

    fclose(arquivo);
    *tamanho = contador;
    return vetor;
}

void escreverVetor(const char* nomeArquivo, int vetor[], int tamanho) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de saida: %s\n", nomeArquivo);
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d\n", vetor[i]);
    }

    fclose(arquivo);
}

int main() {
    char* caminhoEntradaBase = "../../../Vetores/tamanho_100/";
    char* caminhoSaidaBase = "../../Vetores ordenados/C/Merge sort/";

    char nomeArquivoEntrada[256];
    char nomeArquivoSaida[256];
    
    printf("Iniciando processo de ordenacao em lote com Merge Sort...\n");

    for (int i = 1; i <= 100; i++) {
        sprintf(nomeArquivoEntrada, "%svetor_100_%d.txt", caminhoEntradaBase, i);
        sprintf(nomeArquivoSaida, "%svetor_100_%d.txt", caminhoSaidaBase, i);

        int tamanhoVetor;
        int* vetor = lerVetor(nomeArquivoEntrada, &tamanhoVetor);

        if (vetor != NULL && tamanhoVetor > 0) {
            merge_sort(vetor, 0, tamanhoVetor - 1); 
            escreverVetor(nomeArquivoSaida, vetor, tamanhoVetor);
            printf("Arquivo vetor_100_%d.txt processado com sucesso.\n", i);
            free(vetor);
        }
    }
    
    printf("Processo concluido!\n");

    return 0;
}