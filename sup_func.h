#include <stdio.h>
#include <stdlib.h>
#include "Ientity.h"

#ifndef SUP_FUNC_H
#define SUP_FUNC_H

/*no geral e uma funcao que armazena as funcoes de suporte de um determinado personagem em uma lista encadeada*/
/*em associacao cahve valor, onde a chave e uma string e o valor uma funcao*/

int initialshield, initiallife;

//inicializa a lista
void initSupFunc(sup_func *sf){
    sf->sup_func_no = NULL;
}

//insere uma funcao com nome especifico(key) na lista
int insertSupFunc(sup_func *sf, char key[], int (*func) (entity *cause, entity *takes)){
    sup_func_no *no = (sup_func_no *) malloc(sizeof(sup_func_no));
    if(no == NULL) return 0;
    strcpy(no->key, key);
    no->func = func;
    no->prox = sf->sup_func_no;
    sf->sup_func_no = no;
    return 1;
}

//executar a funcao com um nome especifico(key)
int executeSupFunc(sup_func *sf, char key[], entity *cause, entity *takes){
    sup_func_no *aux = sf->sup_func_no;
    do{
        aux = aux->prox;
    }while( ( !strcmp(aux->key, key) ) && ( aux != NULL ) );
    if(aux == NULL) return 0;
    aux->func(cause, takes);
    return 1;
}

#endif