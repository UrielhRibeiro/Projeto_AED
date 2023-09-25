#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "carta.h"
#include "config.h"

int PLAYER_LIFE;

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
int isEntityAlive(entity *entity1){
    if (entity1->life <= 0) return 0;
    return 1;
}

/*cria um jogador*/
/*e retorna a entidade jogador*/
entity CreatePlayer(char *name, int life, int energy){
    entity player;
    player.life = life;
    PLAYER_LIFE = life;
    player.energy = energy;
    player.shield = 0;
    char types[4][20] = {"attack", "defence", "heal", "dig"};
    srand(time(NULL));
    initCardStack(&player.deck);
    for (int i = 0; i < 10; i++){
        Card c;
        int v = rand() %4, p;
        char buffer[100];
        itoa(i, buffer, 10);
        strcat(buffer, " card");
        if      (!strcmp(types[v], types[0]))  p = rand() %(damage[0] +1) +damage[1];  
        else if (!strcmp(types[v], types[1]))  p = rand() %(shield[0] +1) +shield[1];
        else if (!strcmp(types[v], types[2]))  p = rand() %(heal[0] +1)   +heal[1];
        else if (!strcmp(types[v], types[3]))  p = 1;
        strcpy(c.type, types[v]);
        strcpy(c.name, buffer);
        c.energy_cost =  rand() %(energy_cost[0] +1) +energy_cost[0];
        c.power = p;
        pushCard(&player.deck, &c);
    }
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

//!!!!! as funcoes abaixo exceto useEntityCard nao deve estar no jogo pq ao usar a useEntityCard ja executa essas funcoes

//ataca a entidade e retorna se foi possivel realizar o ataque ou n
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

//adiciona escudo a entidade em uma determinada quantidade e retorna se foi possivel realizar o ataque ou n
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

//cava a carta aleatoria e retorna se foi possivel realizar o ataque ou n
int digCard(entity *entity1, entity *entity2){
    static int i = 1;
    if (entity1 != entity2) return 0;
    char types[4][20] = {"attack", "defence", "heal", "dig"};
    srand(time(NULL));
    int v = rand() %4, p;
    char buffer[100];
    itoa(i, buffer, 10);
    strcat(buffer, " dig card");
    if      (!strcmp(types[v], types[0]))  p = rand() %(damage[0] +1) +damage[1];  
    else if (!strcmp(types[v], types[1]))  p = rand() %(shield[0] +1) +shield[1];
    else if (!strcmp(types[v], types[2]))  p = rand() %(heal[0] +1)   +heal[1];
    else if (!strcmp(types[v], types[3]))  p = 1;
    Card c; 
    strcpy(c.type, types[v]);
    strcpy(c.name, buffer);
    c.energy_cost =  rand() %(energy_cost[0] +1) +energy_cost[0];
    c.power = p;
    c.next = entity1->deck.top;
    pushCard(&(entity1->deck), &c);
    i++;
    return 1;
}

// restaura a vida de alguma entidade em um valor especificado e retorna se foi possivel realizar o ataque ou n
int healEntity(entity *entity1, entity *entity2 , int qntheal){
    int pp = isEntityAPlayer(entity1); // pp = possivel jogador
    int pm = isEntityAMonster(entity2); // pm = possivel monstro
    if(pp){
        if (pm) return 0;
    }else if(!pp){
        if (!pm) return 0;
    }  
    if(entity1->life == PLAYER_LIFE) return 0;
    entity1->life = entity1->life +qntheal;
    if(entity1->life > PLAYER_LIFE){
        int overlife = PLAYER_LIFE -entity1->life;
        entity1->life -= overlife;
    }
    return 1;  
}

/*faz a entidade usar sua carta*/
/*a entidade 1 e a que usa a carta, e a entidade 2 e a q sofre em consequencia desse uso*/
/*se a carta selecionada for de defesa, logo a entidade 1 == entidade 2, pois ela mesmo sofre em consequencia do uso*/
/*selected_card e uma cardstack e nao card devido a funcao hassamecard*/
int useEntitycard(entity *causes, entity *takes, Card *selected_card){
    if ((hasSameCardInStack(causes->deck, *selected_card))&&(causes->energy -selected_card->energy_cost >= 0)){
        Card usedcardstack;
        if (takes->deck.top != NULL){
            if(!strcmp(selected_card->type, "attack")){
                int ans = attackEntity(causes, takes, selected_card->power);
                if (ans){
                    DeleteCard(&causes->deck, selected_card);
                    return 1;
                };
            }else if(!strcmp(selected_card->type, "defence")){
                int ans = addEntityShield(causes, takes, selected_card->power);
                if (ans){
                    DeleteCard(&causes->deck, selected_card);
                    return 1;
                };
            }else if(!strcmp(selected_card->type, "heal")){
                int ans = healEntity(causes, takes, selected_card->power);
                if (ans){
                    DeleteCard(&causes->deck, selected_card);
                    return 1;
                };
            }else if(!strcmp(selected_card->type, "dig")){
                int ans = digCard(causes, takes);
                if (ans){
                    DeleteCard(&causes->deck, selected_card);
                    return 1;
                };
            }
        }
    };
    return 0;
}
