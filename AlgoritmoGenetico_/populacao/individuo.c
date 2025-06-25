#include <stdlib.h>
#include <stdio.h>
#include "individuo.h"
#include "populacao.h"
#include "../mapa/labirinto.h"


Individuo* Individuocreate(unsigned int max_parametro){
    Individuo *novo = malloc(sizeof(Individuo));
    //Definindo o estado de uma lista vazia
    if(novo){
        novo->genoma = calloc(max_parametro + 1, sizeof(char));
        if(novo->genoma == NULL)
        {
            free(novo);
            return(NULL);
        }
        novo->fitness = 0;
        novo->tamanho = max_parametro;
        novo->genoma[max_parametro] = '\0';
    }
    return novo;
}


void gerarIndividuo(Individuo *ind, Config *confi) {
    char caminhos[] = {'D', 'E', 'B', 'C'};
    int mov = confi->tamanho_genoma;

    for (int i = 0; i < mov; i++) {
        ind->genoma[i] = caminhos[rand() % 4];
    }

    ind->fitness = 0;
    ind->tamanho = mov;
}


void gerarIndividuoApto();


void simularIndividuo(Labirinto *labi, Individuo *ind, Config *confi){
    int x = labi->inicioX;
    int y = labi->inicioY;
    int penalidade = 0;



    int mov = confi->tamanho_genoma;

    for(int i = 0; i < mov; i++){
        int movX = x;
        int movY = y;
        

        if (ind->genoma[i] == 'C'){
            movY--;
        }else if (ind->genoma[i] == 'B'){
            movY++;
        }else if(ind->genoma[i] == 'E'){
            movX--;
        }else if(ind->genoma[i] == 'D'){
            movX++;
        }
        
        if(movimentoValido(labi, movX, movY)){
            x = movX;
            y = movY;
        }else{
            penalidade++;
        }

    }
        
    ind->posicaoFinal[0] = x;
    ind->posicaoFinal[1] = y;

    int distanciaManhattan = abs(x - labi->fimX) + abs(y - labi->fimY);
    ind->fitness = 1000 - (10 * penalidade) - (5 * distanciaManhattan);
}

void imprimirIndividuo(Individuo *ind) {
    for (int i = 0; i < ind->tamanho; i++) {
        printf("%c ", ind->genoma[i]);
    }
    printf("\n");
}
