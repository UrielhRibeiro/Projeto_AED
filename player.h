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
    ph->first = aux;
    // Se a lista não estiver vazia, atualiza o ponteiro befo do próximo nó
    if (ph->first->next != NULL) {
        ph->first->next->befo = aux;
    }

    return 1;
}

int searchPlayerHandCard (phand *ph, Card *e){
    if(ph->first == NULL) return 0;
    phand_no *aux = ph->first;
    while((aux != NULL) && !areCardsEqual(&aux->card, e)){
        aux = aux->next;
    }
    if(aux == NULL) return 0;
    return 1;
}

Card *searchPlayerHandCard2(phand *ph, int times){
    if(ph->first == NULL) return NULL;
    phand_no *aux = ph->first;
    int t = 1;
    while((aux != NULL) && t < times){
        aux = aux->next;
        t++;
    }
    if(aux == NULL) return NULL;
    return &aux->card;
}

void printPlayerHand(phand *ph){

    //Modifica a linguagem na qual o texto sai no terminal, aceitando assim os assentos e caracteres especiais
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    //Copia a carta no topo da stack para realizar a impressão
    phand_no *aux;
    int cont=1;
    aux = ph->first;
    while (aux != NULL)
    {
        //Imprime a carta e passa para a próxima
        printf("\nCARTA %d %s\nNome: %s\nCusto: %d EA\nForça: %d\n", cont, aux->card.type, aux->card.name, aux->card.energy_cost, aux->card.power);
        aux = aux->next;
        cont ++;
    }

    //Volta a linguagem do terminal para o padrão
    SetConsoleOutputCP(CPAGE_DEFAULT);
}

int countPlayerHand (phand *ph){

    int c=0;
    phand_no *aux = ph->first;
    while(aux != NULL){
        aux=aux->next;
        c++;
    }
    return c;

}

int deletePlayerHandCard(phand *ph, Card *e){
    if(ph->first == NULL) return 0;
    phand_no *aux = ph->first;
    if(areCardsEqual(&aux->card, e)){
        ph->first = aux->next;
        aux->next = NULL;
        free(aux);
        return 1;
    }
    do{
        aux = aux->next;
    }while( (aux->next != NULL) && !areCardsEqual(&aux->card, e) );
    if(aux == NULL) return 0;
    if(aux->next == NULL){
        aux->befo->next = NULL;
        //*e = aux->card;
        aux->befo = NULL;
        aux->card.next = NULL;
        return 1;
    }
    aux->befo->next = aux->next;
    aux->next->befo = aux->befo;
    //*e = aux->card;
    aux->next = NULL;
    aux->befo = NULL;
    aux->card.next = NULL;
    return 1;
}

void mergeCards(CardStack *mergeCard, CardStack *descarte, player *p) {
    // Verifica se a mão do jogador não está vazia antes de realizar a mesclagem
    if (p->hand.first != NULL) {

        // Percorre a mão do jogador e adiciona as cartas à pilha de cartas
        phand_no *handNode = p->hand.first;
        while (handNode != NULL) {
            pushCard(mergeCard, &handNode->card);
            phand_no *temp = handNode;
            handNode = handNode->next;
            free(temp); //Libera o nó da mão do jogador
        }
        initPlayerHand(&p->hand); //Reinicializa a mão do jogador
    }

    // Percorre a pilha de descarte e adiciona as cartas à pilha de cartas
    while (descarte->top != NULL) {
        Card tempCard;
        popCard(descarte, &tempCard);
        pushCard(mergeCard, &tempCard); 
    }
}

#endif