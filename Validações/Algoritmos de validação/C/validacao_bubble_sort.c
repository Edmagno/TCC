#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

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
    
    char* caminhoSaidaBase = "../../Vetores ordenados/C/Bubble sort/";

    char nomeArquivoEntrada[256];
    char nomeArquivoSaida[256];
    
    printf("Iniciando processo de ordenacao em lote...\n");

    for (int i = 1; i <= 100; i++) {
        sprintf(nomeArquivoEntrada, "%svetor_100_%d.txt", caminhoEntradaBase, i);
        sprintf(nomeArquivoSaida, "%svetor_100_%d.txt", caminhoSaidaBase, i);

        int tamanhoVetor;
        int* vetor = lerVetor(nomeArquivoEntrada, &tamanhoVetor);

        if (vetor != NULL && tamanhoVetor > 0) {
            // ... (resto do loop)
            bubble_sort(vetor, tamanhoVetor);
            escreverVetor(nomeArquivoSaida, vetor, tamanhoVetor);
            printf("Arquivo vetor_100_%d.txt processado com sucesso.\n", i);
            free(vetor);
        }
    }
    
    printf("Processo concluido!\n");

    return 0;
}