#ifndef CHARACTER_H
#define CHARACTER_H
#include "carta.h"

void MegumiCards(CardStack *deck){

    //Cartas de Ataque
    Card MegumiAtaque[4];

    //Preenchendo cada elemento das cartas de ataque
    for(int i=0; i<4; i++) strcpy(MegumiAtaque[i].type, "ATAQUE");
    
    strcpy(MegumiAtaque[0].name, "GOLPE");
    strcpy(MegumiAtaque[1].name, "CÃES DIVINOS");
    strcpy(MegumiAtaque[2].name, "NUE");
    strcpy(MegumiAtaque[3].name, "CÃO DIVINO: TOTAL");

    strcpy(MegumiAtaque[0].desc, "Golpeia o inimigo.");
    strcpy(MegumiAtaque[1].desc, "Invoca dois cães gêmeos, um pre-\nto e um branco, que atacam o al-\nvo juntos.");
    strcpy(MegumiAtaque[2].desc, "Invoca Nue, uma criatura voadura\nque eletrocuta o inimigo.");
    strcpy(MegumiAtaque[3].desc, "Mescla os cães divinos, formando\numa criatura de dano massivo.");
    
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

    strcpy(MegumiDefesa[0].desc, "Defenda o golpe do adversário.");
    strcpy(MegumiDefesa[1].desc, "Envolve o usuário em energia a- \nmaldiçoada que amortece o próxi-\nmo ataque inimigo.");
    strcpy(MegumiDefesa[2].desc, "Invoca um sapo capaz de carregar\no usuário dentro da boca, absor-\nvendo o dano do próximo ataque  \ninimigo.");
    strcpy(MegumiDefesa[3].desc, "Invoca vários coelhos que con-  \nfundem o inimigo.");

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

    strcpy(MegumiSuporte[0].name, "Concentrar");
    strcpy(MegumiSuporte[1].name, "BANSHO");
    strcpy(MegumiSuporte[2].name, "OROCHI");
    strcpy(MegumiSuporte[3].name, "SEITEI");

    strcpy(MegumiSuporte[0].desc, "A próxima carta tem -1 de custo de EA (Mínimo 1).");
    strcpy(MegumiSuporte[1].desc, "Invoca um elefante que inunda o ambiente, aumentando em 50% sua proteção nessa rodada.");
    strcpy(MegumiSuporte[2].desc, "Invoca uma cobra que que te auxilia em seu próximo ataque, aumentando em 50% seu dano nessa rodada.");
    strcpy(MegumiSuporte[3].desc, "Invoca sapos alados que atrapalham o alvo, diminuindo a proteção em 50%.");

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
#endif
