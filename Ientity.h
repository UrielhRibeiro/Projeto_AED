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

entity CreateMonster(int life, tp_fila *action);
entity CreatePlayer(char name[], int life, int energy, char character[], sup_func *sup_func);
void DeleteEntity(entity *e);
int isEntityAPlayer(entity *possible_player);
int isEntityAMonster(entity *possible_monster);
int isEntityAlive(entity *entity1);
int printPlayer(entity *e);
int printMonster(entity *e);
int attackEntity(entity *attackentity, entity *defence_entity, int power);
int addEntityShield(entity *entity1, entity *entity2, int qntshield);
int EntityAction(entity *cause, entity *takes, void *action, sup_func *sup_func);

#endif