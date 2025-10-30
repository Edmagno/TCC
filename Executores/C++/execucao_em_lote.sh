#!/bin/bash

# Este script executa todos os testes de C++ em sequência.
# Ele deve estar na MESMA PASTA dos outros scripts 'executar_...sh'.

echo "=========================================="
echo "--- INICIANDO SUÍTE DE TESTES C++ ---"
echo "=========================================="
echo ""

# 1. Quick Sort
echo "--- (1/6) Executando C++ QuickSort ---"
bash ./executar_quick_sort_c++.sh
echo "--- QuickSort Concluído ---"
echo ""

# 2. Merge Sort
echo "--- (2/6) Executando C++ MergeSort ---"
bash ./executar_merge_sort_c++.sh
echo "--- MergeSort Concluído ---"
echo ""

# 3. Heap Sort
echo "--- (3/6) Executando C++ HeapSort ---"
bash ./executar_heap_sort_c++.sh
echo "--- HeapSort Concluído ---"
echo ""

# 4. Selection Sort
echo "--- (4/6) Executando C++ SelectionSort ---"
bash ./executar_selection_sort_c++.sh
echo "--- SelectionSort Concluído ---"
echo ""

# 5. Insertion Sort
echo "--- (5/6) Executando C++ InsertionSort ---"
bash ./executar_insertion_sort_c++.sh
echo "--- InsertionSort Concluído ---"
echo ""

# 6. Bubble Sort
echo "--- (6/6) Executando C++ BubbleSort ---"
bash ./executar_bubble_sort_c++.sh
echo "--- BubbleSort Concluído ---"
echo ""

echo "=========================================="
echo "--- SUÍTE DE TESTES C++ CONCLUÍDA ---"
echo "=========================================="

exit 0