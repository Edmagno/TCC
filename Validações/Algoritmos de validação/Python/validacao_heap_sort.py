import os

# --- Funções do Heap Sort ---
def ajustar_heap(X, tamanho, i):
    """
    Função auxiliar para manter a propriedade de max-heap.
    """
    maior = i
    esq = 2 * i + 1
    dir = 2 * i + 2

    # Verifica se o filho esquerdo existe e é maior que a raiz
    if esq < tamanho and X[esq] > X[maior]:
        maior = esq

    # Verifica se o filho direito existe e é maior que a raiz (ou o filho esquerdo)
    if dir < tamanho and X[dir] > X[maior]:
        maior = dir

    # Troca a raiz se necessário e continua a ajustar o heap
    if maior != i:
        X[i], X[maior] = X[maior], X[i]
        ajustar_heap(X, tamanho, maior)

def heapsort(X):
    """
    Função principal que aplica o algoritmo Heap Sort em uma lista.
    """
    tamanho = len(X)

    # Constrói um max-heap
    for i in range(tamanho // 2 - 1, -1, -1):
        ajustar_heap(X, tamanho, i)

    # Extrai elementos um por um
    for i in range(tamanho - 1, 0, -1):
        X[i], X[0] = X[0], X[i]  # Move a raiz atual para o fim
        ajustar_heap(X, i, 0)   # Chama ajustar_heap no heap reduzido

# --- Funções de Leitura e Escrita de Arquivos ---
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

# --- Função principal para o processo em lote ---
def main():
    """
    Função principal que orquestra a leitura, ordenação com Heap Sort
    e escrita de 100 vetores.
    """
    # Caminhos relativos a partir da pasta de execução do algoritmo (Python)
    caminho_entrada_base = os.path.join("..", "..", "..", "Vetores", "tamanho_100")
    # Ajusta o caminho de saída para uma pasta específica do Heap Sort
    caminho_saida_base = os.path.join("..", "..", "Vetores ordenados", "Python", "Heap sort")

    # Cria o diretório de saída se ele não existir
    os.makedirs(caminho_saida_base, exist_ok=True)

    print("Iniciando processo de ordenacao em lote com Heap Sort (Python)...")

    for i in range(1, 101):
        # Constrói os nomes dos arquivos de forma segura
        nome_arquivo_entrada = os.path.join(caminho_entrada_base, f"vetor_100_{i}.txt")
        nome_arquivo_saida = os.path.join(caminho_saida_base, f"vetor_100_{i}.txt")

        vetor = ler_vetor(nome_arquivo_entrada)

        if vetor is not None:
            # Chama a função heapsort no lugar da bubble_sort
            heapsort(vetor)
            escrever_vetor(nome_arquivo_saida, vetor)
            print(f"Arquivo vetor_100_{i}.txt processado com sucesso.")

    print("Processo concluido!")


if __name__ == "__main__":
    main()
