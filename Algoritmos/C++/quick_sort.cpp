#include <iostream> // Necessário para std::cout e std::cerr
#include <fstream>  // Necessário para std::ifstream
#include <string>   // Necessário para std::string
#include <vector>   // Necessário para std::vector
#include <chrono>   // Necessário para std::chrono
#include <algorithm>// Necessário para std::swap (ou se particao usar)
#include <iomanip>  // Necessário para std::fixed e std::setprecision
#include <stdexcept>// Boa prática


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
    quicksort(vetor, 0, vetor.size() - 1);
    auto fim = std::chrono::steady_clock::now();   
    
    std::chrono::duration<double> duracao = fim - inicio;

    std::cout << std::fixed << std::setprecision(9)
              << duracao.count()
              << std::endl;
        
    return 0; 
}



