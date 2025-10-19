#include <iostream>
#include <fstream>
#include <string>
#include <filesystem> 
#include <vector>
#include <sstream>
#include <algorithm> 
#include <chrono>
#include <iomanip> 


void insertionSort(std::vector<int>& vetor) {
    int n = vetor.size();

    for (int i = 1; i < n; ++i) {
        int eleito = vetor[i]; 
        int j = i - 1;

        while (j >= 0 && vetor[j] > eleito) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = eleito;
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
    insertionSort(vetor);
    auto fim = std::chrono::steady_clock::now();   
    
    std::chrono::duration<double> duracao = fim - inicio;

    std::cout << std::fixed << std::setprecision(9)
              << duracao.count()
              << std::endl;
        
    return 0; 
}