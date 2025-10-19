import sys 
import time 

def troca(X, i, j):
    aux = X[i]
    X[i] = X[j]
    X[j] = aux

def particao(X, p, r):
 
    pivo = X[(p + r) // 2] 
    i = p - 1
    j = r + 1

    while i < j:
        while True:
            j = j - 1
            if not (X[j] > pivo):
                break
        
        while True:
            i = i + 1
            if not (X[i] < pivo):
                break

        if i < j:
            troca(X, i, j)
            
    return j

def quicksort(X, p, r):
    if p < r:
        q = particao(X, p, r)
        quicksort(X, p, q)
        quicksort(X, q + 1, r)

def ler_vetor(nome_arquivo):
    
    with open(nome_arquivo, "r") as arquivo:
            vetor = [int(linha.strip()) for linha in arquivo]  # List comprehension
            return vetor

def main():
    
    nome_arquivo = sys.argv[1]

    vetor = ler_vetor(nome_arquivo)

    inicio = time.monotonic()  
    quicksort(vetor)    
    fim = time.monotonic()
    tempo_execucao = fim - inicio  

    print(f"{tempo_execucao}")


if __name__ == "__main__":
    main()