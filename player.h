#include <stdio.h>
#include <stdlib.h>
#include "carta.h"

#ifndef PHAND_H
#define PHAND_H

int PLAYER_LIFE;

typedef struct phand_no{
    Card card;
    struct phand_no *next;
    struct phand_no *befo;
}phand_no;

typedef struct phand{
    phand_no *first;
}phand;

typedef struct player{
    CardStack deck;
    phand hand;
    char character[20];
    char name[20];
    int energy;
    int MAX_EA;
}player;

void initPlayerHand(phand *ph){
    ph->first = NULL;
}

int insertPlayerHandCard(phand *ph, Card e){
    phand_no *aux = (phand_no *) malloc(sizeof(phand_no));
    if(aux == NULL) return 0;
    aux->card = e;
    aux->next = ph->first;
    aux->befo = NULL;
    ph->first->befo = aux;
    ph->first = aux;
    return 1;
}

int searchPlayerHandCard (phand *ph, Card *e){
    if(ph->first == NULL) return 0;
    phand_no *aux = ph->first;
    do{
        aux = aux->next;
    }while((aux != NULL) && !areCardsEqual(&aux->card, e));
    if(aux == NULL) return 0;
    return 1;
}

int countPlayerHand (phand *ph){

    int c=0;
    phand_no *aux = ph->first;
    if(aux == NULL) return 0;
    while(aux != NULL){
        aux=aux->next;
        c++;
    }

    return c;

}

int deletePlayerHandCard(phand *ph, Card *e){
    if(ph->first == NULL) return 0;
    phand_no *aux = ph->first;
    do{
        aux = aux->next;
    }while( (aux != NULL) && !areCardsEqual(&aux->card, e) );
    if(aux == NULL) return 0;
    aux->befo->next = aux->next;
    aux->next->befo = aux->befo;
    *e = aux->card;
    aux->next = NULL;
    aux->befo = NULL;
    aux->card.next = NULL;
    free(aux);
    return 1;
}

#endif