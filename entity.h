#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "carta.h"
typedef struct entity{
    int life, energy, shield;
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
    player.shield = 0;
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
entity CreateMonster(int life, int shield, cardNo *cardno){
    enitity monster;
    monster.life = life;
    monster.energy = INT_MAX;
    monster.deck.top = cardno;
    monster.shield = shield; 
    return monster;
}

/*pega apenas a parte q intereca da carta, removendo a ja ultilizada*/
int getImportantCards(card c, card selected_card, card *retc, cardNo *usedc){
    if(!(c.top && selected_card.top)) return 0;
    card hcard;
    startCard(&hcard);
    cardNo hcno;
    int hasused = 0;
    while(c.top != NULL){
        int EqType = !strcmp(selected_card.top->type, c.top->type);
        int EqEnergy_cost = selected_card.top->energy_cost == c.top->energy_cost;
        int EqPower= selected_card.top->power == c.top->power;
        deleteFirstCard(&(c), &hcno);
        if(EqEnergy_cost && EqPower && EqType && !hasused) {
            *usedc = hcno; 
            hasused = 1;
            continue;
        }
        addCard(&hcard, &hcno);
    }
    *retc = hcard;
    return 1;
}

/*faz a entidade usar sua carta*/
/*a entidade 1 e a que usa a carta, e a entidade 2 e a q sofre em consequencia desse uso*/
/*se a carta selecionada for de defesa, logo a entidade 1 == entidade 2, pois ela mesmo sofre em consequencia do uso*/
int useEntityCard(card selected_card, entity *causes, entity *takes){
    if ((hasASameCard(selected_card, causes->deck))&&(causes->energy -selected_card.top->energy_cost >= 0)){
        cardNo usedcard;
        if (getImportantCards(causes->deck, selected_card, &(causes->deck), &usedcard) && takes->deck->top != NULL){
            if(!strcmp(selected_card.top->type, "attack")){
                int rest_shield = takes->shield -selected_card.top->power;
                if(rest_shield < 0){
                    takes->life -= -rest_shield;
                    takes->shield = 0;
                }else{
                    takes->shield = rest_shield;
                }
                return 1;
            }else if(!strcmp(selected_card.top->type, "defence")){
                takes->shield += selected_card.top->power;
                return 1;
            }else if(!strcmp(selected_card.top->type, "special")){
                return 1;
            }
        }
    };
    return 0;
}
