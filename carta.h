#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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

/*Inicializa a pilha de cartas*/
void startCard(card *c){
    c->top = NULL;
}

/*Adiciona uma carta a pilha de cartas*/
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
