#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "carta.h"
typedef struct entity{
    int life, energy;
    card deck;
}enitity;

/*verifica se e um jogador*/
/*1: e um jogador | 0: nao e um jogador*/
int isEntityAPlayer(entity *possible_player){
    if(possible_player->energy < INT_MAX -999999) return 1;
    return 0;
}

/*verifica se e um monstro*/
/*1: e um monstro | 0: nao e um monstro*/
int isEntityAMonster(entity *possible_monster){
    if(possible_monster->energy > INT_MAX -999999) return 1;
    return 0;
}

/*cria um jogador*/
/*e retorna a entidade jogador*/
enitity CreatePlayer(char *name){
    char types[3][8] = {"attack", "defence", "special"};
    entity player;
    player.life = 20;
    player.energy = 3;
    srand(time(NULL));
    for (int i=0; i < 10; i++){
        int j = rand() %2;
        char str[10]; 
        itoa(i +1,str,10);
        cardNo no = {*types[j], *strcat(types[j], str), rand() %10, rand() %8};
        startCard(&player.deck);
        addCard(&player.deck, &no);
    }
    return player;
}

/*cria um monstro*/
/*e retorna a entidade monstro*/
entity CreateMonster(int life, cardNo *cardno){
    enitity monster;
    monster.life = life;
    monster.energy = INT_MAX;
    monster.deck.top = cardno; 
    return monster;
}

/*pega apenas a parte q intereca da carta, removendo a ja ultilizada*/
int getImportantCards(card c, card selected_card, card *retc, cardNo *usedc){
    if(!(c.top && selected_card.top)) return 0;
    card hcard;
    startCard(&hcard);
    cardNo hcno;
    while(!c.top){
        int EqName = strcmp(selected_card.top->name, c.top->name);
        int EqType = strcmp(selected_card.top->type, c.top->type);
        int EqEnergy_cost = selected_card.top->energy_cost == c.top->energy_cost;
        int EqPower= selected_card.top->power == c.top->power;
        deleteFirstCard(&(c), &hcno);
        if(EqEnergy_cost && EqName && EqPower && EqType) *usedc = hcno; continue;
        addCard(&hcard, &hcno);
    }
    *retc = hcard;
    return 1;
}

/*faz a entidade usar sua carta*/
/*a entidade 1 e a que usa a carta, e a entidade 2 e a q sofre em consequencia desse uso*/
int useEntityCard(card selected_card, entity *causes, entity *takes){
    if ((hasACardEqual(selected_card, causes->deck))&&(causes->energy -selected_card.top->energy_cost >= 0)){
        cardNo usedcard;
        if (getImportantCards(causes->deck, selected_card, &(causes->deck), &usedcard)){
            if(strcmp(selected_card.top->type, "attack")){
                takes->life -= usedcard.power;
            }else if(strcmp(selected_card.top->type, "defence")){
                /*sistema de defesa n especificado por soussa*/
            }else if(strcmp(selected_card.top->type, "special")){
                /*sistema de defesa n totalmente especificado por soussa*/
            }
            return 1;
        }
    };
    return 0;
}
