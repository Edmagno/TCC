import random
import os

#Caminho para salvar os vetores
caminho_base = r"D:\TCC\Atual\Vetores"

tamanhos = [1000000]  #Tamanhos dos vetores
num_vetores_por_tamanho = 100  #Número de vetores por tamanho
seed = 42  # Semente para reprodutibilidade

random.seed(seed)

# Cria a pasta principal, se não existir
os.makedirs(caminho_base, exist_ok=True)


for tamanho in tamanhos:
    # Cria a subpasta para o tamanho específico
    pasta = os.path.join(caminho_base, f"tamanho_{tamanho}")
    os.makedirs(pasta, exist_ok=True)

    for i in range(num_vetores_por_tamanho):
        vetor = [random.randint(1, 100000) for _ in range(tamanho)]
        nome_arquivo = os.path.join(pasta, f"vetor_{tamanho}_{i+1}.txt")
        with open(nome_arquivo, "w") as f:
            for num in vetor:
                f.write(str(num) + "\n")

print("Vetores gerados e salvos.")
