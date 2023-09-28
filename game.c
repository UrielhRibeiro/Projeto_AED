#include "entity.h"
#include "config.h"
#include "menu.h"



// Função para realizar um round de combate entre um jogador e um monstro
void Round(entity *jogador, entity *monstro) {
    Card monsterCard;
    strcpy(monsterCard.type, "attack");
    strcpy(monsterCard.name, "Monster Attack Card");
    monsterCard.energy_cost = 5;
    monsterCard.power = 10;

    Card playerCard;
    strcpy(playerCard.type, "attack");
    strcpy(playerCard.name, "attack");
    playerCard.energy_cost = 5;
    playerCard.power = 15;
    // Embaralhe o baralho do jogador e do monstro
    shuffleCardStack(&(jogador->deck));
    shuffleCardStack(&(monstro->deck));
    
    useEntitycard(jogador,monstro,&playerCard);
    printf("Vida da maldicao: %d Escudo da maldicao: %d\n", monstro->life, monstro->shield);
    useEntitycard(monstro,jogador,&monsterCard);
    printf("Vida: %d Energia amaldicoada: %d\n", jogador->life, jogador->energy);
    
}


int main(){ 
    char* playerName = GameStart();

    Card monsterCard;
    strcpy(monsterCard.type, "attack");
    strcpy(monsterCard.name, "Monster Attack Card");
    monsterCard.energy_cost = 5;
    monsterCard.power = 10;

    entity jogador = CreatePlayer(playerName,90,6);
    entity monstro = CreateMonster(62,10,monsterCard);       
    
    startMenu();
    intro();
    printf("seja bem vindo ao tutorial %s!\n",playerName);
    printf("Vida:%d Energia amaldiçoada:%d\n",jogador.life,jogador.energy);
    printf("para começar, esses valores são sua vida e energia amaldicoada\n");
    printf("a energia amaldicoada é a fonte de seus ataques e sua principal defesa contra maldicoes\n");
    printf("para comecar vamos ver como voce se sai contra uma maldicao de grau baixo\n");
    printf("Vida:%d Escudo:%d\n",monstro.life,monstro.shield);
    
    do{
       Round(&jogador,&monstro);
    }while((isEntityAlive(&jogador)) && (isEntityAlive(&monstro))==0);
    
    

}