#include <stdio.h>
#include <stdlib.h>
#include "C:\Users\lickc\Desktop\trabalho AED\Projeto_AED\carta.h"

#ifndef PHAND_H
#define PHAND_H

int PLAYER_LIFE;

typedef struct phand_no{
    Card card;
    phand_no *next;
    phand_no *befo;
}phand_no;

typedef struct phand{
    phand_no *top;
}phand;

typedef struct player{
    CardStack deck;
    phand hand;
    char character[20];
    char name[20];
    int energy;
}player;

void initPlayerHand(phand *ph){
    ph->top = NULL;
}

int insertPlayerHandCard(phand *ph, Card e){
    phand_no *aux = (phand_no *) malloc(sizeof(phand_no));
    if(aux == NULL) return 0;
    aux->card = e;
    aux->next = ph->top;
    aux->befo = NULL;
    ph->top->befo = aux;
    ph->top = aux;
    return 1;
}

int serchPlayerHandCard (phand *ph, const Card *e){
    if(ph->top == NULL) return 0;
    phand_no *aux = ph->top;
    do{
        aux = aux->next;
    }while((aux != NULL) && !areCardsEqual(&aux->card, e));
    if(aux == NULL) return 0;
    return 1;
}

int deletePlayerHandCard(phand *ph, Card *e){
    if(ph->top == NULL) return 0;
    phand_no *aux = ph->top;
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