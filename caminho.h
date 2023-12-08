#ifndef CAMINHO_H
#define CAMINHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Ientity.h"

typedef struct tp_no {
   entity info;
   struct tp_no *ant;
   struct tp_no *prox;
   struct tp_no *desv;
} tp_no;

typedef tp_no *Caminho;

Caminho inicializa_caminho(){
    return NULL;
}

tp_no *aloca(){

    tp_no *novo;
    novo = (tp_no*)malloc(sizeof(tp_no));
    return novo;

}

int insere_caminho_prox(tp_no *a, entity e){
    tp_no *novo;
    novo = aloca();
    if(!novo) return 0;
    
    novo->info = e;

    if(a==NULL){
        a=novo;
        a->ant=NULL;
        a->prox=NULL;
        a->desv=NULL;
    }
    else{
        a->prox = novo;
        novo->ant = a;
        novo->prox = NULL;
        novo->desv = NULL;
    }

    return 1;
}

int insere_caminho_desv(tp_no *a, entity e){

    tp_no *novo;
    novo = aloca();
    if(!novo) return 0;
    
    novo->info = e;

    if(a==NULL){
        a=novo;
        a->ant=NULL;
        a->prox=NULL;
        a->desv=NULL;
    }
    else{
        a->desv = novo;
        novo->ant = a;
        novo->prox = NULL;
        novo->desv = NULL;
    }

    return 1;
}


//como vamos imprimir? IDEIAS

void imprime_caminho(tp_no *a){
    printf("\n");
    if(a!=NULL){
        
        printf("%s ", a->info.monster->clas);
        imprime_caminho(a->prox);
        imprime_caminho(a->desv);

    }

}

tp_no * destroi_caminho(tp_no *a){
    tp_no *atu, *aux;
    atu=a;
    while(atu!=NULL){
        aux=atu;
        free(atu);
        atu=aux;
        atu=atu->prox;
    }
    free(a);
    return NULL;
}

#endif