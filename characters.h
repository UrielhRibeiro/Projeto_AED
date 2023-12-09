#ifndef CHARACTER_H
#define CHARACTER_H

#include <math.h>
#include "Ientity.h"
#include "sup_func.h"

void MegumiCards(CardStack *deck){

    //Cartas de Ataque
    Card MegumiAtaque[4];

    //Preenchendo cada elemento das cartas de ataque
    for(int i=0; i<4; i++) strcpy(MegumiAtaque[i].type, "ATAQUE");
    
    strcpy(MegumiAtaque[0].name, "GOLPE");
    strcpy(MegumiAtaque[1].name, "CÃES DIVINOS");
    strcpy(MegumiAtaque[2].name, "NUE");
    strcpy(MegumiAtaque[3].name, "CÃO DIVINO-TOTAL");

    /*strcpy(MegumiAtaque[0].desc, "Golpeia o inimigo.");
    strcpy(MegumiAtaque[1].desc, "Invoca dois cães gêmeos, um preto e um branco, que atacam o alvo juntos.");
    strcpy(MegumiAtaque[2].desc, "Invoca Nue, uma criatura voadora que eletrocuta o inimigo.");
    strcpy(MegumiAtaque[3].desc, "Mescla os cães divinos, formando uma criatura de dano massivo.");*/
    
    MegumiAtaque[0].energy_cost = 1;
    MegumiAtaque[1].energy_cost = 2;
    MegumiAtaque[2].energy_cost = 4;
    MegumiAtaque[3].energy_cost = 5;

    MegumiAtaque[0].power = 6;
    MegumiAtaque[1].power = 11;
    MegumiAtaque[2].power = 18;
    MegumiAtaque[3].power = 23;

    MegumiAtaque[0].quantity = 2;
    MegumiAtaque[1].quantity = 1;
    MegumiAtaque[2].quantity = 1;
    MegumiAtaque[3].quantity = 1;

    //Cartas de Defesa
    Card MegumiDefesa[4];

    //Preenchendo cada elemento das cartas de defesa
    for(int i=0; i<4; i++) strcpy(MegumiDefesa[i].type, "DEFESA");
    
    strcpy(MegumiDefesa[0].name, "DEFENDER");
    strcpy(MegumiDefesa[1].name, "ESCUDO DE ENERGIA AMALDIÇOADA");
    strcpy(MegumiDefesa[2].name, "GAMA");
    strcpy(MegumiDefesa[3].name, "FUGA DOS COELHOS");

    /*strcpy(MegumiDefesa[0].desc, "Defenda o golpe do adversário.");
    strcpy(MegumiDefesa[1].desc, "Envolve o usuário em energia amaldiçoada que amortece o próximo ataque inimigo.");
    strcpy(MegumiDefesa[2].desc, "Invoca um sapo capaz de carregar o usuário dentro da boca, absorvendo o dano do próximo ataque inimigo.");
    strcpy(MegumiDefesa[3].desc, "Invoca vários coelhos que confundem o inimigo.");*/

    MegumiDefesa[0].energy_cost = 1;
    MegumiDefesa[1].energy_cost = 2;
    MegumiDefesa[2].energy_cost = 4;
    MegumiDefesa[3].energy_cost = 5;

    MegumiDefesa[0].power = 5;
    MegumiDefesa[1].power = 9;
    MegumiDefesa[2].power = 15;
    MegumiDefesa[3].power = 22;

    MegumiDefesa[0].quantity = 2;
    MegumiDefesa[1].quantity = 1;
    MegumiDefesa[2].quantity = 1;
    MegumiDefesa[3].quantity = 1;

    //Cartas de Suporte
    Card MegumiSuporte[4];
    //int att, def, ec;

    //Preenchendo cada elemento das cartas de suporte
    for(int i=0; i<4; i++) strcpy(MegumiSuporte[i].type, "SUPORTE");

    strcpy(MegumiSuporte[0].name, "CONCENTRAR");
    strcpy(MegumiSuporte[1].name, "BANSHO");
    strcpy(MegumiSuporte[2].name, "OROCHI");
    strcpy(MegumiSuporte[3].name, "SEITEI");

    /*strcpy(MegumiSuporte[0].desc, "Adiciona +1 de EA.");
    strcpy(MegumiSuporte[1].desc, "Invoca um elefante que inunda o ambiente, aumentando em 50% seu escudo nessa rodada.");
    strcpy(MegumiSuporte[2].desc, "Invoca uma cobra que que te auxilia em seu próximo ataque, aumentando em 50% seu dano nessa rodada.");
    strcpy(MegumiSuporte[3].desc, "Invoca sapos alados que atrapalham o alvo, diminuindo a proteção em 50%.");*/

    MegumiSuporte[0].energy_cost = 0;
    MegumiSuporte[1].energy_cost = 0;
    MegumiSuporte[2].energy_cost = 0;
    MegumiSuporte[3].energy_cost = 0;

    MegumiSuporte[0].power = 0;
    MegumiSuporte[1].power = 0;
    MegumiSuporte[2].power = 0;
    MegumiSuporte[3].power = 0;

    MegumiSuporte[0].quantity = 1;
    MegumiSuporte[1].quantity = 1;
    MegumiSuporte[2].quantity = 1;
    MegumiSuporte[3].quantity = 1;

    //Passando todas as cartas pro deck
    for(int i=0; i<4; i++){
        //Passa as cartas repetidamente N número de vezes para o deck, N = quantidade pré-definida
        for(int j=0; j<MegumiAtaque[i].quantity; j++)  pushCard(deck, &MegumiAtaque[i]);  
        for(int j=0; j<MegumiDefesa[i].quantity; j++)  pushCard(deck, &MegumiDefesa[i]);
        for(int j=0; j<MegumiSuporte[i].quantity; j++) pushCard(deck, &MegumiSuporte[i]);   
    }
}

int Megumi_supfunc_EA(entity *causes, entity *takes){
    int r1 = isEntityAPlayer(causes);
    if(r1 == 1){
        causes->player->energy++;
        return 1;
    }
    printf("\n%s | %s\n", causes->player->character, takes->monster->clas);
    return 0;
}

int aumentou_dano = 0; 

int Megumi_supfunc_attack(entity *causes,entity *takes) {
    int r1 = isEntityAPlayer(causes);

    if (r1 == 1) { //Verificação 
        for (phand_no *card_node = causes->player->hand.first; card_node != NULL; card_node = card_node->next) {
            //Aumenta o dano da carta multiplicando por 1.5
            if( !strcmp(card_node->card.type , "DEFESA")){
                card_node->card.power *= 1.5;
            }
            //Comentado pra ver se vai arredondar ou não 
            //card_node->card.damage = ceil(card_node->card.damage * 1.5);
        }

        aumentou_dano = 1; 

        return 1;//Funcionou
    }
    printf("\n%s | %s\n", causes->player->character, takes->monster->clas);
    return 0;//Não funcionou 
}


int Megumi_supfunc_shield(entity *causes, entity *takes){
    int r1 = isEntityAPlayer(causes);
    if(r1 == 1){
        initialshield = causes->shield; //Vai definir o escudo inicial 
        causes->shield = ceil(causes->shield*1.5);
        return 1;
    }
    printf("\n%s | %s\n", causes->player->character, takes->monster->clas);
    return 0;
}

int Megumi_supfunc_hitshield(entity *causes, entity *takes){
    int r1 = isEntityAPlayer(causes);
    int r2 = isEntityAMonster(takes);
    if(r1 == r2 && r1 == 1){
        takes->shield /= 1.5;
        return 1;
    }

    return 0;
}


void Megumi_Reset(entity *player, entity *monster){
    int isp = isEntityAPlayer(player);
    int ism = isEntityAMonster(monster);
    if(isp){
        //Resetar Ataque
        if(aumentou_dano){
            for (phand_no *card_node = player->player->hand.first; card_node != NULL; card_node = card_node->next) {
            //Diminui o dano da carta dividindo por 1.5
            if( !strcmp(card_node->card.type , "DEFESA")){
                card_node->card.power /= 1.5;
            } 
            //Comentado pra ver se vai arredondar ou não 
            //card_node->card.damage = ceil(card_node->card.damage * 1.5);
            }
        }
        if(ism) monster->shield = 0;
        player->shield = 0;
    }
}  

#endif

