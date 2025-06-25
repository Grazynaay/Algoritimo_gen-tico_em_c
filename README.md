# Algoritimo_genetico_em_c
# Algoritmo Genético para Resolução de Labirintos

Este repositório contém a implementação de um algoritmo genético em linguagem C, desenvolvido para encontrar o caminho ideal em um labirinto representado em ASCII. O projeto foi dividido em múltiplos módulos para facilitar a organização e a compreensão, incluindo simulação, cálculo de fitness, operadores genéticos e manipulação de mapas.

---

## Estrutura do Repositório

### Compilação

## Experimentos
Dois experimentos foram realizados com diferentes parâmetros evolutivos, como taxa de mutação, tamanho da população e número de gerações. Cada experimento está documentado separadamente:

experimento/experimento1.csv

Graficos de evolução em png, gerado a partir de um arquico csv, do experimento de config1.ini

![Captura de tela 2025-06-25 061515](https://github.com/user-attachments/assets/d1b8e355-1a84-4613-aec6-108a0563092e)


experimento/experimento2.csv

Graficos de evolução em png, gerado a partir de um arquico csv, do experimento de config2.ini

![Captura de tela 2025-06-25 061609](https://github.com/user-attachments/assets/940145ef-d569-48ca-b399-5be01c323366)


Resultados
Os logs e gráficos estão disponíveis nas respectivas pastas em resultados/. Cada pasta contém:

log.txt: registro da execução com fitness por geração

experimento1.csv: dados para gerar gráficos


```bash
gcc -o labirinto.exe main.c config/config.c mapa/labirinto.c populacao/populacao.c populacao/individuo.c genetico/genetico.c

bash
.\labirinto.exe labirinto.txt config1.ini

bash
.\labirinto.exe labirinto.txt config2.ini


