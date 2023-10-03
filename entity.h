#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include "characters.h"

int PLAYER_LIFE;
//usado para o monstro na geracao de valores aleatorios com um valor minimo e outro valor maximo para definir o intervalo dos valores aleatorios
typedef struct random{
    int min;
    int max;
}random;

typedef struct player{
    CardStack deck;
    char character[20];
    char name[20];
    int energy;
}player;

typedef struct monster{
    random random_damage;
    random random_shield;        
}monster;

typedef struct entity{
    int life, shield;
    player *const player;
    monster *const monster;
}entity;

/*verifica se e um jogador*/
/*1: e um jogador | 0: nao e um jogador*/
int isEntityAPlayer(entity *possible_player){
    if(possible_player->monster == NULL) return 1;
    return 0;
}

/*verifica se e um monstro*/
/*1: e um monstro | 0: nao e um monstro*/
int isEntityAMonster(entity *possible_monster){
    if(possible_monster->player == NULL) return 1;
    return 0;
}

//verifica se a entidade esta viva
int isEntityAlive(entity *entity1){
    if (entity1->life <= 0) return 0;
    return 1;
}
/*cria um jogador*/
/*e retorna a entidade jogador*/
entity CreatePlayer(char name[], int life, int energy, char character[]){
    player *p;
    do {
        p = (player *) malloc(sizeof(player));
    }while(p == NULL);
    
    PLAYER_LIFE = life;
    p->energy = energy;
    strcpy(p->name, name);
    initCardStack(&(p->deck));
    srand(time(NULL));

    if (!strcmp(character, "Megumi")){//personagem
        strcpy(p->character, "Megumi");
        MegumiCards(&p->deck);
    }else if(0) {/*outro personagem ainda n definido*/}

    entity e = {.life = life, .shield = 0, .player = p, .monster = NULL};
    return e;
}

/*cria um monstro*/
/*e retorna a entidade monstro*/
entity CreateMonster(int life, int minShield, int maxShield, int minDamage, int maxDamage){
    monster *m;
    do {
        m = (monster *) malloc(sizeof(monster));
    }while(m == NULL);

    m->random_shield.min = minShield;
    m->random_shield.max = maxShield;
    m->random_damage.min = minDamage;
    m->random_damage.max = maxDamage;

    entity e = {.life = life, .shield = 0, .player = NULL, .monster = m};
    return e;
}

//Deleta uma entidade
void DeleteEntity(entity *e){
    free(e);
    e = NULL;
}

//Imprime o jogador
int printPlayer(entity *e){
    if(isEntityAMonster(e)) return 0;
    printf("\nJogador: %s\nPersonagem: %s\nVida: %d | EA: %d\n", e->player->name, e->player->character, e->life, e->player->energy);
    return 1;
}

//Imprime o monstro
int printMonster(entity *e){
    if(isEntityAPlayer(e)) return 0;
    printf("\nMonstro\nVida: %d\nAtaque: %d - %d\nEscudo: %d - %d\n", e->life, e->monster->random_damage.min, e->monster->random_damage.max, e->monster->random_shield.min, e->monster->random_shield.max);
    return 1;
}

//retorna se o ataque foi realizado ou n
int attackEntity(entity *attackentity, entity *defence_entity, int power){
    int pp = isEntityAPlayer(attackentity); // pp = possivel jogador
    int pm = isEntityAMonster(defence_entity); // pm = possivel monstro
    if(pp){
        if (!pm) return 0;
    }else if(!pp){
        if (pm) return 0;
    }
    int restshield = defence_entity->shield -power;
        if(restshield < 0){
            defence_entity->life -= -restshield;
            defence_entity->shield = 0;
        }else{
            defence_entity->shield = restshield;
        }
    return 1;
}

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

/*a entidade causes e a que causa a acao, e a entidade takes e a q sofre a acao*/
/*o vararg esta ali para funcionar como um parametro opcional, pois o monstro possui apenas a acao, e o jogador a carta*/
/*(entity, entity, char[] ou *Card)*/
int EntityAction(entity *causes, entity *takes, ...){
    va_list args;
    char action[20];
    Card *selected_card;
    va_start(args, takes);
        if(isEntityAPlayer(causes)){
            va_arg(args, Card *);
            //ve se tem a carta no pilha de cartas e se ele tem energia pra isso
            if(!( (hasSameCardInStack(causes->player->deck, *selected_card)) && (causes->player->energy -selected_card->energy_cost >= 0) ) ) return 0;
            strcpy(action, selected_card->type);
        }else if(isEntityAMonster(causes)){
            strcpy(action, va_arg(args, char *));
        }else { return 0; }
    va_end(args);
    if(!strcmp(action, "ATAQUE")){
        if (isEntityAPlayer(causes)){
            int ans = attackEntity(causes, takes, selected_card->power);
            if (ans) {
                DeleteCard(&causes->player->deck, selected_card);
            }
        }else if(isEntityAMonster(causes)){
            int ans = attackEntity(causes, takes, selected_card->power);
            if (ans) {
                //vai executar a remocao e insercao na fila
            }
        }
    }
    return 0;
}

