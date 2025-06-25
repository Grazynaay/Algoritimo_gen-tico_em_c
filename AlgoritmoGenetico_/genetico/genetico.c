#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genetico.h"
#include "../populacao/populacao.h"
#include "../config/config.h"
#include "../mapa/labirinto.h"
#include "../populacao/individuo.h"



Individuo* selecaoRoleta(Populacao* populacao) {
    if (!populacao || !populacao->inicio) return NULL;

    double soma_fitness = 0.0;
    TNo* aux = populacao->inicio;

    do {
        soma_fitness += aux->individuo.fitness;
        aux = aux->prox;
    }while (aux != NULL);

    if (soma_fitness == 0.0) return NULL;

    double sorteado = ((double) rand() / (double) RAND_MAX) * soma_fitness;
    double acumulado = 0.0;

    aux = populacao->inicio;
    while (aux != NULL) {
        acumulado += aux->individuo.fitness;
        if (acumulado >= sorteado) {
            return &aux->individuo;
        }
        aux = aux->prox;
    }

    return NULL;  
}

void organizarFitness(Populacao* populacao) {
    if (!populacao || !populacao->inicio) 
        return;

    int trocou;
    TNo* atual;
    TNo* fim = NULL;

    do {
        trocou = 0;
        atual = populacao->inicio;

        while (atual->prox != fim) {
            if (atual->individuo.fitness < atual->prox->individuo.fitness) {
            
                Individuo temp = atual->individuo;
                atual->individuo = atual->prox->individuo;
                atual->prox->individuo = temp;
                trocou = 1;
            }
            atual = atual->prox;
        }
        fim = atual;
    } while (trocou);
}

Individuo* replicar(Individuo* original, Config* config) {

    if (!original || !config) return NULL;

    Individuo* replica_individuo = Individuocreate(config->tamanho_genoma);

     if (!replica_individuo) return NULL;

    for (int i = 0; i < config->tamanho_genoma; i++) {
        replica_individuo->genoma[i] = original->genoma[i];
    }
    replica_individuo->fitness = original->fitness;
    return replica_individuo;
}



Populacao* elitismo(Populacao* atual, Config* config, Labirinto* lab) {
    organizarFitness(atual);

    Populacao* nova = criarPopulacao();
    int meia_populacao = config->num_individuos / 2;

    TNo* atualNo = atual->inicio;
    for (int i = 0; i < meia_populacao && atualNo != NULL; i++) {
        Individuo* replica_individuo = replicar(&atualNo->individuo, config);
        simularIndividuo(lab, replica_individuo, config);  // <-- recalcula fitness
        inserirnaPopulacao(nova, replica_individuo);
        atualNo = atualNo->prox;
    }

    return nova;
}

TNo* individuoAleatorio(Populacao* populacao) {
    if (populacao == NULL || populacao->inicio == NULL) return NULL;

    int posicao = rand() % populacao->max_populacao;  
    TNo* atual = populacao->inicio;

    for (int i = 0; i < posicao; i++) {
        if (atual->prox != NULL) {
            atual = atual->prox;
        } else {
            break;  
        }
    }

    return atual;  
}


Individuo* crossover(Individuo* pai, Individuo* mae, Config* config) {
    Individuo* filho = Individuocreate(config->tamanho_genoma);
    int ponto = rand() % config->tamanho_genoma;

    for (int i = 0; i < config->tamanho_genoma; i++) {
        if (i < ponto) {
            filho->genoma[i] = pai->genoma[i];
        } else {
            filho->genoma[i] = mae->genoma[i];
        }
    }

    return filho;
}

void pais(Populacao* nova, Populacao* original, Config* config, Labirinto* lab) {
    if (!nova || !original || !config || !lab) return;

    int faltam = config->num_individuos - nova->max_populacao;

    for (int i = 0; i < faltam; i++) {
        Individuo* pai = selecaoRoleta(original);
        Individuo* mae = selecaoRoleta(original);

        if (!pai || !mae) continue;  

        Individuo* filho = crossover(pai, mae, config);
        if (!filho) continue;

        simularIndividuo(lab, filho, config); // ✔️ Esse cálculo é necessário
        inserirnaPopulacao(nova, filho);

        simularIndividuo(lab, filho, config);
        inserirnaPopulacao(nova, filho);
    }
}

TNo* melhorIndividuo(Populacao* populacao) {
    if (!populacao || !populacao->inicio) return NULL;

    TNo* melhor = populacao->inicio;
    for (TNo* atual = populacao->inicio->prox; atual != NULL; atual = atual->prox) {
        if (atual->individuo.fitness > melhor->individuo.fitness) {
            melhor = atual;
        }
    }
    return melhor;
}

void salvarEvolucao(int geracao, TNo* melhor, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "a");
    if (!arquivo) {
        printf("Erro ao abrir arquivo '%s'\n", nomeArquivo);
        return;
    }

    fprintf(arquivo, "%d,%d,", geracao, melhor->individuo.fitness);

    for (int i = 0; i < melhor->individuo.tamanho; i++) {
        fputc(melhor->individuo.genoma[i], arquivo);
    }

    fprintf(arquivo, "\n");
    fclose(arquivo);
}