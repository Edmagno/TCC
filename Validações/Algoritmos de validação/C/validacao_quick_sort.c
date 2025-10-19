#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Adicionado para sprintf

// --- Funções do Quicksort (as que você forneceu) ---
void troca(int X[], int i, int j) {
    int aux;
    aux = X[i];
    X[i] = X[j];
    X[j] = aux;
}

int particao(int X[], int p, int r) {
    int pivo, i, j;
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

// --- Funções de Leitura e Escrita de Arquivos ---
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

// --- Função main adaptada para o processo em lote ---
int main() {
    // Caminhos relativos a partir da pasta de execução
    char* caminhoEntradaBase = "../../../Vetores/tamanho_100/";
    // Novo caminho de saída para o Quicksort
    char* caminhoSaidaBase = "../../Vetores ordenados/C/Quick sort/";

    char nomeArquivoEntrada[256];
    char nomeArquivoSaida[256];
    
    printf("Iniciando processo de ordenacao em lote com Quicksort...\n");

    for (int i = 1; i <= 100; i++) {
        sprintf(nomeArquivoEntrada, "%svetor_100_%d.txt", caminhoEntradaBase, i);
        sprintf(nomeArquivoSaida, "%svetor_100_%d.txt", caminhoSaidaBase, i);

        int tamanhoVetor;
        int* vetor = lerVetor(nomeArquivoEntrada, &tamanhoVetor);

        if (vetor != NULL && tamanhoVetor > 0) {
            // Chamada correta para o quicksort, passando os índices
            quicksort(vetor, 0, tamanhoVetor - 1);
            escreverVetor(nomeArquivoSaida, vetor, tamanhoVetor);
            printf("Arquivo vetor_100_%d.txt processado com sucesso.\n", i);
            free(vetor);
        }
    }
    
    printf("Processo concluido!\n");

    return 0;
}