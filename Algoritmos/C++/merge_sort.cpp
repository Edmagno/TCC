#include <iostream>
#include <fstream>
#include <string>
#include <filesystem> 
#include <vector>
#include <sstream>
#include <algorithm> 
#include <chrono>
#include <iomanip> 

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
    merge_sort(vetor, 0, vetor.size() - 1);
    auto fim = std::chrono::steady_clock::now();   
    
    std::chrono::duration<double> duracao = fim - inicio;

    std::cout << std::fixed << std::setprecision(9)
              << duracao.count()
              << std::endl;
        
    return 0; 
}