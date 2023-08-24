#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cardNo{
    char type[20];
    char name[20];
    int energy_cost;
    int power;
    cardNo *prx;
}cardNo;
typedef struct card{
    cardNo *top;
}card;

/*Inicializa a pilha de cartas*/
void startCard(card *c){
    c->top = NULL;
}

/*Adiciona uma carta a pilha de cartas*/
int addCard(card *c, cardNo *cno1){
    cardNo *cno2 = (cardNo *) malloc(sizeof(cardNo));
    if(cno2 == NULL) return 0;
    strcpy(cno2->name,cno1->name);
    strcpy(cno2->type,cno1->type);
    cno2->energy_cost = cno1->energy_cost;
    cno2->power = cno1->power;
    cno2->prx = c->top;
    c->top = cno2;
    return 1;
}

/*Pega o primeiro elemento da pilha de cartas e remove o primeiro elemnto da pilha*/
int deleteFirstCard(card *c, cardNo *data_backup){
    if(c->top == NULL) return 0;
    cardNo *cfree = c->top;
    strcpy(data_backup->name, c->top->name);
    strcpy(data_backup->type, c->top->type);
    data_backup->energy_cost = c->top->energy_cost;
    data_backup->power = c->top->power;
    c->top = cfree->prx;
    cfree->prx = NULL;
    free(cfree);
    return 1;
}

/*verifica se tem pelo menos uma carta igual*/
int hasACardEqual(card card1, card card2){
    while (!card1.top){
        while (!card2.top){
            int EqName = strcmp(card1.top->name, card2.top->name);
            int EqType = strcmp(card1.top->type, card2.top->type);
            int EqEnergy_cost = card1.top->energy_cost == card2.top->energy_cost;
            int EqPower= card1.top->power == card2.top->power;
            if(EqEnergy_cost && EqName && EqPower && EqType) return 1;
            deleteFirstCard(&card1,NULL);
            deleteFirstCard(&card2,NULL);
        }
    }
    return 0;
}