# Algoritimo_genetico_em_c
# Algoritmo Genético para Resolução de Labirintos

Este repositório contém a implementação de um algoritmo genético em linguagem C, desenvolvido para encontrar o caminho ideal em um labirinto representado em ASCII. O projeto foi dividido em múltiplos módulos para facilitar a organização e a compreensão, incluindo simulação, cálculo de fitness, operadores genéticos e manipulação de mapas.

---

## 📁 Estrutura do Repositório

### Compilação

```bash
gcc -o labirinto.exe main.c config/config.c mapa/labirinto.c populacao/populacao.c populacao/individuo.c genetico/genetico.c

bash
.\labirinto.exe labirinto.txt config1.ini

bash
.\labirinto.exe labirinto.txt config2.ini



🧪 Experimentos
Dois experimentos foram realizados com diferentes parâmetros evolutivos, como taxa de mutação, tamanho da população e número de gerações. Cada experimento está documentado separadamente:

experimento/experimento1.csv

experimento/experimento2.csv
