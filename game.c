#include "entity.h"
#include "config.h"
#include "menu.h"

// Função para realizar um round de combate entre um jogador e um monstro
void Round(entity *jogador, entity *monstro) {
    // Cria uma carta de ataque para o monstro
    Card monsterCard;
    strcpy(monsterCard.type, "attack");
    strcpy(monsterCard.name, "Monster Attack Card");
    monsterCard.energy_cost = 5;
    monsterCard.power = 10;

    // Cria uma carta de ataque para o jogador
    Card playerCard;
    strcpy(playerCard.type, "attack");
    strcpy(playerCard.name, "attack");
    playerCard.energy_cost = 5;
    playerCard.power = 15;

    // Embaralhe o baralho do jogador e do monstro
    shuffleCardStack(&(jogador->deck));
    shuffleCardStack(&(monstro->deck));

    // Use a carta do jogador contra o monstro
    useEntitycard(jogador, monstro, &playerCard);
    printf("Vida da maldição: %d Escudo da maldição: %d\n", monstro->life, monstro->shield);

    // Use a carta do monstro contra o jogador
    useEntitycard(monstro, jogador, &monsterCard);
    printf("Vida: %d Energia amaldiçoada: %d\n", jogador->life, jogador->energy);
}

int main() {
    // Obtenha o nome do jogador
    char playerName[20];
    GameStart(playerName);

    // Crie uma carta de ataque para o monstro
    Card monsterCard;
    strcpy(monsterCard.type, "attack");
    strcpy(monsterCard.name, "Monster Attack Card");
    monsterCard.energy_cost = 5;
    monsterCard.power = 10;

    // Crie o jogador e o monstro
    entity jogador = CreatePlayer(playerName, 90, 6);
    entity monstro = CreateMonster(62, 10, monsterCard);

    // Inicia o menu 
    startMenu();
    intro();
    printf("Seja bem-vindo ao tutorial %s!\n", playerName);
    printf("Vida: %d Energia amaldiçoada: %d\n", jogador.life, jogador.energy);
    printf("Para começar, esses valores são sua vida e energia amaldiçoada.\n");
    printf("A energia amaldiçoada é a fonte de seus ataques e sua principal defesa contra maldições.\n");
    printf("Para começar, vamos ver como você se sai contra uma maldição de grau baixo.\n");
    printf("Vida: %d Escudo: %d\n", monstro.life, monstro.shield);

    do {
        // Realize um round de combate
        Round(&jogador, &monstro);
    } while (isEntityAlive(&jogador) && !isEntityAlive(&monstro));

    // Verifique o resultado da partida e exiba uma mensagem apropriada
    if (isEntityAlive(&jogador)) {
        printf("Parabéns %s!! Você venceu!\n", playerName);
    } else {
        printf("Você perdeu...\n");
        GameCredits(); // Exiba os créditos do jogo 
    }

    return 0;
}