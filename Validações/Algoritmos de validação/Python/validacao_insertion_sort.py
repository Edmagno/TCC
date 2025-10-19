import os

# --- Função do Insertion Sort ---
def insertion_sort(X):
    """
    Função que aplica o algoritmo Insertion Sort em uma lista.
    """
    n = len(X)
    for i in range(1, n):
        eleito = X[i]
        j = i - 1
        while j >= 0 and X[j] > eleito:
            X[j + 1] = X[j]
            j -= 1
        X[j + 1] = eleito

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
    Função principal que orquestra a leitura, ordenação com Insertion Sort
    e escrita de 100 vetores.
    """
    # Caminhos relativos a partir da pasta de execução do algoritmo (Python)
    caminho_entrada_base = os.path.join("..", "..", "..", "Vetores", "tamanho_100")
    # Ajusta o caminho de saída para uma pasta específica do Insertion Sort
    caminho_saida_base = os.path.join("..", "..", "Vetores ordenados", "Python", "Insertion sort")

    # Cria o diretório de saída se ele não existir
    os.makedirs(caminho_saida_base, exist_ok=True)

    print("Iniciando processo de ordenacao em lote com Insertion Sort (Python)...")

    for i in range(1, 101):
        # Constrói os nomes dos arquivos de forma segura
        nome_arquivo_entrada = os.path.join(caminho_entrada_base, f"vetor_100_{i}.txt")
        nome_arquivo_saida = os.path.join(caminho_saida_base, f"vetor_100_{i}.txt")

        vetor = ler_vetor(nome_arquivo_entrada)

        if vetor is not None:
            # Chama a função insertion_sort
            insertion_sort(vetor)
            escrever_vetor(nome_arquivo_saida, vetor)
            print(f"Arquivo vetor_100_{i}.txt processado com sucesso.")

    print("Processo concluido!")


if __name__ == "__main__":
    main()
