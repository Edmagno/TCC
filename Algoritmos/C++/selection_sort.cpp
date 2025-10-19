#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <iomanip>


void selectionSort(std::vector<int>& vetor) {
    int n = vetor.size();
    
    int i, j, eleito, menor, pos;

    for (i = 0; i < n - 1; ++i) {
        
        eleito = vetor[i];
        menor = vetor[i + 1];
        pos = i + 1;
        
        for (j = i + 1; j < n; ++j) {
            if (vetor[j] < menor) {
                menor = vetor[j];
                pos = j;
            }
        }

        if (menor < eleito) {
            std::swap(vetor[i], vetor[pos]);
        }
    }
}

std::vector<int> lerVetorDeArquivo(const std::string& nomeDoArquivo) {
    std::ifstream arquivo(nomeDoArquivo);

    std::vector<int> vetor;
    int numero;
    while (arquivo >> numero) {
        vetor.push_back(numero);
    }

    return vetor;
}

int main(int, char *argv[]) {
    
    std::string nomeDoArquivoParaAbrir = argv[1];
    std::vector<int> vetor = lerVetorDeArquivo(nomeDoArquivoParaAbrir);

    auto inicio = std::chrono::steady_clock::now(); 
    selectionSort(vetor);
    auto fim = std::chrono::steady_clock::now();   
    
    std::chrono::duration<double> duracao = fim - inicio;

    std::cout << std::fixed << std::setprecision(9)
              << duracao.count()
              << std::endl;
        
    return 0; 
}