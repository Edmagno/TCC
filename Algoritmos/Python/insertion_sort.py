import sys
import time
import os 

def insertion_sort(X):
  n = len(X)
  for i in range(1, n):
    eleito = X[i]
    j = i - 1
    while j >= 0 and X[j] > eleito:
      X[j + 1] = X[j]
      j -= 1
    X[j + 1] = eleito


def ler_vetor(nome_arquivo):
    
    with open(nome_arquivo, "r") as arquivo:
            vetor = [int(linha.strip()) for linha in arquivo]  # List comprehension
            return vetor

def main():
    
    nome_arquivo = sys.argv[1]

    vetor = ler_vetor(nome_arquivo)

    inicio = time.monotonic()  
    insertion_sort(vetor)    
    fim = time.monotonic()
    tempo_execucao = fim - inicio  

    print(f"{tempo_execucao}")


if __name__ == "__main__":
    main()