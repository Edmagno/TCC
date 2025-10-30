#!/bin/bash

# --- Parte 1: Encontrar o Diretório Base (TCC) ---
DIRETORIO_ATUAL=$(dirname "$(readlink -f "$0")")
# echo "Diretório inicial do script: $DIRETORIO_ATUAL" # Removido para limpeza

DIRETORIO_BASE="" # Inicializa a variável

while [ "$DIRETORIO_ATUAL" != "/" ]; do 
    # echo "Verificando o diretório: $DIRETORIO_ATUAL" # Removido para limpeza

    if [ "$(basename "$DIRETORIO_ATUAL")" = "TCC" ]; then
        DIRETORIO_BASE="$DIRETORIO_ATUAL"
        echo "Diretório base (TCC) encontrado em: $DIRETORIO_BASE"
        break
    fi
    DIRETORIO_ATUAL=$(dirname "$DIRETORIO_ATUAL")
done

# Verificar se o diretório TCC foi encontrado
if [ -z "$DIRETORIO_BASE" ]; then
    echo "ERRO: Não foi possível encontrar o diretório 'TCC' subindo a árvore de diretórios."
    exit 1
fi

# --- Parte 2: Definição de Variáveis (Python - BubbleSort) ---

NOME_ARQUIVO_FONTE="selection_sort.py" 
LINGUAGEM="Python"
ALGORITMO="SelectionSort" 

DIRETORIO_ALGORITMOS="$DIRETORIO_BASE/Algoritmos/$LINGUAGEM" 
DIRETORIO_VETORES="$DIRETORIO_BASE/Vetores"
DIRETORIO_RESULTADOS_PYTHON="$DIRETORIO_BASE/Resultados/$LINGUAGEM"
ARQUIVO_RESULTADOS="$DIRETORIO_RESULTADOS_PYTHON/resultados_"$ALGORITMO"_"$LINGUAGEM".csv" 


CAMINHO_COMPLETO_ARQUIVO_FONTE="$DIRETORIO_ALGORITMOS/$NOME_ARQUIVO_FONTE"

# --- Parte 3: Definição do Experimento ---
tamanhos=(100 1000 10000 100000 1000000)
num_repeticoes=100
CABECALHO="Linguagem;Algoritmo;Tamanho;Tempo;Repeticao"

# --- CORREÇÃO: Criar o diretório de resultados ANTES de escrever nele ---
mkdir -p "$DIRETORIO_RESULTADOS_PYTHON"

# --- NOVO: Parte 4 - Lógica para Resumir ---

# Valores padrão (iniciar do zero)
iniciar_tamanho_idx=0
iniciar_repeticao=1

if [ ! -f "$ARQUIVO_RESULTADOS" ]; then
    # 4.1: Arquivo não existe. Crie-o com o cabeçalho.
    echo "Arquivo de resultados não encontrado. Criando novo em: $ARQUIVO_RESULTADOS"
    echo "$CABECALHO" > "$ARQUIVO_RESULTADOS"
else
    # 4.2: Arquivo existe. Leia a última linha.
    ultima_linha=$(tail -n 1 "$ARQUIVO_RESULTADOS")
    
    if [ -z "$ultima_linha" ] || [ "$ultima_linha" == "$CABECALHO" ]; then
        # 4.3: Arquivo está vazio ou só tem o cabeçalho. Comece do zero.
        echo "Arquivo de resultados encontrado, mas vazio ou só com cabeçalho. Iniciando do zero."
    else
        # 4.4: Arquivo tem dados. Analise a última linha.
        echo "Arquivo de resultados encontrado. Verificando onde parou..."
        
        # Extrai o último tamanho (campo 3) e repetição (campo 5)
        ultimo_tamanho=$(echo "$ultima_linha" | cut -d';' -f3)
        ultima_repeticao=$(echo "$ultima_linha" | cut -d';' -f5)

        echo "Última execução salva: Tamanho $ultimo_tamanho, Repetição $ultima_repeticao"

        # Encontre o índice do último tamanho executado
        achou_idx=false
        for i in "${!tamanhos[@]}"; do
           if [ "${tamanhos[$i]}" = "$ultimo_tamanho" ]; then
                
                if [ "$ultima_repeticao" -lt "$num_repeticoes" ]; then
                    # 4.5: Continue do próximo item NO MESMO tamanho
                    iniciar_tamanho_idx=$i
                    iniciar_repeticao=$((ultima_repeticao + 1))
                    echo "Continuando do Tamanho ${tamanhos[$iniciar_tamanho_idx]} (Repetição $iniciar_repeticao)..."
                else
                    # 4.6: Continue do próximo TAMANHO (repetição 1)
                    iniciar_tamanho_idx=$((i + 1))
                    iniciar_repeticao=1
                    if [ $iniciar_tamanho_idx -lt ${#tamanhos[@]} ]; then
                         echo "Continuando do próximo Tamanho ${tamanhos[$iniciar_tamanho_idx]} (Repetição 1)..."
                    fi
                fi
                achou_idx=true
                break
           fi
        done
        
        if [ "$achou_idx" = false ]; then
             echo "AVISO: O último tamanho ($ultimo_tamanho) não está na lista. Reiniciando do zero."
             echo "$CABECALHO" > "$ARQUIVO_RESULTADOS" # Reinicia o arquivo
        fi
    fi
fi

# --- MODIFICADO: Parte 5 - Execução e Coleta de Resultados ---

# 5.1: Verifique se já terminamos
if [ $iniciar_tamanho_idx -ge ${#tamanhos[@]} ]; then
    echo "Execução já estava completa. Nenhum teste a ser rodado."
    exit 0
fi

# 5.2: Loop de tamanho modificado (começa do índice que encontramos)
for ((t_idx = iniciar_tamanho_idx; t_idx < ${#tamanhos[@]}; t_idx++)); do
    tamanho=${tamanhos[$t_idx]}

    # 5.3: Loop de repetição modificado (começa da repetição que encontramos)
    for ((i = iniciar_repeticao; i <= num_repeticoes; i++)); do
        echo "Processando $ALGORITMO ($LINGUAGEM) - Tamanho: $tamanho, Repetição: $i de $num_repeticoes"

        CAMINHO_COMPLETO_ARQUIVO_VETOR="$DIRETORIO_VETORES/tamanho_${tamanho}/vetor_${tamanho}_${i}.txt"

        if [ ! -f "$CAMINHO_COMPLETO_ARQUIVO_VETOR" ]; then
            echo "AVISO: Vetor não encontrado em $CAMINHO_COMPLETO_ARQUIVO_VETOR. Pulando."
            tempo_log="VETOR_NAO_ENCONTRADO"
        else
            tempo_capturado=$(python "$CAMINHO_COMPLETO_ARQUIVO_FONTE" "$CAMINHO_COMPLETO_ARQUIVO_VETOR" "$ALGORITMO" "$tamanho")
            exit_code=$?
            
            tempo_log=$(echo "$tempo_capturado" | xargs)

            if [ $exit_code -ne 0 ]; then
                echo "ERRO na execução do Python (Tamanho: $tamanho, Repetição: $i). Código de saída: $exit_code"
                tempo_log="ERRO_EXECUCAO"
            fi
        fi
            
        # Salva a linha no CSV (usando '>>' para adicionar)
        echo "$LINGUAGEM;$ALGORITMO;$tamanho;$tempo_log;$i" >> "$ARQUIVO_RESULTADOS"
    done
    
    # 5.4: --- IMPORTANTE ---
    # Após o primeiro loop de tamanho terminar, todos os próximos devem começar da repetição 1
    iniciar_repeticao=1 
done

echo "Execução concluída. Resultados salvos em $ARQUIVO_RESULTADOS"
exit 0