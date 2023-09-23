#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "carta.h"

#define MAX_SHIELD 20
typedef struct entity{
    int life, energy, shield;
    CardStack deck;
}entity;

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

//verifica se a entidade esta viva
int isEntityalive(entity *entity1){
    if (entity1->life <= 0) return 0;
    return 1;
}

/*cria um jogador*/
/*e retorna a entidade jogador*/
entity CreatePlayer(char *name, Card card){
    entity player;
    player.life = 20;
    player.energy = 3;
    player.shield = 0;
    player.deck.top = &card;
    return player;
}

/*cria um monstro*/
/*e retorna a entidade monstro*/
entity CreateMonster(int life, int shield, Card card){
    entity monster;
    monster.life = life;
    monster.energy = INT_MAX;
    monster.deck.top = &card;
    monster.shield = shield; 
    return monster;
}

//retorna se o ataque foi realizado ou n
int attackEntity(entity *attackentity, entity *defenceentity, int power){
    int pp = isEntityAPlayer(attackentity); // pp = possivel jogador
    int pm = isEntityAMonster(defenceentity); // pm = possivel monstro
    if(pp){
        if (!pm) return 0;
    }else if(!pp){
        if (pm) return 0;
    }
    int restshield = defenceentity->shield -power;
        if(restshield < 0){
            defenceentity->life -= -restshield;
            defenceentity->shield = 0;
        }else{
            defenceentity->shield = restshield;
        }
    return 1;
}

int addEntityShield(entity *entity1, entity *entity2, int qntshield){
    int pp = isEntityAPlayer(entity1); // pp = possivel jogador
    int pm = isEntityAMonster(entity2); // pm = possivel monstro
    if(pp){
        if (pm) return 0;
    }else if(!pp){
        if (!pm) return 0;
    }  
    if(entity1->shield == MAX_SHIELD) return 0;
    entity1->shield = entity1->shield +qntshield;
    if(entity1->shield > MAX_SHIELD){
        int overshield = MAX_SHIELD -entity1->shield;
        entity1->shield -= overshield;
    }
    return 1;
}

/*faz a entidade usar sua carta*/
/*a entidade 1 e a que usa a carta, e a entidade 2 e a q sofre em consequencia desse uso*/
/*se a carta selecionada for de defesa, logo a entidade 1 == entidade 2, pois ela mesmo sofre em consequencia do uso*/
/*selected_cardstack e uma cardstack e nao card devido a funcao hassamecard*/
int useEntitycardstack(entity *causes, entity *takes, CardStack *selected_cardstack){
    if ((hasSameCard(causes->deck, selected_cardstack))&&(causes->energy -selected_cardstack.top->energy_cost >= 0)){
        Card usedcardstack;
        if (takes->deck.top != NULL){
            if(!strcmp(selected_cardstack.top->type, "attack")){
                int ans = attackEntity(causes, takes, selected_cardstack->top->power);
                if (ans){/*vai remover a carta*/};
            }else if(!strcmp(selected_cardstack.top->type, "defence")){
                int ans = addEntityShield(causes, takes, selected_cardstack->top->power);
                if (ans){/*vai remover a carta*/};
            }else if(!strcmp(selected_cardstack.top->type, "special")){
                return 1;
            }
        }
    };
    return 0;
}
