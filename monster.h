#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tp_no_aux {
    char type[20];
    int power;
    struct tp_no_aux *prox;
} tp_no;

typedef struct {
    tp_no *ini, *fim;
} tp_fila;

typedef struct monster{
    tp_fila action;     
    char clas[32]; 
}monster;

// a fila de acoes do monstro
tp_fila *inicializa_fila (){
    tp_fila *fila=(tp_fila*) malloc(sizeof(tp_fila));
    fila->ini=fila->fim = NULL;
    return fila;
}

tp_no *aloca() {
    tp_no* pt;
    pt=(tp_no*) malloc(sizeof(tp_no));
    return pt;
}

int fila_vazia (tp_fila *fila){
    if (fila->ini == NULL) return 1;
    return 0;
}

int insere_fila (tp_fila *fila, char type[], int pow){
    tp_no *novo;
    novo=aloca();
    if (!novo) return 0;
    novo->power = pow;
    strcpy(novo->type, type);

    novo->prox = NULL;
    if ( fila_vazia(fila) ) { //Se for o primeiro elemento da lista
    fila->ini = novo;
    }
    else {
    fila->fim->prox = novo;
    }
    fila->fim=novo;
    return 1;
}

int remove_fila (tp_fila *fila, char ty[], int *e){
    tp_no *aux;
    if (fila_vazia(fila)) return 0;
    *e=fila->ini->power;
    strcpy(ty, fila->ini->type);

    aux=fila->ini;
    if (fila->ini == fila->fim) //Se for o início da fila
    fila->ini=fila->fim=NULL;
    else
    fila->ini=fila->ini->prox;
    free(aux);
    return 1;
}

tp_fila *destroi_fila(tp_fila *fila) {
    tp_no *atu=fila->ini;
    int e;
    char ty[20];
    while (atu!=NULL)
    {
    remove_fila(fila, &ty[20], &e);
    atu=atu->prox;
    }
    fila->ini=fila->fim=NULL;
    free(fila);
    return NULL;
}

void imprime_fila(tp_fila *fila) {
    tp_fila *fila_aux;
    int pow;
    char ty[20];
    //cria e inicializa uma fila auxiliar
    fila_aux=inicializa_fila();
    while (!fila_vazia(fila))
    {
    remove_fila(fila, &ty[20], &pow);
    printf("%s - %d\n", ty, pow);
    insere_fila(fila_aux, ty, pow);
    }
    fila->ini = fila_aux->ini;
    fila->fim = fila_aux->fim;
    fila_aux->ini = NULL;
    fila_aux->fim = NULL;
    fila_aux = destroi_fila(fila_aux);
    printf("\n");
}

void imprime_primeiro_fila(tp_fila *fila){
    tp_fila *fila_aux;
    int pow;
    char ty[20];
    //cria e incializa a fila auxiliar
    fila_aux=inicializa_fila();
    fila_aux->ini = fila->ini;
    fila_aux->fim = fila->fim;
    remove_fila(fila_aux, &ty[20], &pow);
    printf("%s - %d\n", ty, pow);
    fila_aux = destroi_fila(fila_aux);
    printf("\n");
}


#endif