#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void intercala(std::vector<int>& X, int inicio, int meio, int fim) {
    int i;
    int inicio_vetor1 = inicio;
    int inicio_vetor2 = meio + 1;
    
    std::vector<int> aux;
    aux.reserve(fim - inicio + 1);

    while (inicio_vetor1 <= meio && inicio_vetor2 <= fim) {
        if (X[inicio_vetor1] <= X[inicio_vetor2]) {
            aux.push_back(X[inicio_vetor1]);
            inicio_vetor1 = inicio_vetor1 + 1;
        } else {
            aux.push_back(X[inicio_vetor2]);
            inicio_vetor2 = inicio_vetor2 + 1;
        }
    }

    while (inicio_vetor1 <= meio) {
        aux.push_back(X[inicio_vetor1]);
        inicio_vetor1 = inicio_vetor1 + 1;
    }

    while (inicio_vetor2 <= fim) {
        aux.push_back(X[inicio_vetor2]);
        inicio_vetor2 = inicio_vetor2 + 1;
    }
    
    for (i = 0; i < aux.size(); i++) {
        X[inicio + i] = aux[i];
    }
}

void merge_sort(std::vector<int>& X, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2; 
        merge_sort(X, inicio, meio);
        merge_sort(X, meio + 1, fim);
        intercala(X, inicio, meio, fim);
    }
}

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

int main() {
    std::string caminhoEntradaBase = "../../../Vetores/tamanho_100/";
    std::string caminhoSaidaBase = "../../Vetores ordenados/C++/Merge sort/";

    std::cout << "Iniciando processo de ordenacao em lote com Merge Sort (C++)..." << std::endl;

    for (int i = 1; i <= 100; ++i) {
        std::string nomeArquivoEntrada = caminhoEntradaBase + "vetor_100_" + std::to_string(i) + ".txt";
        std::string nomeArquivoSaida = caminhoSaidaBase + "vetor_100_" + std::to_string(i) + ".txt";
        std::vector<int> vetor = lerVetorDeArquivo(nomeArquivoEntrada);

        if (!vetor.empty()) {
            merge_sort(vetor, 0, vetor.size() - 1);
            escreverVetorEmArquivo(nomeArquivoSaida, vetor);
            std::cout << "Arquivo vetor_100_" << i << ".txt processado com sucesso." << std::endl;
        }
    }

    std::cout << "Processo concluido!" << std::endl;
    return 0;
}