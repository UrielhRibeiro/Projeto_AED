#ifndef CAMINHO_H
#define CAMINHO_H

#include <stdio.h>
#include <stdlib.h>
#include "Ientity.h"
#include <string.h>
#include <time.h>

typedef struct tp_no {
   entity *info;
   struct tp_no *ant;
   struct tp_no *prox;
   struct tp_no *desv;
} tp_no;

typedef tp_no *Caminho;

Caminho inicializa_caminho(){
    return NULL;
}

tp_no *aloca_no(){

    tp_no *novo;
    novo=(tp_no*)malloc(sizeof(tp_no));
    return novo;

}

int insere_caminho_prox(tp_no *a, entity *e){
    tp_no *novo;
    novo = aloca_no();
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

int insere_caminho_desv(tp_no *a, entity *e){

    tp_no *novo;
    novo = aloca_no();
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

Caminho * cria_caminho(){

    Caminho novo;
    novo = inicializa_caminho();

    //Criação dos 5 Monstros
    tp_fila *cl4 = inicializa_fila();
    preencher_fila(cl4);
    entity classe4 = CreateMonster("cl4", 62, cl4);
    Sleep(1);

    tp_fila *cl3 = inicializa_fila();
    preencher_fila(cl3);
    entity classe3 = CreateMonster("cl3", 84, cl3);
    Sleep(1);

    tp_fila *res = inicializa_fila();
    preencher_fila(res);
    entity RES = CreateMonster("RES", 98, res);
    Sleep(1);

    tp_fila *cl2 = inicializa_fila();
    preencher_fila(cl2);
    entity classe2 = CreateMonster("cl2", 98, cl2);
    Sleep(1);

    tp_fila *cl1 = inicializa_fila();
    preencher_fila(cl1);
    entity classe1 = CreateMonster("cl1", 110, cl1);
    Sleep(1);

    tp_fila *clesp = inicializa_fila();
    preencher_fila(clesp);
    entity classeEsp = CreateMonster("clesp", 135, clesp);
    Sleep(1);

    insere_caminho_prox(novo, &classe4);
    Sleep(1);

    insere_caminho_prox(novo, &classe3);
    Sleep(1);  

    insere_caminho_prox(novo->prox, &classe2);
    Sleep(1);

    insere_caminho_desv(novo->prox, &RES);
    Sleep(1);

    insere_caminho_prox(novo->prox->prox, &classe1);
    Sleep(1);

    insere_caminho_prox(novo->prox->prox, &classeEsp);
    Sleep(1);

    novo->prox->desv->desv = novo->prox->prox->prox;

    return novo;
}


void imprime_caminho(tp_no *a){

    printf("   %s   \n", a->info->monster->clas);
    printf("   %s   \n", a->prox->info->monster->clas);
    printf("%s   \tRES\n", a->prox->prox->info->monster->clas);
    printf("   %s   \n", a->prox->prox->prox->info->monster->clas);
    printf("   %s   \n", a->prox->prox->prox->prox->info->monster->clas);
    
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