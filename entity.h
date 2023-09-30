#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h> 
#include "characters.h"

int PLAYER_LIFE;
typedef struct random{
    int min;
    int max;
}random;

typedef struct entity{
    int life, energy, shield;
}entity;

typedef struct monster{
    entity property;
    random random_damage;
    random random_shield;
}monster;

typedef struct player {
    entity property;
    CardStack deck;
    char character[20];
    char name[20];
}player;

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
int isEntityAlive(entity *entity1){
    if (entity1->life <= 0) return 0;
    return 1;
}

/*cria um jogador*/
/*e retorna a entidade jogador*/
player CreatePlayer(char name[], int life, int energy, char character[]){
    player player;
    player.property.life = life;
    PLAYER_LIFE = life;
    player.property.energy = energy;
    player.property.shield = 0;
    strcpy(player.name, name);
    initCardStack(&player.deck);
    srand(time(NULL));
    for (int c = 0; c < 10; c++){
        if (!strcmp(character, "Megumi")){//personagem
            strcpy(player.character, "Megumi");
            MegumiCards(&player.deck);
        }else if(0) {/*outro personagem ainda n definido*/}
    }
    return player;
}

/*cria um monstro*/
/*e retorna a entidade monstro*/
monster CreateMonster(int life, int minShield, int maxShield, int minDamage, int maxDamage){
    monster m;
    m.property.life = life;
    m.property.energy = INT_MAX;
    m.property.shield = 0;
    m.random_shield.min = minShield;
    m.random_shield.max = maxShield;
    m.random_damage.min = minDamage;
    m.random_damage.max = maxDamage;
    return m;
}

//Imprime o jogador
int printPlayer(player *player1){
    if(isEntityAMonster(&player1->property)) return 0;
    printf("\nJogador: %s\nPersonagem: %s\nVida: %d | EA: %d\n", player1->name, player1->character, player1->property.life, player1->property.energy);
    return 1;
}

//Imprime o monstro
int printMonster(monster *monster1){
    if(isEntityAPlayer(&monster1->property)) return 0;
    printf("\nMonstro\nVida: %d\nAtaque: %d - %d\n Escudo: %d - %d\n", monster1->property.life, monster1->random_damage.min, monster1->random_damage.max, monster1->random_shield.min, monster1->random_shield.max);
    return 1;
}
/*
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
*/
/*
int addEntityShield(entity *entity1, entity *entity2, int qntshield){
    int pp = isEntityAPlayer(entity1); // pp = possivel jogador
    int pm = isEntityAMonster(entity2); // pm = possivel monstro
    if(pp){
        if (pm) return 0;
    }else if(!pp){
        if (!pm) return 0;
    }  
    if(player1->property.shield == MAX_SHIELD) return 0;
    player1->property.shield = player1->property.shield +qntshield;
    if(player1->property.shield > MAX_SHIELD){
        int overshield = MAX_SHIELD -player1->property.shield;
        player1->property.shield -= overshield;
    }
    return 1;
}
*/
/*
int healEntity(entity *entity1, entity *entity2 , int qntheal){
    int pp = isEntityAPlayer(entity1); // pp = possivel jogador
    int pm = isEntityAMonster(entity2); // pm = possivel monstro
    if(pp){
        if (pm) return 0;
    }else if(!pp){
        if (!pm) return 0;
    }  
    if(player1->property.life == PLAYER_LIFE) return 0;
    player1->property.life = player1->property.life +qntheal;
    if(player1->property.life > PLAYER_LIFE){
        int overlife = PLAYER_LIFE -player1->property.life;
        player1->property.life -= overlife;
    }
    return 1;  
}
*/
/*a entidade 1 e a que causa a acao, e a entidade 2 e a q sofre a acao*/
/*a entidade que deve ser passada como parametro n deve ser do tipo entity, e sim do tipo player ou monster*/
/*a variavel inutil e realmente inutil so serve pra poder usar o vararg*/
/*entity *causes, entity *takes, Card *selected_card*/
/*
int EntityAction(char inutil, ...){
    player player1[2];
    monster monster1[2];
    Card action;
    va_list args;
    int aux = 0; 
    va_start(args, inutil);
    for (int i = 0; i < 3; i++){
        if (i == 0) {// a entidade que causa a acao
        
        }else if(i == 1){//a entidade que sofre a acao

        }
    }
    va_end(args);

    if ((hasSameCardInStack(causes->deck, *selected_card))&&(causes->energy -selected_card->energy_cost >= 0)){
        if (takes->deck.top != NULL){
            if(!strcmp(selected_card->type, "ATAQUE")){
                int ans = attackEntity(causes, takes, selected_card->power);
                if (ans){
                    DeleteCard(&causes->deck, selected_card);
                    return 1;
                }
            }else if(!strcmp(selected_card->type, "DEFESA")){
                int ans = addEntityShield(causes, takes, selected_card->power);
                if (ans){
                    DeleteCard(&causes->deck, selected_card);
                    return 1;
                }
            }else if(!strcmp(selected_card->type, "SUPORTE")){
                int ans = healEntity(causes, takes, selected_card->power);
                if (ans){
                    DeleteCard(&causes->deck, selected_card);
                    return 1;
                }
            }
        }
    }
    return 0;
}
*/
