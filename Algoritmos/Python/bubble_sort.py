import sys
import time

def bubble_sort(X):
    n = len(X)
    for i in range(n):
        for j in range(0, n - i - 1):
            if X[j] > X[j + 1]:
                X[j], X[j + 1] = X[j + 1], X[j]  

def ler_vetor(nome_arquivo):
    
    with open(nome_arquivo, "r") as arquivo:
            vetor = [int(linha.strip()) for linha in arquivo]  
            return vetor

def main():
    
    nome_arquivo = sys.argv[1]

    vetor = ler_vetor(nome_arquivo)

    inicio = time.monotonic()  
    bubble_sort(vetor)    
    fim = time.monotonic()
    tempo_execucao = fim - inicio  

    print(f"{tempo_execucao}")


if __name__ == "__main__":
    main()