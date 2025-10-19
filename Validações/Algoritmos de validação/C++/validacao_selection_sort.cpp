#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // Para std::swap

// --- Função do Selection Sort (a que você forneceu) ---
void selectionSort(std::vector<int>& vetor) {
    int n = vetor.size();
    int i, j, pos;
    
    for (i = 0; i < n - 1; ++i) {
        pos = i; // Assume que o elemento atual é o menor
        
        // Encontra o menor elemento no restante do vetor
        for (j = i + 1; j < n; ++j) {
            if (vetor[j] < vetor[pos]) {
                pos = j;
            }
        }

        // Se o menor elemento não for o elemento atual, troca-os
        if (pos != i) {
            std::swap(vetor[i], vetor[pos]);
        }
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
    std::string caminhoSaidaBase = "../../Vetores ordenados/C++/Selection sort/";

    std::cout << "Iniciando processo de ordenacao em lote com Selection Sort (C++)..." << std::endl;

    for (int i = 1; i <= 100; ++i) {
        std::string nomeArquivoEntrada = caminhoEntradaBase + "vetor_100_" + std::to_string(i) + ".txt";
        std::string nomeArquivoSaida = caminhoSaidaBase + "vetor_100_" + std::to_string(i) + ".txt";
        std::vector<int> vetor = lerVetorDeArquivo(nomeArquivoEntrada);

        if (!vetor.empty()) {
            selectionSort(vetor);
            escreverVetorEmArquivo(nomeArquivoSaida, vetor);
            std::cout << "Arquivo vetor_100_" << i << ".txt processado com sucesso." << std::endl;
        }
    }

    std::cout << "Processo concluido!" << std::endl;
    return 0;
}