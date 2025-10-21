import sys
import time


# --- Funções do Merge Sort ---
def intercala(X, inicio, meio, fim):
    """
    Combina duas sub-listas ordenadas (X[inicio..meio] e X[meio+1..fim])
    em uma única lista ordenada.
    """
    aux = []
    inicio_vetor1 = inicio
    inicio_vetor2 = meio + 1

    # Intercala os elementos em ordem na lista auxiliar
    while inicio_vetor1 <= meio and inicio_vetor2 <= fim:
        if X[inicio_vetor1] <= X[inicio_vetor2]:
            aux.append(X[inicio_vetor1])
            inicio_vetor1 += 1
        else:
            aux.append(X[inicio_vetor2])
            inicio_vetor2 += 1

    # Adiciona os elementos restantes do primeiro subvetor (se houver)
    while inicio_vetor1 <= meio:
        aux.append(X[inicio_vetor1])
        inicio_vetor1 += 1

    # Adiciona os elementos restantes do segundo subvetor (se houver)
    while inicio_vetor2 <= fim:
        aux.append(X[inicio_vetor2])
        inicio_vetor2 += 1

    # Copia a lista auxiliar ordenada de volta para a lista original
    for i in range(len(aux)):
        X[inicio + i] = aux[i]

def merge_sort(X, inicio, fim):
    """
    Função principal que aplica o algoritmo Merge Sort recursivamente.
    """
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