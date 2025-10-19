import os
from datetime import datetime

def ler_vetor(caminho_arquivo):
    """
    Lê um vetor de um arquivo de texto.
    Retorna uma lista de inteiros ou None em caso de erro.
    """
    try:
        with open(caminho_arquivo, "r") as arquivo:
            vetor = [int(linha.strip()) for linha in arquivo]
            return vetor
    except Exception:
        # Silencioso para não poluir o console, o erro será logado no relatório
        return None

def verificar_ordenacao(vetor):
    """
    Verifica se uma lista de números está em ordem não decrescente (crescente, permitindo valores iguais).
    Retorna True se estiver ordenada, False caso contrário.
    """
    if not vetor or len(vetor) < 2:
        return True # Um vetor vazio ou com um elemento é considerado ordenado
    for i in range(len(vetor) - 1):
        # A verificação falha apenas se um elemento for estritamente maior que o seu sucessor.
        # Isso permite que elementos adjacentes sejam iguais (ex: [5, 5, 6]), o que está correto.
        if vetor[i] > vetor[i+1]:
            return False
    return True

def encontrar_caminho_tcc():
    """
    Sobe a árvore de diretórios a partir do local do script
    para encontrar a pasta 'TCC' e constrói o caminho para 'Vetores ordenados'.
    Retorna o caminho completo ou None se não for encontrado.
    """
    try:
        caminho_atual = os.path.abspath(os.path.dirname(__file__))
    except NameError:
        caminho_atual = os.getcwd()

    for _ in range(10):
        if os.path.basename(caminho_atual) == 'TCC':
            caminho_vetores = os.path.join(caminho_atual, "Validações", "Vetores ordenados")
            if os.path.isdir(caminho_vetores):
                return caminho_vetores
            else:
                return None

        caminho_pai = os.path.dirname(caminho_atual)
        if caminho_pai == caminho_atual:
            break
        caminho_atual = caminho_pai
        
    return None

def main():
    """
    Função principal que percorre a estrutura de pastas, valida os arquivos
    e gera um relatório consolidado.
    """
    caminho_base = encontrar_caminho_tcc()

    if caminho_base is None:
        print("Erro: Não foi possível encontrar a estrutura 'TCC/Validações/Vetores ordenados'.")
        print("Por favor, certifique-se de que o script está dentro da estrutura de pastas correta do projeto.")
        return

    print(f"Iniciando a verificação de ordenação em: {os.path.abspath(caminho_base)}...")

    # Variáveis para o relatório
    linhas_relatorio = []
    total_geral_corretos = 0
    total_geral_incorretos = 0
    arquivos_com_erro = []

    try:
        pastas_linguagem = sorted([d for d in os.listdir(caminho_base) if os.path.isdir(os.path.join(caminho_base, d))])
    except FileNotFoundError:
        print(f"Erro: O diretório base '{caminho_base}' não foi encontrado.")
        return

    for linguagem in pastas_linguagem:
        linhas_relatorio.append(f"\n===== LINGUAGEM: {linguagem.upper()} =====")
        caminho_linguagem = os.path.join(caminho_base, linguagem)
        
        try:
            pastas_algoritmo = sorted([d for d in os.listdir(caminho_linguagem) if os.path.isdir(os.path.join(caminho_linguagem, d))])
        except FileNotFoundError:
            continue

        for algoritmo in pastas_algoritmo:
            caminho_algoritmo = os.path.join(caminho_linguagem, algoritmo)
            
            total_algoritmo_corretos = 0
            total_algoritmo_incorretos = 0
            
            try:
                arquivos = sorted([f for f in os.listdir(caminho_algoritmo) if f.endswith(".txt")])
            except FileNotFoundError:
                continue

            for nome_arquivo in arquivos:
                caminho_completo = os.path.join(caminho_algoritmo, nome_arquivo)
                vetor = ler_vetor(caminho_completo)

                if vetor is not None and verificar_ordenacao(vetor):
                    total_algoritmo_corretos += 1
                else:
                    total_algoritmo_incorretos += 1
                    motivo = "Não está ordenado" if vetor is not None else "Falha na leitura"
                    arquivos_com_erro.append(f"- Linguagem: {linguagem}, Algoritmo: {algoritmo}, Arquivo: {nome_arquivo} (Motivo: {motivo})")

            # Adiciona resumo do algoritmo ao relatório
            linhas_relatorio.append(f"\n--- Algoritmo: {algoritmo} ---")
            linhas_relatorio.append(f"  - Arquivos Corretos: {total_algoritmo_corretos}")
            linhas_relatorio.append(f"  - Arquivos Incorretos/Com Falha: {total_algoritmo_incorretos}")
            
            total_geral_corretos += total_algoritmo_corretos
            total_geral_incorretos += total_algoritmo_incorretos

    # Monta o conteúdo final do arquivo de relatório
    timestamp = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
    conteudo_final = [
        "=====================================================",
        "      RELATÓRIO DE VERIFICAÇÃO DE ORDENAÇÃO",
        f"      Gerado em: {timestamp}",
        "=====================================================",
    ]
    
    conteudo_final.extend(linhas_relatorio)
    
    conteudo_final.append("\n\n=====================================================")
    conteudo_final.append("           LISTA DE ARQUIVOS COM PROBLEMAS")
    conteudo_final.append("=====================================================")
    if arquivos_com_erro:
        conteudo_final.extend(arquivos_com_erro)
    else:
        conteudo_final.append("Nenhum arquivo com erro encontrado. Todos os vetores estão ordenados corretamente!")

    conteudo_final.append("\n\n=====================================================")
    conteudo_final.append("                   RESUMO GERAL")
    conteudo_final.append("=====================================================")
    conteudo_final.append(f"Total de Arquivos Corretamente Ordenados: {total_geral_corretos}")
    conteudo_final.append(f"Total de Arquivos Incorretos ou com Erro: {total_geral_incorretos}")
    conteudo_final.append(f"Total Geral de Arquivos Verificados: {total_geral_corretos + total_geral_incorretos}")

    # Salva o relatório na pasta 'Validações'
    try:
        caminho_validacoes = os.path.dirname(caminho_base)
        nome_relatorio = f"relatorio_verificacao_{datetime.now().strftime('%Y%m%d_%H%M%S')}.txt"
        caminho_relatorio = os.path.join(caminho_validacoes, nome_relatorio)

        with open(caminho_relatorio, "w", encoding="utf-8") as f:
            f.write("\n".join(conteudo_final))
        
        print(f"\nVerificação concluída. Relatório salvo em: {caminho_relatorio}")

    except Exception as e:
        print(f"\nOcorreu um erro ao salvar o relatório: {e}")


if __name__ == "__main__":
    main()

