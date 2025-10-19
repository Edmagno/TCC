#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm> 
#include <iomanip>   


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
    heapsort(vetor);
    auto fim = std::chrono::steady_clock::now();   
    
    std::chrono::duration<double> duracao = fim - inicio;

    std::cout << std::fixed << std::setprecision(9)
              << duracao.count()
              << std::endl;
        
    return 0; 
}
