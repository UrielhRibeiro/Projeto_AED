#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "monster.h"

#ifndef IENTITY_H
#define IENTITY_H

typedef struct entity{
    int life, shield;
    player *const player;
    monster *const monster;
}entity;

typedef struct sup_func_no{
    char key[20];
    int (*func) (entity *cause, entity *takes);
    struct sup_func_no *prox;
} sup_func_no;

typedef struct sup_func{
    sup_func_no *sup_func_no;
}sup_func;

/*cria um monstro*/
/*e retorna a entidade monstro*/
entity CreateMonster(char class[], int life, tp_fila *action);

/*cria um jogador*/
/*e retorna a entidade jogador*/
entity CreatePlayer(char name[], int life, int energy, char character[], sup_func *sup_func);

//Deleta uma entidade
void DeleteEntity(entity *e);

/*verifica se e um jogador*/
/*1: e um jogador | 0: nao e um jogador*/
int isEntityAPlayer(entity *possible_player);

/*verifica se e um monstro*/
/*1: e um monstro | 0: nao e um monstro*/
int isEntityAMonster(entity *possible_monster);

//verifica se a entidade esta viva
int isEntityAlive(entity *entity1);

//Imprime o jogador
int printPlayer(entity *e);

//Imprime o monstro
int printMonster(entity *e);

//retorna se o ataque foi realizado ou n
int attackEntity(entity *attackentity, entity *defence_entity, int power);

//retorna se foi possivel adicionar escudo ou n
int addEntityShield(entity *entity1, entity *entity2, int qntshield);

/*a entidade cause e a que causa a acao, e a entidade takes e a q sofre a acao                     */
/*o tipo do 3 parametro e void pq podem ser 2 tipos de variaveis, esta descrito abaixo             */
/*valores de entrada (entity, entity, tp_fila * ou Card *, funcao de suporte[apenas para player] ) */
int EntityAction(entity *cause, entity *takes, void *action, sup_func *sup_func);

#endif