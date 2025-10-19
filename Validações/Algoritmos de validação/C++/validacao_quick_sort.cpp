#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // Para std::swap

// --- Funções do Quicksort (as que você forneceu) ---
int particao(std::vector<int>& X, int p, int r) {
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

        if (i < j) {
            std::swap(X[i], X[j]);
        }
    }
    return j;
}

void quicksort(std::vector<int>& X, int p, int r) {
    int q;
    if (p < r) {
        q = particao(X, p, r);
        quicksort(X, p, q);
        quicksort(X, q + 1, r);
    }
}

// --- Funções de Leitura e Escrita de Arquivos ---
std::vector<int> lerVetorDeArquivo(const std::string& nomeDoArquivo) {
    std::ifstream arquivo(nomeDoArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada: " << nomeDoArquivo << std::endl;
        return {};
    }
    std::vector<int> vetor;
    int numero;
    while (arquivo >> numero) {
        vetor.push_back(numero);
    }
    return vetor;
}

void escreverVetorEmArquivo(const std::string& nomeDoArquivo, const std::vector<int>& vetor) {
    std::ofstream arquivo(nomeDoArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao criar o arquivo de saida: " << nomeDoArquivo << std::endl;
        return;
    }
    for (int numero : vetor) {
        arquivo << numero << "\n";
    }
}

// --- Função main adaptada para o processo em lote ---
int main() {
    std::string caminhoEntradaBase = "../../../Vetores/tamanho_100/";
    std::string caminhoSaidaBase = "../../Vetores ordenados/C++/Quick sort/";

    std::cout << "Iniciando processo de ordenacao em lote com Quicksort (C++)..." << std::endl;

    for (int i = 1; i <= 100; ++i) {
        std::string nomeArquivoEntrada = caminhoEntradaBase + "vetor_100_" + std::to_string(i) + ".txt";
        std::string nomeArquivoSaida = caminhoSaidaBase + "vetor_100_" + std::to_string(i) + ".txt";
        std::vector<int> vetor = lerVetorDeArquivo(nomeArquivoEntrada);

        if (!vetor.empty()) {
            quicksort(vetor, 0, vetor.size() - 1);
            escreverVetorEmArquivo(nomeArquivoSaida, vetor);
            std::cout << "Arquivo vetor_100_" << i << ".txt processado com sucesso." << std::endl;
        }
    }

    std::cout << "Processo concluido!" << std::endl;
    return 0;
}