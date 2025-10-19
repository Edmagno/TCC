import sys
import time

def selection_sort(X):
   
    n = len(X)
 
    for i in range(n - 1):
        eleito = X[i]
        menor = X[i + 1]
        pos = i + 1

        for j in range(i + 1, n):
            if X[j] < menor:
                menor = X[j]
                pos = j

        if menor < eleito:
            X[i], X[pos] = X[pos], X[i]


def ler_vetor(nome_arquivo):
    
    with open(nome_arquivo, "r") as arquivo:
            vetor = [int(linha.strip()) for linha in arquivo]  # List comprehension
            return vetor

def main():
    
    nome_arquivo = sys.argv[1]

    vetor = ler_vetor(nome_arquivo)

    inicio = time.monotonic()  
    selection_sort(vetor)    
    fim = time.monotonic()
    tempo_execucao = fim - inicio  

    print(f"{tempo_execucao}")


if __name__ == "__main__":
    main()