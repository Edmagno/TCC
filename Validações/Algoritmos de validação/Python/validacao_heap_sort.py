import os

def ajustar_heap(X, tamanho, i):
    """
    Função auxiliar para manter a propriedade de max-heap.
    """
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
    """
    Função principal que aplica o algoritmo Heap Sort em uma lista.
    """
    tamanho = len(X)

    for i in range(tamanho // 2 - 1, -1, -1):
        ajustar_heap(X, tamanho, i)

    for i in range(tamanho - 1, 0, -1):
        X[i], X[0] = X[0], X[i]  
        ajustar_heap(X, i, 0)   

def ler_vetor(nome_arquivo):
    """Lê um vetor de um arquivo, com tratamento de erro."""
    try:
        with open(nome_arquivo, "r") as arquivo:
            vetor = [int(linha.strip()) for linha in arquivo]
            return vetor
    except FileNotFoundError:
        print(f"Erro: Arquivo de entrada não encontrado em {nome_arquivo}")
        return None
    except Exception as e:
        print(f"Ocorreu um erro ao ler o arquivo {nome_arquivo}: {e}")
        return None

def escrever_vetor(nome_arquivo, vetor):
    """Escreve um vetor (lista) em um arquivo de texto."""
    try:
        with open(nome_arquivo, "w") as arquivo:
            for numero in vetor:
                arquivo.write(f"{numero}\n")
    except Exception as e:
        print(f"Ocorreu um erro ao escrever no arquivo {nome_arquivo}: {e}")

def main():
    """
    Função principal que orquestra a leitura, ordenação com Heap Sort
    e escrita de 100 vetores.
    """
    caminho_entrada_base = os.path.join("..", "..", "..", "Vetores", "tamanho_100")
    caminho_saida_base = os.path.join("..", "..", "Vetores ordenados", "Python", "Heap sort")

    os.makedirs(caminho_saida_base, exist_ok=True)

    print("Iniciando processo de ordenacao em lote com Heap Sort (Python)...")

    for i in range(1, 101):
        nome_arquivo_entrada = os.path.join(caminho_entrada_base, f"vetor_100_{i}.txt")
        nome_arquivo_saida = os.path.join(caminho_saida_base, f"vetor_100_{i}.txt")

        vetor = ler_vetor(nome_arquivo_entrada)

        if vetor is not None:
            heapsort(vetor)
            escrever_vetor(nome_arquivo_saida, vetor)
            print(f"Arquivo vetor_100_{i}.txt processado com sucesso.")

    print("Processo concluido!")


if __name__ == "__main__":
    main()
