import os

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
    Função principal que orquestra a leitura, ordenação com Merge Sort
    e escrita de 100 vetores.
    """
    # Caminhos relativos a partir da pasta de execução do algoritmo (Python)
    caminho_entrada_base = os.path.join("..", "..", "..", "Vetores", "tamanho_100")
    # Ajusta o caminho de saída para uma pasta específica do Merge Sort
    caminho_saida_base = os.path.join("..", "..", "Vetores ordenados", "Python", "Merge sort")

    # Cria o diretório de saída se ele não existir
    os.makedirs(caminho_saida_base, exist_ok=True)

    print("Iniciando processo de ordenacao em lote com Merge Sort (Python)...")

    for i in range(1, 101):
        # Constrói os nomes dos arquivos de forma segura
        nome_arquivo_entrada = os.path.join(caminho_entrada_base, f"vetor_100_{i}.txt")
        nome_arquivo_saida = os.path.join(caminho_saida_base, f"vetor_100_{i}.txt")

        vetor = ler_vetor(nome_arquivo_entrada)

        if vetor is not None:
            # Chama a função merge_sort com os parâmetros iniciais
            merge_sort(vetor, 0, len(vetor) - 1)
            escrever_vetor(nome_arquivo_saida, vetor)
            print(f"Arquivo vetor_100_{i}.txt processado com sucesso.")

    print("Processo concluido!")


if __name__ == "__main__":
    main()
