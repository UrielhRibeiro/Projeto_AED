#include <stdio.h>
#include <stdlib.h>
#include "characters.h"
#include "player.h"

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
entity CreatePlayer(char name[], int life, int energy, char character[], sup_func *sup_func) {
    player *p;
    do {
        p = (player *) malloc(sizeof(player));
    } while (p == NULL);
    
    PLAYER_LIFE = life;
    p->energy = energy;
    p->MAX_EA = energy;
    strcpy(p->name, name);
    initCardStack(&p->deck);

    if (!strcmp(character, "Megumi")) { // Personagem Megumi

     // Insira as funções do Megumi na lista de funções de suporte
        insertSupFunc(sup_func, "Megumi_EA", Megumi_supfunc_EA);
        insertSupFunc(sup_func, "Megumi_attack", Megumi_supfunc_attack);
        insertSupFunc(sup_func, "Megumi_shield", Megumi_supfunc_shield);

        strcpy(p->character, "Megumi");
        MegumiCards(&p->deck);
    } else if (0) {
        // Outro personagem ainda não definido
    }

    entity e = {.life = life, .shield = 0, .player = p, .monster = NULL};

    // Adicione cartas da pilha de cartas do jogador à sua mão
    for (int i = 0; i < NUM_INITIAL_CARDS; i++) {
        Card drawnCard;
        if (drawCardFromDeck(&p->deck, &drawnCard)) {
            insertPlayerHandCard(&p->hand, drawnCard);
        }
    }

    return e;
}


/*cria um monstro*/
/*e retorna a entidade monstro*/
entity CreateMonster(int life, tp_fila *action){
    monster *m;
    do {
        m = (monster *) malloc(sizeof(monster));
    }while(m == NULL);
    if(fila_vazia(action)) return (entity){-1, -1, NULL, NULL};
    *m->action = *action;
    entity e = {.life = life, .shield = 0, .player = NULL, .monster = m};
    return e;
}

//Deleta uma entidade
void DeleteEntity(entity *e){
    if(isEntityAPlayer(e)){
        free(e->player);
    }else if(isEntityAMonster(e)){
        free(e->monster);
    }
    e->life = -1;
    e->shield = -1;
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
    printf("\nMonstro\nVida: %d\nAction: %s - %d", e->life, e->monster->action->ini->type, e->monster->action->ini->power);
    return 1;
}

//retorna se o ataque foi realizado ou n
int attackEntity(entity *attackentity, entity *defence_entity, int power){
    int pp = isEntityAPlayer(attackentity); // pp = possivel jogador
    int pm = isEntityAMonster(defence_entity); // pm = possivel monstro
    if(pp == !pm) return 0;
        int restshield = defence_entity->shield -power;
        if(restshield < 0){
            defence_entity->life -= -restshield;
            defence_entity->shield = 0;
        }else{
            defence_entity->shield = restshield;
        }
    return 1;
}

//retorna se foi possivel adicionar escudo ou n
int addEntityShield(entity *entity1, entity *entity2, int qntshield){
    int pp = isEntityAPlayer(entity1); // pp = possivel jogador
    int pm = isEntityAMonster(entity2); // pm = possivel monstro
    if(pp == pm) return 0; 
    entity1->shield += qntshield;
    return 1;
}

/*a entidade cause e a que causa a acao, e a entidade takes e a q sofre a acao                     */
/*o tipo do 3 parametro e void pq podem ser 2 tipos de variaveis, esta descrito abaixo             */
/*valores de entrada (entity, entity, tp_fila * ou Card *, funcao de suporte[apenas para player] ) */
int EntityAction(entity *cause, entity *takes, void *action, sup_func *sup_func){
    char actiontxt[20];
    Card *selected_card;
    tp_fila *queue_action;
    if(isEntityAPlayer(cause)){

        selected_card = (Card *) action;// converte o ponteiro
        //ve se tem a carta no pilha de cartas e se ele tem energia pra isso
        if(!( (serchPlayerHandCard(&cause->player->hand, selected_card)) && (cause->player->energy -selected_card->energy_cost >= 0) ) ) return 0;
        strcpy(actiontxt, selected_card->type);

    }else if(isEntityAMonster(cause)){

        queue_action = (tp_fila *) action;
        if(fila_vazia(queue_action)) return 0;
        strcpy(actiontxt, queue_action->ini->type);

    }else { return 0; }

    if(!strcmp(actiontxt, "ATAQUE")){

        if (isEntityAPlayer(cause)){
            int ans = attackEntity(cause, takes, selected_card->power);
            if (ans) {
                deletePlayerHandCard(&cause->player->hand, selected_card);
                return 1;
            }
        }else if(isEntityAMonster(cause)){
            int ans = attackEntity(cause, takes, queue_action->ini->power);
            if (ans) {
                int old_power;
                char old_type[20];
                remove_fila(queue_action, old_type, &old_power);
                insere_fila(queue_action, old_type, old_power);
                return 1;
            }
        }


    } else if(!strcmp(actiontxt, "DEEFESA")){

        if (isEntityAPlayer(cause)){
            int ans = addEntityShield(cause, takes, selected_card->power);
            if (ans) {
                deletePlayerHandCard(&cause->player->hand, selected_card);
                return 1;
            }
        }else if(isEntityAMonster(cause)){
            int ans = addEntityShield(cause, takes, queue_action->ini->power);
            if (ans) {
                int old_power;
                char old_type[20];
                remove_fila(queue_action, old_type, &old_power);
                insere_fila(queue_action, old_type, old_power);
                return 1;
            }
        }


    } else if(!strcmp(actiontxt, "SUPORTE")){

        if (isEntityAPlayer(cause)){
            int ans = executeSupFunc(sup_func, selected_card->name, cause, takes); //falta a funcao
            if (ans) {
                deletePlayerHandCard(&cause->player->hand, selected_card);
                return 1;
            }
        }

    }

    return 0;
}