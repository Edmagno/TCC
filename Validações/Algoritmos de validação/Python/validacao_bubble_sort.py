import os

def bubble_sort(X):
    n = len(X)
    for i in range(n):
        for j in range(0, n - i - 1):
            if X[j] > X[j + 1]:
                X[j], X[j + 1] = X[j + 1], X[j]

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
    Função principal que orquestra a leitura, ordenação e escrita
    de 100 vetores.
    """
    caminho_entrada_base = os.path.join("..", "..", "..", "Vetores", "tamanho_100")
    caminho_saida_base = os.path.join("..", "..", "Vetores ordenados", "Python", "Bubble sort")

    os.makedirs(caminho_saida_base, exist_ok=True)

    print("Iniciando processo de ordenacao em lote com Bubble Sort (Python)...")

    for i in range(1, 101):
        nome_arquivo_entrada = os.path.join(caminho_entrada_base, f"vetor_100_{i}.txt")
        nome_arquivo_saida = os.path.join(caminho_saida_base, f"vetor_100_{i}.txt")

        vetor = ler_vetor(nome_arquivo_entrada)

        if vetor is not None:
            bubble_sort(vetor)
            escrever_vetor(nome_arquivo_saida, vetor)
            print(f"Arquivo vetor_100_{i}.txt processado com sucesso.")

    print("Processo concluido!")


if __name__ == "__main__":
    main()