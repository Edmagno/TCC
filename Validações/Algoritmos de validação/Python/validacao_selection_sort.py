import os

# --- Função do Selection Sort ---
def selection_sort(X):
    """
    Função que aplica o algoritmo Selection Sort em uma lista.
    """
    n = len(X)

    for i in range(n - 1):
        # Encontra o índice do menor elemento no restante da lista
        min_idx = i
        for j in range(i + 1, n):
            if X[j] < X[min_idx]:
                min_idx = j

        # Troca o elemento encontrado com o primeiro elemento não ordenado
        if min_idx != i:
            X[i], X[min_idx] = X[min_idx], X[i]


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
    Função principal que orquestra a leitura, ordenação com Selection Sort
    e escrita de 100 vetores.
    """
    # Caminhos relativos a partir da pasta de execução do algoritmo (Python)
    caminho_entrada_base = os.path.join("..", "..", "..", "Vetores", "tamanho_100")
    # Ajusta o caminho de saída para uma pasta específica do Selection Sort
    caminho_saida_base = os.path.join("..", "..", "Vetores ordenados", "Python", "Selection sort")

    # Cria o diretório de saída se ele não existir
    os.makedirs(caminho_saida_base, exist_ok=True)

    print("Iniciando processo de ordenacao em lote com Selection Sort (Python)...")

    for i in range(1, 101):
        # Constrói os nomes dos arquivos de forma segura
        nome_arquivo_entrada = os.path.join(caminho_entrada_base, f"vetor_100_{i}.txt")
        nome_arquivo_saida = os.path.join(caminho_saida_base, f"vetor_100_{i}.txt")

        vetor = ler_vetor(nome_arquivo_entrada)

        if vetor is not None:
            # Chama a função selection_sort
            selection_sort(vetor)
            escrever_vetor(nome_arquivo_saida, vetor)
            print(f"Arquivo vetor_100_{i}.txt processado com sucesso.")

    print("Processo concluido!")


if __name__ == "__main__":
    main()
