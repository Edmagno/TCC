#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#include <chrono>    
#include <iomanip>  

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
    bubbleSort(vetor);
    auto fim = std::chrono::steady_clock::now();   
    
    std::chrono::duration<double> duracao = fim - inicio;

    std::cout << std::fixed << std::setprecision(9)
              << duracao.count()
              << std::endl;
        
    return 0; 
}