import sys
import time


def intercala(X, inicio, meio, fim):
   
    aux = []
    
    inicio_vetor1 = inicio
    inicio_vetor2 = meio + 1

    while inicio_vetor1 <= meio and inicio_vetor2 <= fim:
        if X[inicio_vetor1] <= X[inicio_vetor2]:
            aux.append(X[inicio_vetor1])
            inicio_vetor1 += 1
        else:
            aux.append(X[inicio_vetor2])
            inicio_vetor2 += 1

    while inicio_vetor1 <= meio:
        aux.append(X[inicio_vetor1])
        inicio_vetor1 += 1

    while inicio_vetor2 <= fim:
        aux.append(X[inicio_vetor2])
        inicio_vetor2 += 1
    
    poslivre = len(aux)
    for i in range(poslivre):
        X[inicio + i] = aux[i]



def merge_sort(X, inicio, fim):
    if inicio < fim:
        meio = (inicio + fim) // 2

        merge_sort(X, inicio, meio)
        merge_sort(X, meio + 1, fim)
        
        intercala(X, inicio, meio, fim)

def ler_vetor(nome_arquivo):
    
    with open(nome_arquivo, "r") as arquivo:
            vetor = [int(linha.strip()) for linha in arquivo]  # List comprehension
            return vetor

def main():
    
    nome_arquivo = sys.argv[1]

    vetor = ler_vetor(nome_arquivo)

    inicio = time.monotonic()  
    merge_sort(vetor, 0, len(vetor) - 1)
    fim = time.monotonic()
    tempo_execucao = fim - inicio  

    print(f"{tempo_execucao}")


if __name__ == "__main__":
    main()