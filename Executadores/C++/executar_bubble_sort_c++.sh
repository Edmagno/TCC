DIRETORIO_ATUAL=$(dirname "$(readlink -f "$0")")
echo "Diretório inicial do script: $DIRETORIO_ATUAL"

while [ "$DIRETORIO_ATUAL" != "/" ]; do
    
    echo "Verificando o diretório: $DIRETORIO_ATUAL"

    if [ "$(basename "$DIRETORIO_ATUAL")" = "TCC" ]; then
        DIRETORIO_BASE="$DIRETORIO_ATUAL"
        break
    fi
    DIRETORIO_ATUAL=$(dirname "$DIRETORIO_ATUAL")
done

DIRETORIO_ALGORITMOS="$DIRETORIO_BASE\\Algoritmos\\C++"
DIRETORIO_VETORES="$DIRETORIO_BASE\\Vetores"
ARQUIVO_RESULTADOS="$DIRETORIO_BASE\\Resultados\\C++\\resultados_bubble_sort_c++.csv"

NOME_ARQUIVO_FONTE="bubble_sort.cpp"       
ARQUIVO_EXECUTAVEL="./bubble_sort_exec"
LINGUAGEM="C++"            
ALGORITMO="BubbleSort"

CAMINHO_COMPLETO_ARQUIVO_FONTE="$DIRETORIO_ALGORITMOS\\$NOME_ARQUIVO_FONTE"

g++ "$CAMINHO_COMPLETO_ARQUIVO_FONTE" -o "$ARQUIVO_EXECUTAVEL" -std=c++11 -Wall -Wextra
if [ $? -ne 0 ]; then
  exit 1
fi

tamanhos=(100 1000 10000 100000 1000000)
num_repeticoes=100

echo "Linguagem;Algoritmo;Tamanho;Tempo;Repeticao" > "$ARQUIVO_RESULTADOS"


for tamanho in "${tamanhos[@]}"; do
  for ((i = 1; i <= num_repeticoes; i++)); do
    echo "Processando Tamanho: $tamanho: Repetição: $i de $num_repeticoes"

    CAMINHO_COMPLETO_ARQUIVO_VETOR="$DIRETORIO_VETORES\\tamanho_${tamanho}\\vetor_${tamanho}_${i}.txt"

    tempo_capturado=$("$ARQUIVO_EXECUTAVEL" "$CAMINHO_COMPLETO_ARQUIVO_VETOR")
    exit_code=$?

    tempo_log=$(echo "$tempo_capturado" | xargs)

    echo "$LINGUAGEM;$ALGORITMO;$tamanho;$tempo_log;$i" >> "$ARQUIVO_RESULTADOS"
  done
done

exit 0