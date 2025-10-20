TCC: Análise de Performance de Algoritmos de Ordenação (C vs. C++)
Este repositório contém todos os artefatos relacionados ao Trabalho de Conclusão de Curso (TCC) focado na análise de performance e legibilidade de algoritmos de ordenação (QuickSort, MergeSort e HeapSort) implementados em C e C++.

O projeto é dividido em duas frentes de análise:

Análise Quantitativa (Performance): Medição do tempo de execução dos algoritmos com diferentes tamanhos de entrada (vetores de 100 a 1.000.000 de elementos), com 100 repetições para cada cenário.

Análise Qualitativa (Legibilidade): Pesquisa com alunos para avaliar a facilidade de entendimento e manutenção de cada implementação.

Estrutura do Repositório
O repositório está organizado da seguinte forma para facilitar a navegação e compreensão da metodologia:

/TCC
│
├── 📂 Codigos-Fonte/
│   ├── 📂 C/
│   │   ├── heap_sort.c
│   │   ├── merge_sort.c
│   │   └── quick_sort.c
│   │
│   └── 📂 C++/
│       ├── heap_sort.cpp
│       ├── merge_sort.cpp
│       └── quick_sort.cpp
│
├── 📂 Resultados/
│   │   (Dados brutos em .csv gerados pelas execuções dos códigos-fonte)
│   │
│   ├── 📂 C/
│   │   ├── resultados_heap_sort_c.csv
│   │   ├── resultados_merge_sort_c.csv
│   │   └── resultados_quick_sort_c.csv
│   │
│   └── 📂 C++/
│       ├── resultados_heap_sort_c++.csv
│       ├── resultados_merge_sort_c++.csv
│       └── resultados_quick_sort_c++.csv
│
├── 📂 Analise/
│   └── 📈 AnaliseDePerformance.ipynb
│       (Jupyter Notebook que importa todos os .csv, une, trata e gera os gráficos)
│
├── 📂 Pesquisa-Legibilidade/
│   ├── 🖼️ Screenshots/
│   │   (Imagens dos códigos usadas na pesquisa)
│   │
│   └── 📝 Roteiro_Pesquisa.md
│       (Perguntas e estrutura do formulário de pesquisa qualitativa)
│
└── README.md
    (Este arquivo)
Descrição das Pastas
/Codigos-Fonte: Contém as implementações dos algoritmos nas linguagens C e C++. Cada arquivo é um programa executável que gera um .csv com os tempos de execução.

/Resultados: Armazena os dados brutos de performance gerados pelos programas. Os dados estão em formato .csv e separados por linguagem.

/Analise: Contém o Jupyter Notebook (.ipynb) responsável por toda a análise de dados. Este notebook carrega os arquivos .csv da pasta /Resultados, os consolida e gera as visualizações de dados (gráficos de linha, box plots, etc.).

/Pesquisa-Legibilidade: Guarda os materiais de apoio para a análise qualitativa (legibilidade), incluindo as imagens do código e o roteiro de perguntas.

Fluxo de Trabalho do Projeto
Esta seção descreve o passo a passo da execução do projeto, desde a coleta de dados até a análise final.

Fase 1: Implementação dos Algoritmos
Os três algoritmos (HeapSort, MergeSort e QuickSort) foram implementados nas linguagens C e C++. Os códigos-fonte completos estão disponíveis na pasta /Codigos-Fonte.

Fase 2: Coleta de Dados (Geração dos Resultados)
Cada programa da Fase 1 foi compilado e executado para realizar os testes de performance. O processo de coleta seguiu os seguintes passos:

Geração de Vetores: Para cada teste, foram criados vetores com diferentes tamanhos (ex: 100, 1.000, 10.000, 100.000, 1.000.000).

Repetições: Para garantir a relevância estatística e mitigar flutuações do sistema, cada algoritmo foi executado 100 vezes para cada tamanho de vetor.

Medição: O tempo de execução de cada uma das 100 ordenações foi cronometrado.

Exportação: Ao final da execução, cada programa salvou seus resultados em um arquivo .csv (ex: resultados_quick_sort_c.csv), contendo colunas como Linguagem, Algoritmo, Tamanho, Tempo e Repeticao.

Armazenamento: Esses arquivos .csv brutos são a fonte primária de dados para a análise e estão armazenados na pasta /Resultados.

Fase 3: Análise de Performance (Análise Quantitativa)
Toda a análise dos dados de performance foi centralizada no Jupyter Notebook AnaliseDePerformance.ipynb, localizado na pasta /Analise. O fluxo de análise dentro do notebook é:

Carregamento: O notebook primeiro localiza e carrega dinamicamente todos os arquivos .csv das pastas /Resultados/C e /Resultados/C++.

Unificação: Os dados de todos os arquivos são concatenados em um único DataFrame (usando a biblioteca Pandas) para permitir uma análise unificada.

Agregação: Os dados brutos (com 100 repetições) são agrupados para calcular estatísticas descritivas, como o tempo médio, mediana e desvio padrão para cada cenário (ex: C++, QuickSort, Tamanho 1.000.000).

Visualização: Com os dados tratados e agregados, são gerados os gráficos comparativos (usando Matplotlib e Seaborn) para responder às perguntas do TCC, como:

Gráficos de Linha (Complexidade vs. Tempo).

Box Plots (Distribuição e estabilidade dos tempos).

Gráficos de Barras (Comparação direta C vs. C++).

Fase 4: Análise de Legibilidade (Análise Qualitativa)
Paralelamente à análise de performance, foi conduzida uma pesquisa qualitativa:

Criação do Formulário: Um questionário foi elaborado (conforme /Pesquisa-Legibilidade/Roteiro_Pesquisa.md) com perguntas objetivas e subjetivas sobre a legibilidade dos códigos.

Coleta de Respostas: A pesquisa foi compartilhada com alunos da área para coletar suas percepções sobre a facilidade de entender e manter cada implementação.

Análise: As respostas foram compiladas para identificar padrões e complementar a análise quantitativa de performance.