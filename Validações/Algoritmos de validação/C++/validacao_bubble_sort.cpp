#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // Para std::swap

// Função bubbleSort (a que você forneceu)
void bubbleSort(std::vector<int>& vetor) {
    int n = vetor.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                std::swap(vetor[j], vetor[j + 1]);
            }
        }
    }
}

// Função para ler um vetor de um arquivo (a que você forneceu)
std::vector<int> lerVetorDeArquivo(const std::string& nomeDoArquivo) {
    std::ifstream arquivo(nomeDoArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada: " << nomeDoArquivo << std::endl;
        return {}; // Retorna um vetor vazio em caso de erro
    }

    std::vector<int> vetor;
    int numero;
    while (arquivo >> numero) {
        vetor.push_back(numero);
    }
    return vetor;
}

// Nova função para escrever o vetor ordenado em um arquivo
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

// Função main adaptada para o processo em lote
int main() {
    // Caminhos relativos a partir da pasta de execução do algoritmo (CPP)
    std::string caminhoEntradaBase = "../../../Vetores/tamanho_100/";
    // Novo caminho de saída para os resultados do C++
    std::string caminhoSaidaBase = "../../Vetores ordenados/C++/Bubble sort/";

    std::cout << "Iniciando processo de ordenacao em lote com Bubble Sort (C++)..." << std::endl;

    for (int i = 1; i <= 100; ++i) {
        // Constrói os nomes dos arquivos de forma mais moderna com C++
        std::string nomeArquivoEntrada = caminhoEntradaBase + "vetor_100_" + std::to_string(i) + ".txt";
        std::string nomeArquivoSaida = caminhoSaidaBase + "vetor_100_" + std::to_string(i) + ".txt";

        std::vector<int> vetor = lerVetorDeArquivo(nomeArquivoEntrada);

        if (!vetor.empty()) {
            bubbleSort(vetor);
            escreverVetorEmArquivo(nomeArquivoSaida, vetor);
            std::cout << "Arquivo vetor_100_" << i << ".txt processado com sucesso." << std::endl;
        }
    }

    std::cout << "Processo concluido!" << std::endl;
    return 0;
}