#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem> 
#include <algorithm>  

void ajustarHeap(std::vector<int>& X, int tamanho, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < tamanho && X[esq] > X[maior]) {
        maior = esq;
    }

    if (dir < tamanho && X[dir] > X[maior]) {
        maior = dir;
    }

    if (maior != i) {
        std::swap(X[i], X[maior]);
        ajustarHeap(X, tamanho, maior);
    }
}

void heapsort(std::vector<int>& X) {
    int n = X.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        ajustarHeap(X, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(X[0], X[i]);
        ajustarHeap(X, i, 0);
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
    std::string caminhoSaidaBase = "../../Vetores ordenados/C++/Selection sort/";

    std::cout << "Iniciando processo de ordenacao em lote com Selection Sort (C++)..." << std::endl;

    for (int i = 1; i <= 100; ++i) {
        std::string nomeArquivoEntrada = caminhoEntradaBase + "vetor_100_" + std::to_string(i) + ".txt";
        std::string nomeArquivoSaida = caminhoSaidaBase + "vetor_100_" + std::to_string(i) + ".txt";
        std::vector<int> vetor = lerVetorDeArquivo(nomeArquivoEntrada);

        if (!vetor.empty()) {
            heapsort(vetor);
            escreverVetorEmArquivo(nomeArquivoSaida, vetor);
            std::cout << "Arquivo vetor_100_" << i << ".txt processado com sucesso." << std::endl;
        }
    }

    std::cout << "Processo concluido!" << std::endl;
    return 0;
}