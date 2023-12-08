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
    sf->no = NULL;
}

//insere uma funcao com nome especifico(key) na lista
int insertSupFunc(sup_func *sf, char key[], int (*func) (entity *causes, entity *takes)){
    sup_func_no *newno = (sup_func_no *) malloc(sizeof(sup_func_no));
    if(newno == NULL) return 0;
    strcpy(newno->key, key);
    newno->func = func;
    newno->prox = sf->no;
    sf->no = newno;
    return 1;
}

//executar a funcao com um nome especifico(key)
int executeSupFunc(sup_func *sf, char key[], entity *cause, entity *takes){
    sup_func_no *aux = sf->no;
    while( ( strcmp(aux->key, key) ) && ( aux != NULL ) ){
        aux = aux->prox;
        Sleep(10);
    }
    if(aux == NULL) return 0;
    int (*func2) (entity *causes, entity *takes);
    func2 =  aux->func;
    func2(cause, takes);
    return 1;
}

#endif
