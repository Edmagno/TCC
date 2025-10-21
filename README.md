# TCC: Análise de Performance de Algoritmos de Ordenação (C vs. C++)

Este repositório contém todos os artefatos relacionados ao meu Trabalho de Conclusão de Curso (TCC) em Engenharia da Computação focado na análise de desempenho de algoritmos de ordenação (Bubblesort, Insertionsort, Selectionsort, QuickSort, MergeSort e HeapSort) implementados em C, C++ e Python.

O projeto é dividido em duas frentes de análise:
1.  **Análise Quantitativa (Performance):** Medição do tempo de execução dos algoritmos com diferentes tamanhos de entrada (vetores de 100 a 1.000.000 de elementos), com 100 repetições para cada cenário.
2.  **Análise Qualitativa (Legibilidade):** Pesquisa com alunos para avaliar a facilidade de entendimento e manutenção de cada implementação.

---

## Estrutura do Repositório

O repositório está organizado nas seguintes pastas para facilitar a navegação e compreensão da metodologia:

* **/Algoritmos**: Contém as implementações dos algoritmos de ordenação nas linguagens C, C++ e Python. Cada subpasta de linguagem armazena os códigos-fonte e os respectivos executáveis responsáveis por gerar os arquivos `.csv` de performance.

* **/Analise**: Abriga o Jupyter Notebook (`.ipynb`) principal. Este notebook é responsável por importar os dados da pasta `/Resultados`, consolidar tudo em um DataFrame e gerar as análises estatísticas e visualizações (gráficos de linha, box plots, etc.).

* **/Apoio**: Armazena materiais de consulta, artigos e referências teóricas utilizadas durante o desenvolvimento do trabalho.

* **/Executores**: Contém os scripts de automação (arquivos `.bash`) utilizados para executar os testes em lote, garantindo que todos os algoritmos sejam rodados sob as mesmas condições e gerando os arquivos de resultado de forma padronizada.

* **/Resultados**: Armazena os dados brutos de performance gerados pelos executáveis. Os dados estão em formato `.csv`, separados em subpastas por linguagem, e prontos para ser consumidos pelo notebook de análise.

* **/Validações**: Inclui um conjunto de testes e códigos auxiliares. O objetivo desta pasta é validar a corretude das implementações, assegurando que os algoritmos estão, de fato, ordenando os vetores corretamente antes da medição de performance.

* **/Vetores**: Contém o script responsável por gerar os vetores de entrada (com diferentes tamanhos) e os próprios arquivos de vetores utilizados nos testes, garantindo que todos os algoritmos sejam testados com os mesmos dados.

* **README.md**: Este arquivo.

---

## Fluxo de Trabalho do Projeto

Esta seção descreve o passo a passo metodológico da execução do projeto, desde a preparação dos dados até a análise final.

### Fase 1: Geração dos Vetores de Teste

Antes de qualquer execução, foi necessário criar uma base de dados consistente para os testes.

1.  **Criação dos Vetores:** Foi utilizado o script na pasta `/Vetores` para gerar os conjuntos de dados. Para cada tamanho (ex: 100, 1.000, 1.000.000), foram criados **100 vetores distintos** com elementos em ordem aleatória.
2.  **Armazenamento:** Esses vetores foram salvos, garantindo que todos os algoritmos, em todas as linguagens, fossem testados com os mesmos 100 conjuntos de dados de entrada para cada tamanho.

### Fase 2: Implementação dos Algoritmos

Os seis algoritmos (BubbleSort, InsertionSort, SelectionSort, MergeSort, HeapSort e QuickSort) foram implementados nas linguagens C, C++ e Python. Os códigos-fonte completos estão disponíveis na pasta `/Algoritmos`.

### Fase 3: Validação da Corretude

Antes de medir o *tempo* de execução, foi fundamental garantir a *corretude* das implementações. Este processo foi feito em duas etapas e está contido na pasta `/Validações`:

1.  **Execução de Teste:** Cada algoritmo foi executado utilizando um conjunto de vetores de teste de tamanho 100 (escolhido para facilitar a depuração). O resultado de cada ordenação foi salvo em um arquivo de saída (o vetor supostamente ordenado).
2.  **Verificação Automatizada:** Foi desenvolvido um script Python que, após a execução dos algoritmos, lia todos os arquivos de saída gerados. Este script verificava a ordenação de cada vetor (garantindo que `vetor[i] <= vetor[i+1]` para todos os elementos) e emitia um relatório final, confirmando se todas as implementações estavam, de fato, ordenando 100% dos vetores de teste corretamente.

### Fase 4: Execução Automatizada e Coleta de Dados

Com os algoritmos validados e os vetores prontos, a coleta de performance foi automatizada.

1.  **Scripts de Execução:** Os arquivos `.bash` na pasta `/Executores` foram criados para automatizar todo o processo de teste.
2.  **Execução em Lote:** Cada script executou os algoritmos (da pasta `/Algoritmos`) contra os vetores de teste (da pasta `/Vetores`).
3.  **Coleta Estatística:** Para garantir a relevância estatística, o teste para um único tamanho (ex: 1.000.000) consistiu em **ordenar os 100 vetores diferentes** daquele tamanho, um de cada vez.
4.  **Medição:** O tempo de execução de *cada uma* dessas 100 ordenações (uma para cada vetor) foi cronometrado individualmente.
5.  **Exportação:** Ao final do processo, o programa salvou os 100 tempos medidos em um único arquivo `.csv` (ex: `resultados_quick_sort_c.csv`), contendo colunas como `Linguagem`, `Algoritmo`, `Tamanho`, `Tempo` e `Repeticao` (onde `Repeticao` de 1 a 100 indica o índice do vetor testado).
6.  **Armazenamento:** Esses arquivos `.csv` brutos foram salvos diretamente na pasta `/Resultados`.

### Fase 5: Análise de Performance (Análise Quantitativa)

Toda a análise dos dados de performance foi centralizada no Jupyter Notebook localizado na pasta `/Analise`.

1.  **Carregamento:** O notebook primeiro localiza e carrega dinamicamente todos os arquivos `.csv` das pastas `/Resultados/C`, `/Resultados/C++` e `/Resultados/Python`.
2.  **Unificação:** Os dados de todos os arquivos são concatenados em um único DataFrame (usando a biblioteca Pandas).
3.  **Agregação:** Os dados brutos (agora representando 100 execuções em vetores distintos) são agrupados para calcular estatísticas descritivas, como o **tempo médio**, **mediana** e **desvio padrão** para cada cenário (ex: C++, QuickSort, Tamanho 1.000.000).
4.  **Visualização:** Com os dados tratados e agregados, são gerados os gráficos comparativos (usando Matplotlib e Seaborn) para responder às perguntas do TCC, como:
    * Gráficos de Linha (Complexidade vs. Tempo).
    * Box Plots (Distribuição e estabilidade dos tempos entre os diferentes vetores).
    * Gráficos de Barras (Comparação direta entre as linguagens).

---

## Autor

* **[Seu Nome Completo]** - [edamgnogomes@gmail.com]