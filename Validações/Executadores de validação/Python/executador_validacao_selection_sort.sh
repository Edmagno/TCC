# 1. Captura o diretório onde o SCRIPT está localizado.
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# 2. Define o caminho para a pasta do código-fonte Python.
SOURCE_DIR="$SCRIPT_DIR/../../Algoritmos de validação/Python"

# --- NOME DO ARQUIVO PYTHON ---
SOURCE_FILE="validacao_selection_sort.py"
# -----------------------------

# --- Início da execução do script ---

echo "Diretório do script detectado: $SCRIPT_DIR"
echo "Diretório do código-fonte: $SOURCE_DIR"
echo "Navegando para o diretório do código-fonte..."

# 3. Entra na pasta do CÓDIGO-FONTE para executar.
cd "$SOURCE_DIR" || { echo "ERRO: O diretório do código-fonte não foi encontrado: $SOURCE_DIR"; exit 1; }

echo "------------------------------------"
echo "Executando o script Python: $SOURCE_FILE..."

# Comando de execução usando o interpretador python3
python "$SOURCE_FILE"

echo "------------------------------------"
echo "Execução finalizada."