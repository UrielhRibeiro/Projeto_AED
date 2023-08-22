#include <stdio.h>
#include <limits.h>
#include "carta.h"

typedef struct entity{
    int life, energy;
    card deck;
}enitity;

int isEntityAPlayer(entity *possible_player){
    if(possible_player->energy < INT_MAX -999999) return 1;
    return 0;
}

int isEntityAMonster(entity *possible_monster){
    if(isEntityAPlayer(possible_monster)) return 0;
    return 1;
}

enitity CreatePlayer(int life, int energy){
    entity player;
    player.life = life;
    player.energy = energy;
    /*falta a carta*/
    return player;
}

entity CreateMonster(int life){
    enitity monster;
    monster.life = life;
    monster.energy = INT_MAX;
    /*falta a carta*/
    return monster;
}

