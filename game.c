#include "menu.h"
#include "characters.h"
#include "intro.h"
#include "caminho.h"
#include "sup_func.h"

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

    //cria um ponteiro para se refereciar aos personagens devido ao const em player na struct entity
    entity *jogador;
    sup_func j1;
    initSupFunc(&j1);
    if(escolhaPersonagem==1){

        printf("\nVocê escolheu Fushiguro Megumi!\nVida: 90/90\nEA: 6/6\n");

        //Cria o jogador
        printf("\n1\n");
        entity temp = CreatePlayer(playerName, 90, 6, "Megumi", &j1);
        printf("\n1\n");
        jogador = &temp;
        printf("\n1\n");
    }
    

    //Visualizar jogador
    printf("\nO seu jogador foi criado!\nVeja como ficou:\n");
    printPlayer(jogador);

    continuar();

    //Visualizar o deck
    printf("\nVeja agora quais são as suas    \ncartas para esta aventura!\n");
    printCardStack(&jogador->player->deck);

    continuar();

    //Imprime a introdução do jogo
    intro();

    continuar();

    printf("\nSeja bem-vindo ao tutorial!\n");
    printPlayer(jogador);
    printf("\nPara começar, esses valores são \nsua vida e energia amaldiçoada.\n");
    printf("\nA energia amaldiçoada é a fonte \nde seus ataques e sua principal \ndefesa contra maldições.\n");
    printf("\nPara começar, vamos ver como vo-\ncê se sai contra uma maldição de\ngrau baixo.\n");
    
    
    //Criação dos 5 Monstros
    tp_fila *cl4 = inicializa_fila();
    preencher_fila(cl4);
    entity classe4 = CreateMonster("cl4", 62, cl4);

    tp_fila *cl3 = inicializa_fila();
    preencher_fila(cl3);
    entity classe3 = CreateMonster("cl3", 84, cl3);

    tp_fila *cl2 = inicializa_fila();
    preencher_fila(cl2);
    entity classe2 = CreateMonster("cl2", 98, cl2);

    tp_fila *cl1 = inicializa_fila();
    preencher_fila(cl1);
    entity classe1 = CreateMonster("cl1", 110, cl1);

    tp_fila *clesp = inicializa_fila();
    preencher_fila(clesp);
    entity classeEsp = CreateMonster("clesp", 135, clesp);
    continuar();

    //Criando o caminho
    tp_caminho game;
    inicializa_caminho(&game);
    int r = insere_caminho_no_fim(&game, &classe4);
    insere_caminho_no_fim(&game, &classe3);
    insere_caminho_no_fim(&game, &classe2);
    insere_caminho_no_fim(&game, &classe1);
    insere_caminho_no_fim(&game, &classeEsp);
    

    printf("Esse é o caminho pelo qual você \nirá percorrer:\n\n");

    imprime_caminho(&game);

    continuar();

    //Primeiro combate
    printf("Vamos ver como você se sai no   \nseu primeiro combate.\n");
    printf("\nOs monstros possuem valores mí- \nnimos e máximos de ataque e es- \ncudo. Eles podem efetuar uma jo-\ngada por rodada utilizando esses\nvalores.\n\n");
    CardStack descarte;
    initCardStack(&descarte);
    Card drawnCard;

    do{
        //Mantém o jogador sempre com 5 cartas
        int v = countPlayerHand(&jogador->player->hand);
        for(int i=5; i>v; i--){
            if (popCard(&jogador->player->deck, &drawnCard)) {
            insertPlayerHandCard(&jogador->player->hand, drawnCard);
            }
            
        }
        int aux=jogador->player->energy;

        while(1){
            int op=0, resp=1;
            printf("\nSua mão:");
            printPlayerHand(&jogador->player->hand);
            printMonster(&classe4);
            printPlayer(jogador);
            printf("\nEA restante = %d\n", jogador->player->energy);
            printf("Deseja continuar?\n(1)-SIM\n(0)-NÃO\n");
            scanf("%d", &resp);
            if(!resp) continue;
            printf("\nQual carta deseja utilizar?\n");
            scanf("%d", &op);
            if(op > countPlayerHand(&jogador->player->hand)) {
                printf("\nDigite novamente qual carta deseja utilizar?\n");
                scanf("%d", &op);              
            }
            EntityAction(jogador, &classe4, (void*)searchPlayerHandCard2(&jogador->player->hand, op), &j1);

            printMonster(&classe4);
            
        }
        jogador->player->energy=aux;
        Megumi_Reset(jogador);
        if(!isEntityAlive(jogador)) printf("GAME OVER!\n");

    }while((!isEntityAlive(jogador)) && (!isEntityAlive(&classe4)));



    /*do {
        // Realize um round de combate
        Round(&jogador, &monstro);
    } while (isEntityAlive(&jogador) && !isEntityAlive(&monstro));*/

    // Verifique o resultado da partida e exiba uma mensagem apropriada
    if (isEntityAlive(jogador)) {
        printf("Parabéns %s! Você venceu!\n", playerName);
    } else {
        printf("Você perdeu...\n");
        GameCredits(); // Exiba os créditos do jogo 
    }

    destroi_caminho(&game);

    SetConsoleOutputCP(CPAGE_DEFAULT);
    return 0;
}