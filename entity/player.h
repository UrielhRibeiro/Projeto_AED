#include <stdio.h>
#include <stdlib.h>
#include "C:\Users\lickc\Desktop\trabalho AED\Projeto_AED\carta.h"

#ifndef PHAND_H
#define PHAND_H

typedef struct phand_no{
    Card card;
    phand_no *prox;
}phand_no;

typedef struct phand{
    phand_no *topo;
}phand;

typedef struct player{
    CardStack deck;
    phand hand;
    char character[20];
    char name[20];
    int energy;
}player;

void initPHand(phand *ph){
    ph->topo = NULL;
}

int insertPHandCard(phand *ph, Card e){
    phand_no *aux = (phand_no *) malloc(sizeof(phand_no));
    if(aux == NULL) return 0;
    aux->card = e;
    aux->prox = ph->topo;
    ph->topo = aux;
    return 1;
}

int serchPhandCard (phand *ph, Card e){
    if(ph->topo == NULL) return 0;
    phand_no *aux = ph->topo;
    do{
        aux = aux->prox;
    }while((aux != NULL) && (aux->card != e));
    return 1;
}
int deletePHandCard(phand *p, Card *e);


#endif