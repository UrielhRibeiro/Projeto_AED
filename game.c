#include "entity/entity.h"
#include "menu.h"
#include "characters.h"
#include "intro.h"

void Round_Finished(entity *player, entity *monster){
    if(isEntityAPlayer(player) && isEntityAMonster(monster)){
        player->shield = 0;
        monster->shield = 0;
    }
}

// Função para realizar um round de combate entre um jogador e um monstro
void Round(player *jogador, monster *monstro) {
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

    // Use a carta do jogador contra o monstro
    /*useEntitycard(jogador, monstro, &playerCard);
    printf("Vida da maldição: %d Escudo da maldição: %d\n", monstro->life, monstro->shield);

    // Use a carta do monstro contra o jogador
    useEntitycard(monstro, jogador, &monsterCard);
    printf("Vida: %d Energia amaldiçoada: %d\n", jogador->life, jogador->energy);*/

    Round_Finished();
}

int main() {
    
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    // Crie o jogador e o monstro
    player jogador;
    monster monstro;

    // Inicia o menu 
    startMenu();
    
    // Obtenha o nome do jogador
    char playerName[20];

    strcpy(playerName, GameStart());

    
    //Seleção de personagem
    int escolhaPersonagem;
    printf("\nEscolha o personagem que deseja jogar:\n1.Fushiguro Megumi\n");
    scanf("%d", &escolhaPersonagem);
    while(escolhaPersonagem!=1){
        printf("Escolha uma opção válida.");
        scanf("%d", &escolhaPersonagem);
    }
    
    if(escolhaPersonagem==1){

        printf("\nVocê escolheu Fushiguro Megumi!\nVida: 90/90\nEA: 6/6\n");

        //Cria o jogador
        jogador = CreatePlayer(playerName, 90, 6, "Megumi");
        shuffleCardStack(&jogador.deck);
    }
    

    //Visualizar jogador
    printf("\nO seu jogador foi criado!\nVeja como ficou:\n")/
    printPlayer(&jogador);

    //Visualizar o deck
    printf("\nVeja agora quais são as suas    \ncartas para esta aventura!\n");
    printCardStack(&jogador.deck);

    //Imprime a introdução do jogo
    intro();

    printf("\nSeja bem-vindo ao tutorial!\n");
    printPlayer(&jogador);
    printf("\nPara começar, esses valores são \nsua vida e energia amaldiçoada.\n");
    printf("\nA energia amaldiçoada é a fonte \nde seus ataques e sua principal \ndefesa contra maldições.\n");
    printf("\nPara começar, vamos ver como vo-\ncê se sai contra uma maldição de\ngrau baixo.\n");
    monstro = CreateMonster(62, 5, 8, 7, 12);
    printMonster(&monstro);
    printf("\nOs monstros possuem valores mí-\nnimos e máximos de ataque e es-\ncudo. Eles podem efetuar um jo-\ngada por rodada utilizando esses\nvalores.");

    printf("\n\nObrigado por jogar!\nNovas versões virão em breve!");
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

    SetConsoleOutputCP(CPAGE_DEFAULT);
    return 0;
}