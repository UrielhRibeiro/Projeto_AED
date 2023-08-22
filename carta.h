#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cardNo{
    char name[20];
    char type[20];
    int energy_cost;
    int power;
    cardNo *prx;
}cardNo;
typedef struct card{
    cardNo *top;
}card;

void startCard(card *c){
    c->top = NULL;
}

int addCard(card *c, char *name, char *type, int energy_cost, int power){
    cardNo *cno = (cardNo *) malloc(sizeof(cardNo));
    if(cno == NULL) return 0;
    strcpy(cno->name,name);
    strcpy(cno->type,type);
    cno->energy_cost;
    cno->power = power;
    cno->prx = c->top;
    c->top = cno;
    return 1;
}

int getFirstCard(card *c, cardNo *data){
    if(c->top == NULL) return 0;
    strcpy(data->name, c->top->name);
    strcpy(data->type, c->top->type);
    data->energy_cost = c->top->energy_cost;
    data->power = c->top->power; 
    return 1;
}

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