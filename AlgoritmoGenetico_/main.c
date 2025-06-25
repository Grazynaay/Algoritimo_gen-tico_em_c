#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config/config.h"
#include "mapa/labirinto.h"
#include "populacao/individuo.h"
#include "populacao/populacao.h"
#include "genetico/genetico.h"

int main(int argc, char *argv[]){

    printf("Inicio do programa\n");

    
    srand(time(NULL));

    if (argc != 3) {
        printf("Uso: %s <arquivo_mapa> <arquivo_config>\n", argv[0]);
        return 1;
    }

    // Carrega labirinto
    Labirinto mapa = CarregarLabirinto(argv[1]);
    if (mapa.matriz == NULL) {
        printf("Erro ao carregar o labirinto: %s\n", argv[1]);
        return 1;
    }

    // Carrega configuração
    Config config = carregarConfiguracao(argv[2]);

    // Print configurações para conferência
    printf("\nArquivo mapa: %s\n", argv[1]);
    printf("Arquivo config: %s\n", argv[2]);
    printf("Numero de individuos: %d\n", config.num_individuos);
    printf("Tamanho do genoma: %d\n", config.tamanho_genoma);
    printf("Taxa de mutacao: %.4f\n", config.taxa_mutacao);
    printf("Elitismo: %d\n", config.elitismo);
    printf("Maximo de geracoes: %d\n", config.max_geracoes);
    printf("Apenas movimentos validos: %d\n", config.apenas_movimentos_validos);
    printf("Arquivo de saidaa (log): %s\n\n", config.saida_log);

    // Cria arquivo CSV limpo para salvar a evolução
    FILE *f = fopen(config.saida_log, "w");
    if (f) {
        fprintf(f, "geracao,fitness,movimentos\n");
        fclose(f);
    } else {
        printf("Erro ao criar arquivo de log: %s\n", config.saida_log);
        liberarLabirinto(&mapa);
        return 1;
    }

    // Gera população inicial
    Populacao* pop = gerarPopulacaoInicial(&config, &mapa);
    if (!pop) {
        printf("Erro ao criar populacao\n");
        liberarLabirinto(&mapa);
        return 1;
    }
    printf("Populacao inicial criada com sucesso!\n");

    // Loop principal de gerações
    for (int i = 0; i < config.max_geracoes; i++) {
        Populacao* nova = NULL;

        if (config.elitismo) {
            nova = elitismo(pop, &config, &mapa);
        } else {
            nova = criarPopulacao();
        }

        pais(nova, pop, &config, &mapa);

        liberarPopulacao(pop);
        pop = nova;

        TNo* melhor = melhorIndividuo(pop);
        printf("Melhor fitness da geracaoo %d: %d\n", i, melhor->individuo.fitness);


        printf("\n=-=-=-=-=-=-== Geracao %d =-=-=-=-=-=-==\n", i);
        imprimirPopulacao(pop);
        salvarEvolucao(i, melhor, config.saida_log);
    }

    // Limpa tudo
    liberarPopulacao(pop);
    liberarLabirinto(&mapa);

    return 0;




    // srand(time(NULL));

    // Config *config = malloc(sizeof(Config));

    // if (argc != 3){
    //     printf(" %s labirinto1.txt config.ini\n", argv[0]);
    //     return 1;
    // }

    // Labirinto mapa = CarregarLabirinto(argv[1]);
    // if (mapa.matriz == NULL){
    //     printf("Erro ao carregar o labirinto1.txt: %s\n", argv[1]);
    //     return 1;
    // }

    // FILE *configFile = fopen(argv[2], "r");
    // if(configFile == NULL){
    //     printf("Erro ao abrir o config.ini: %s\n", argv[2]);
    //     liberarLabirinto(&mapa);
        
    //     return 1;
    // }

    // Config config = carregarConfiguracao(argv[2]);

    // printf("\n---------------labirinto----------------------\n");
    // imprimirLabirinto(&mapa);

    // Populacao* pop = gerarPopulacaoInicial(config, &mapa);;

    // if (!pop){
    //     printf("Erro ao criar população");
    //     return 1;
    // }

    //  else
    // {
    //     printf("Populacao inicial criada com sucesso!");
    // }

    

    // for(int i = 0; i < config->max_geracoes; i++ ){
    //     Populacao* nova = elitismo(pop, config);
    //     pais(nova, pop, config, &mapa);

    //     liberarPopulacao(pop);
    //     pop = nova;

    //     TNo* melhor = melhorIndividuo(pop);

    //     printf("\n=-=-=-=-=-=-== Geracao %d =-=-=-=-=-=-==\n", i);
    //     imprimirPopulacao(pop);
    //     salvarEvolucao(i, melhor, config->saida_log);


    // }
    // liberarPopulacao(pop);
    // liberarLabirinto(&mapa);
    // free(config);
 






    
    // Config confi = carregarConfiguracao("config/config.ini"); //testando configurações
    // printf("Numero de individuos: %d\n", confi.num_individuos);
    // printf("Tamanho do genoma: %d\n", confi.tamanho_genoma);
    // printf("Taxa de mutacao: %.2f\n", confi.taxa_mutacao);

    // Labirinto labi = CarregarLabirinto("labirinto1.txt");   //testando leitura do labirinto
    // imprimirLabirinto(&labi);
    

    // Individuo* ind = Idividuocnreate(confi.tamanho_genoma);
    // gerarIndividuo(ind, &confi);
    // imprimirIndividuo(ind);
    // simularIndividuo(&labi, ind, &confi);
    // printf("Posicao final: (%d, %d)\n", ind->posicaoFinal[0], ind->posicaoFinal[1]);
    // printf("Fitness: %d\n", ind->fitness);

    // Populacao* pop = gerarPopulacaoInicial(&confi, &labi);
    // imprimirPopulacao(pop);

    // Populacao* nova = criarPopulacao();
    // pais(nova, pop, &confi, &labi);



    // FILE* f = fopen("evolucao.csv", "w");
    //     if (f) {
    //     fprintf(f, "geracao,fitness,movimentos\n");
    //     fclose(f);
    // }

    // for (int ger = 0; ger < confi.max_geracoes; ger++) {
    //     Populacao* nova = criarPopulacao();
    //     pais(nova, pop, &confi, &labi);

    //     liberarPopulacao(pop);
    //     pop = nova;

    //     TNo* melhor = melhorIndividuo(pop);

    //     salvarEvolucao(ger, melhor, "evolucao.csv");

    //     printf("Geracao %d: melhor fitness = %d\n", ger, melhor->individuo.fitness);
    // }
    
    // free(ind->genoma);
    // free(ind);

    // return 0;
}