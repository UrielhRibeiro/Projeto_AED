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

/*Pega os elementos do topo da pilha de cartas*/
/*Nao passe como 2 parametro o no da pilha original*/
int getFirstCard(card *c, cardNo *data_cpy){
    if(c->top == NULL) return 0;
    strcpy(data_cpy->name, c->top->name);
    strcpy(data_cpy->type, c->top->type);
    data_cpy->energy_cost = c->top->energy_cost;
    data_cpy->power = c->top->power; 
    return 1;
}

/*
    !!!!Tentativa de encapsular!!!!

    /*Os elementos a serem modficados sao:
        name;
        type;
        energy_cost;
        power;
    /*Ele muda somente 1 elemento por vez, logo fazer um loop pra definir outros elementos
    /*Muda o elemento que esta no topo da pilha
    int setFirstCardElement(card *c, char *element, ...){
        if(c->top == NULL) return 0;
        va_list argp;
        va_start(argp, element);
            if(strcmp(element, "name")){
                strcpy(c->top->name, va_arg(argp, char *));
            }else if(strcmp(element, "type")){
                strcpy(c->top->type, va_arg(argp, char *));
            }else if(strcmp(element, "energy_cost")){
                c->top->energy_cost = va_arg(argp, int);
            }else if(strcmp(element, "power")){
                c->top->power = va_arg(argp, int);
            }
        va_end(argp);
        return 1;
    }
*/

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