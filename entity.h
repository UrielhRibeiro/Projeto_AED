#include <stdio.h>
#include <limits.h>
#include "carta.h"

/*Perguntar a Soussa se no header pode passar uma funcao na struct*/
typedef struct entity{
    int life, energy;
    card deck;
}enitity;

/*verifica se e um jogador*/
int isEntityAPlayer(entity *possible_player){
    if(possible_player->energy < INT_MAX -999999) return 1;
    return 0;
}

/*verifica se e um monstro*/
int isEntityAMonster(entity *possible_monster){
    if(possible_monster->energy > INT_MAX -999999) return 1;
    return 0;
}

/*cria um jogador*/
enitity CreatePlayer(int life, int energy){
    entity player;
    player.life = life;
    player.energy = energy;
    /*falta a carta*/
    return player;
}

/*cria um monstro*/
entity CreateMonster(int life){
    enitity monster;
    monster.life = life;
    monster.energy = INT_MAX;
    /*falta a carta*/
    return monster;
}

