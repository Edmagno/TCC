# 1. Captura o diretório onde o SCRIPT está localizado.
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# 2. Define o caminho para a pasta do código-fonte C++.
SOURCE_DIR="$SCRIPT_DIR/../../Algoritmos de validação/C++"

# --- NOMES DOS ARQUIVOS PARA O BUBBLE SORT (C++) ---
SOURCE_FILE="validacao_bubble_sort.cpp"
EXECUTABLE_NAME="validacao_bubble_sort_cpp"
# ---------------------------------------------------

# --- Início da execução do script ---

echo "Diretório do script detectado: $SCRIPT_DIR"
echo "Diretório do código-fonte: $SOURCE_DIR"
echo "Navegando para o diretório do código-fonte..."

# 3. Entra na pasta do CÓDIGO-FONTE para compilar e executar.
cd "$SOURCE_DIR" || { echo "ERRO: O diretório do código-fonte não foi encontrado: $SOURCE_DIR"; exit 1; }

echo "------------------------------------"
echo "Compilando o arquivo $SOURCE_FILE com g++..."

# Comando de compilação usando g++ (o compilador para C++)
g++ -std=c++17 "$SOURCE_FILE" -o "$EXECUTABLE_NAME" -Wall

# Verifica se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação concluída com sucesso."
    echo "------------------------------------"
    
    # Executa o programa
    echo "Executando o programa $EXECUTABLE_NAME..."
    ./"$EXECUTABLE_NAME"
    
    echo "------------------------------------"
    echo "Execução finalizada."
else
    # Exibe uma mensagem de erro se a compilação falhar
    echo "ERRO durante a compilação. Verifique o código-fonte."
fi