# --- Parte 1: Encontrar o Diretório Base (TCC) ---
DIRETORIO_ATUAL=$(dirname "$(readlink -f "$0")")
echo "Diretório inicial do script: $DIRETORIO_ATUAL"

DIRETORIO_BASE="" 

while [ "$DIRETORIO_ATUAL" != "/" ]; do 
    echo "Verificando o diretório: $DIRETORIO_ATUAL"

    if [ "$(basename "$DIRETORIO_ATUAL")" = "TCC" ]; then
        DIRETORIO_BASE="$DIRETORIO_ATUAL"
        echo "Diretório base (TCC) encontrado em: $DIRETORIO_BASE"
        break
    fi
    DIRETORIO_ATUAL=$(dirname "$DIRETORIO_ATUAL")
done

if [ -z "$DIRETORIO_BASE" ]; then
    echo "ERRO: Não foi possível encontrar o diretório 'TCC' subindo a árvore de diretórios."
    exit 1
fi

# --- Parte 2: Definição de Variáveis (C - MergeSort) ---

NOME_ARQUIVO_FONTE="merge_sort.c"
LINGUAGEM="C"
ALGORITMO="MergeSort"

DIRETORIO_ALGORITMOS="$DIRETORIO_BASE/Algoritmos/"$LINGUAGEM""
ARQUIVO_EXECUTAVEL="$DIRETORIO_ALGORITMOS/"$ALGORITMO""
DIRETORIO_VETORES="$DIRETORIO_BASE/Vetores"
DIRETORIO_RESULTADOS_C="$DIRETORIO_BASE/Resultados/$LINGUAGEM"
ARQUIVO_RESULTADOS="$DIRETORIO_RESULTADOS_C/resultados_"$ALGORITMO"_"$LINGUAGEM".csv"

CAMINHO_COMPLETO_ARQUIVO_FONTE="$DIRETORIO_ALGORITMOS/$NOME_ARQUIVO_FONTE"

# --- Parte 3: Compilação ---
echo "Compilando $CAMINHO_COMPLETO_ARQUIVO_FONTE..."
gcc "$CAMINHO_COMPLETO_ARQUIVO_FONTE" -o "$ARQUIVO_EXECUTAVEL" 
if [ $? -ne 0 ]; then
  echo "ERRO na compilação. Abortando."
  exit 1
fi
echo "Compilação bem-sucedida. Executável em: $ARQUIVO_EXECUTAVEL"


# --- Parte 4: Lógica para "Continuar de onde parou" ---

mkdir -p "$DIRETORIO_RESULTADOS_C"

CABECALHO="Linguagem;Algoritmo;Tamanho;Tempo;Repeticao"
ultimo_tamanho=0
ultima_repeticao=0

if [ ! -f "$ARQUIVO_RESULTADOS" ]; then
    # 1. Se o arquivo não existe, cria com o cabeçalho
    echo "Criando novo arquivo de resultados: $ARQUIVO_RESULTADOS"
    echo "$CABECALHO" > "$ARQUIVO_RESULTADOS"
else
    # 2. Se o arquivo existe, lê a última linha
    ultima_linha=$(tail -n 1 "$ARQUIVO_RESULTADOS")
    
    # 3. Verifica se a última linha não é o cabeçalho (ou seja, se já temos dados)
    if [ "$ultima_linha" != "$CABECALHO" ] && [ -n "$ultima_linha" ]; then
        # Extrai o último tamanho e repetição 
        ultimo_tamanho=$(echo "$ultima_linha" | awk -F';' '{print $3}')
        ultima_repeticao=$(echo "$ultima_linha" | awk -F';' '{print $5}')
        
        # Validação (caso a linha esteja corrompida)
        if ! [[ "$ultimo_tamanho" =~ ^[0-9]+$ ]] || ! [[ "$ultima_repeticao" =~ ^[0-9]+$ ]]; then
            echo "Aviso: Última linha do CSV parece corrompida. Recomeçando do zero."
            ultimo_tamanho=0
            ultima_repeticao=0
        fi
    fi
fi

echo "--- Iniciando/Continuando a partir de Tamanho: $ultimo_tamanho, Repetição: $ultima_repeticao ---"


# --- Parte 5: Execução e Coleta de Resultados ---
tamanhos=(100 1000 10000 100000 1000000)
num_repeticoes=100

for tamanho in "${tamanhos[@]}"; do
    # --- LÓGICA DE CONTINUAÇÃO (TAMANHO) ---
    # Se o tamanho atual for menor que o último salvo, pula o loop inteiro
    if [ "$tamanho" -lt "$ultimo_tamanho" ]; then
        echo "Pulando tamanho $tamanho (já completo)."
        continue
    fi

    for ((i = 1; i <= num_repeticoes; i++)); do
        # --- LÓGICA DE CONTINUAÇÃO (REPETIÇÃO) ---
        # Se o tamanho for O MESMO que o último salvo, verifica a repetição
        if [ "$tamanho" -eq "$ultimo_tamanho" ]; then
            # Se a repetição atual for menor ou igual à última salva, pula para a próxima
            if [ "$i" -le "$ultima_repeticao" ]; then
                echo "Pulando Tamanho: $tamanho, Repetição: $i (já completa)."
                continue
            fi
        fi

        # --- Execução normal ---
        echo "Processando $ALGORITMO ($LINGUAGEM) - Tamanho: $tamanho, Repetição: $i de $num_repeticoes"

        CAMINHO_COMPLETO_ARQUIVO_VETOR="$DIRETORIO_VETORES/tamanho_${tamanho}/vetor_${tamanho}_${i}.txt"

        if [ ! -f "$CAMINHO_COMPLETO_ARQUIVO_VETOR" ]; then
            echo "AVISO: Vetor não encontrado em $CAMINHO_COMPLETO_ARQUIVO_VETOR. Pulando."
            tempo_log="VETOR_NAO_ENCONTRADO"
        else
            tempo_capturado=$("$ARQUIVO_EXECUTAVEL" "$CAMINHO_COMPLETO_ARQUIVO_VETOR")
            exit_code=$?
            tempo_log=$(echo "$tempo_capturado" | xargs)

            if [ $exit_code -ne 0 ]; then
                echo "ERRO na execução do C++ (Tamanho: $tamanho, Repetição: $i). Código: $exit_code"
                tempo_log="ERRO_EXECUCAO"
            fi
        fi

        # Salva a linha no CSV
        echo "$LINGUAGEM;$ALGORITMO;$tamanho;$tempo_log;$i" >> "$ARQUIVO_RESULTADOS"
    done
done

echo "Execução concluída. Resultados salvos em $ARQUIVO_RESULTADOS"
exit 0