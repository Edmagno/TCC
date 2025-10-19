DIRETORIO_BASE="D:/TCC/Atual"
DIRETORIO_ALGORITMOS="$DIRETORIO_BASE/Algoritmos/Python" 
DIRETORIO_VETORES="$DIRETORIO_BASE/Vetores"
ARQUIVO_RESULTADOS="$DIRETORIO_BASE/Resultados/Python/resultados_bubble_python.csv" 

NOME_ARQUIVO_FONTE="bubble_sort.py" 
LINGUAGEM="Python"
ALGORITMO="BubbleSort"                   

CAMINHO_COMPLETO_ARQUIVO_FONTE="$DIRETORIO_ALGORITMOS\\$NOME_ARQUIVO_FONTE"

tamanhos=(100 1000 10000 100000 1000000)
num_repeticoes=100

echo "Linguagem;Algoritmo;Tamanho;Tempo;Repeticao" > "$ARQUIVO_RESULTADOS"


for tamanho in "${tamanhos[@]}"; do
  mkdir -p "$DIRETORIO_VETORES\\tamanho_${tamanho}"

  for ((i = 1; i <= num_repeticoes; i++)); do
    echo "Processando $ALGORITMO - Tamanho: $tamanho, Repetição: $i de $num_repeticoes"

    CAMINHO_COMPLETO_ARQUIVO_VETOR="$DIRETORIO_VETORES\\tamanho_${tamanho}\\vetor_${tamanho}_${i}.txt"

    tempo_capturado=$(python "$CAMINHO_COMPLETO_ARQUIVO_FONTE" "$CAMINHO_COMPLETO_ARQUIVO_VETOR" "$ALGORITMO" "$tamanho")
    exit_code=$?

    tempo_log=$(echo "$tempo_capturado" | xargs)S
      
    echo "$LINGUAGEM;$ALGORITMO;$tamanho;$tempo_log;$i" >> "$ARQUIVO_RESULTADOS"
  done
done

exit 0