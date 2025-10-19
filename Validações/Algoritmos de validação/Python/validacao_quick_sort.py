import os
import sys


# --- Funções do Quick Sort ---
def troca(X, i, j):
    """Função auxiliar para trocar dois elementos de posição em uma lista."""
    aux = X[i]
    X[i] = X[j]
    X[j] = aux

def particao(X, p, r):
    """
    Particiona o subvetor X[p..r] em torno de um pivô.
    """
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
    """
    Função principal que aplica o algoritmo Quick Sort recursivamente.
    """
    if p < r:
        q = particao(X, p, r)
        quicksort(X, p, q)
        quicksort(X, q + 1, r)

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
    Função principal que orquestra a leitura, ordenação com Quick Sort
    e escrita de 100 vetores.
    """
    # Caminhos relativos a partir da pasta de execução do algoritmo (Python)
    caminho_entrada_base = os.path.join("..", "..", "..", "Vetores", "tamanho_100")
    # Ajusta o caminho de saída para uma pasta específica do Quick Sort
    caminho_saida_base = os.path.join("..", "..", "Vetores ordenados", "Python", "Quick sort")

    # Cria o diretório de saída se ele não existir
    os.makedirs(caminho_saida_base, exist_ok=True)

    print("Iniciando processo de ordenacao em lote com Quick Sort (Python)...")

    for i in range(1, 101):
        # Constrói os nomes dos arquivos de forma segura
        nome_arquivo_entrada = os.path.join(caminho_entrada_base, f"vetor_100_{i}.txt")
        nome_arquivo_saida = os.path.join(caminho_saida_base, f"vetor_100_{i}.txt")

        vetor = ler_vetor(nome_arquivo_entrada)

        if vetor is not None:
            # Chama a função quicksort com os parâmetros iniciais
            quicksort(vetor, 0, len(vetor) - 1)
            escrever_vetor(nome_arquivo_saida, vetor)
            print(f"Arquivo vetor_100_{i}.txt processado com sucesso.")

    print("Processo concluido!")


if __name__ == "__main__":
    main()
