import sys
import time

def ajustar_heap(X, tamanho, i):
    maior = i       
    esq = 2 * i + 1 
    dir = 2 * i + 2 

    if esq < tamanho and X[esq] > X[maior]:
        maior = esq

    if dir < tamanho and X[dir] > X[maior]:
        maior = dir

    if maior != i:
        X[i], X[maior] = X[maior], X[i]  
        ajustar_heap(X, tamanho, maior)

def heapsort(X):
    tamanho = len(X)

    for i in range(tamanho // 2 - 1, -1, -1):
        ajustar_heap(X, tamanho, i)

    for i in range(tamanho - 1, 0, -1):
        X[i], X[0] = X[0], X[i]

        ajustar_heap(X, i, 0)


def ler_vetor(nome_arquivo):
    try:
        with open(nome_arquivo, "r") as arquivo:
            vetor = [int(linha.strip()) for linha in arquivo]
            return vetor
    except FileNotFoundError:
        print(f"Erro: Arquivo '{nome_arquivo}' não encontrado.", file=sys.stderr)
        return None
    except ValueError:
        print(f"Erro: O arquivo '{nome_arquivo}' contém valores não numéricos.", file=sys.stderr)
        return None

def main():
    if len(sys.argv) < 2:
        print(f"Uso: python {sys.argv[0]} <caminho_do_arquivo>", file=sys.stderr)
        sys.exit(1)
    
    nome_arquivo = sys.argv[1]
    vetor = ler_vetor(nome_arquivo)

    inicio = time.monotonic()
    heapsort(vetor)  
    fim = time.monotonic()
    
    tempo_execucao = fim - inicio

    print(f"{tempo_execucao:.9f}")


if __name__ == "__main__":
    main()