#include "menu.h"
#include "characters.h"
#include "intro.h"

int main() {
    
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);


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

    //cria um ponteiro para se referecir ao personagens devido ao const em player na struct entity
    entity *jogador;
    if(escolhaPersonagem==1){

        printf("\nVocê escolheu Fushiguro Megumi!\nVida: 90/90\nEA: 6/6\n");

        //Cria o jogador
        entity temp = CreatePlayer(playerName, 90, 6, "Megumi");
        jogador = &temp;
        shuffleCardStack(&jogador->player->deck);
    }
    

    //Visualizar jogador
    printf("\nO seu jogador foi criado!\nVeja como ficou:\n")/
    printPlayer(jogador);

    //Visualizar o deck
    printf("\nVeja agora quais são as suas    \ncartas para esta aventura!\n");
    printCardStack(&jogador->player->deck);

    //Imprime a introdução do jogo
    intro();

    printf("\nSeja bem-vindo ao tutorial!\n");
    printPlayer(&jogador);
    printf("\nPara começar, esses valores são \nsua vida e energia amaldiçoada.\n");
    printf("\nA energia amaldiçoada é a fonte \nde seus ataques e sua principal \ndefesa contra maldições.\n");
    printf("\nPara começar, vamos ver como vo-\ncê se sai contra uma maldição de\ngrau baixo.\n");
    tp_fila *tutorial = inicializa_fila();
    // Cria o monstro
    entity monstro = CreateMonster(62, tutorial);
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