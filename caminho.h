#ifndef CAMINHO_H
#define CAMINHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "entity.h"
typedef struct caminho_no{

    entity *entity;
    struct caminho_no *prox;
    struct caminho_no *befo;
    struct caminho_no *rest; 

}caminho_no;
typedef struct caminho{
    caminho_no *cam_no;
}caminho;

void start_caminnho(caminho *cam){
    cam->cam_no = NULL;
}

int addCaminho(entity *monster, caminho *cam){
    caminho_no *aux = (caminho_no *)malloc(sizeof(caminho_no));
    if(aux == NULL || !isEntityAMonster(monster)) return 0;
    aux->entity = monster;
    aux->rest = NULL;
    aux->prox = NULL;
    if(cam->cam_no == NULL){
        aux->befo = NULL;
        cam->cam_no = aux;
        return 1;
    }
    caminho_no *aux2 = cam->cam_no;
    while(aux2->prox != NULL){
        aux2 = aux2->prox;
    }
    aux->befo = aux->prox;
    aux2->prox = aux;
    return 1;
}

int addRest(caminho *cam){
    caminho_no *aux = (caminho_no *)malloc(sizeof(caminho_no));
    if(aux == NULL) return 0;
    caminho_no *aux2 = cam->cam_no;
    int count = 1, count2 = 0;
    while(aux2->prox != NULL){
        aux2 = aux2->prox;
        count++;
        if(count % 2){
            if(count2 == 0){
                if(aux2->rest != NULL) continue;
                aux->befo = aux2;
                aux2->rest = aux;
                count2++;
                continue;
            }
            count2 = 0;
            aux->prox = aux2;
        }
    }
    return 1;
}

void imprime_caminho(caminho *cam){
    caminho_no *aux = cam->cam_no;  
    while (aux != NULL){
        printf("\n%s", aux->entity->monster->clas);
        if(aux->rest != NULL){
            printf(" | Descanco");
        }
        aux = aux->prox;
    }
    
}


#endif