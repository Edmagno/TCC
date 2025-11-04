#!/bin/bash

# Este script executa todos os testes de Python em sequência.
# Ele deve estar na MESMA PASTA dos outros scripts 'executar_...sh'.

echo "=========================================="
echo "--- INICIANDO SUÍTE DE TESTES Python ---"
echo "=========================================="
echo ""

# 1. Quick Sort
echo "--- (1/6) Executando Python QuickSort ---"
bash ./executar_quick_sort_py.sh
echo "--- QuickSort Concluído ---"
echo ""

# 2. Merge Sort
echo "--- (2/6) Executando Python MergeSort ---"
bash ./executar_merge_sort_py.sh
echo "--- MergeSort Concluído ---"
echo ""

# 3. Heap Sort
echo "--- (3/6) Executando Python HeapSort ---"
bash ./executar_heap_sort_py.sh
echo "--- HeapSort Concluído ---"
echo ""

# 4. Selection Sort
#echo "--- (4/6) Executando Python SelectionSort ---"
#bash ./executar_selection_sort_py.sh
#echo "--- SelectionSort Concluído ---"
#echo ""

# 5. Insertion Sort
#echo "--- (5/6) Executando Python InsertionSort ---"
#bash ./executar_insertion_sort_py.sh
#echo "--- InsertionSort Concluído ---"
#echo ""

# 6. Bubble Sort
echo "--- (6/6) Executando Python BubbleSort ---"
bash ./executar_bubble_sort_py.sh
echo "--- BubbleSort Concluído ---"
echo ""

echo "=========================================="
echo "--- SUÍTE DE TESTES Python CONCLUÍDA ---"
echo "=========================================="

exit 0