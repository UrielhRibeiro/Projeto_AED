#include "caminho.h"
#include "menu.h"
#include "characters.h"
#include "intro.h"
#include "save.h"

int main() {
    
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    FILE *arquivo = fopen("save.data", "w");
    fclose(arquivo);

    // Inicia o menu 
    startMenu();
    
    // Obtenha o nome do jogador
    char playerName[20];
    struct SaveData savedData;
    strcpy(savedData.playerName, "Jogador1");
    
    strcpy(playerName, GameStart());

    


    //Seleção de personagem
    int escolhaPersonagem;
    entity *jogador;
    sup_func j1;

    printf("\nEscolha o personagem que deseja jogar:\n1.Fushiguro Megumi\n");
    scanf(" %d", &escolhaPersonagem);
    while(escolhaPersonagem!=1){
        printf("Escolha uma opção válida.");
        scanf(" %d", &escolhaPersonagem);
    }

    //cria um ponteiro para se refereciar aos personagens devido ao const em player na struct entity
    initSupFunc(&j1);
    if(escolhaPersonagem==1){

        printf("\nVocê escolheu Fushiguro Megumi!\nVida: 90/90\nEA: 6/6\n");

        //Cria o jogador
        entity temp = CreatePlayer(playerName, 90, 6, "Megumi", &j1);
        jogador = &temp;
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
    
    continuar();

    //Criando o caminho
    caminho cam;
    start_caminnho(&cam);

    //Criação dos 5 Monstros
    tp_fila *cl4 = inicializa_fila();
    preencher_fila(cl4);
    char str1[20] = "cl4";
    entity classe4 = CreateMonster(str1, 1, cl4);
    addCaminho(&classe4, &cam); 

    tp_fila *cl3 = inicializa_fila();
    preencher_fila(cl3);
    char str2[20] = "cl3";
    entity classe3 = CreateMonster(str2, 1, cl3);
    addCaminho(&classe3, &cam); 

    tp_fila *cl2 = inicializa_fila();
    preencher_fila(cl2);
    entity classe2 = CreateMonster("cl2", 1, cl2);
    addCaminho(&classe2, &cam); 
    Sleep(1);

    tp_fila *cl1 = inicializa_fila();
    preencher_fila(cl1);
    entity classe1 = CreateMonster("cl1", 1, cl1);
    addCaminho(&classe1, &cam); 

    tp_fila *clesp = inicializa_fila();
    preencher_fila(clesp);
    entity classeEsp = CreateMonster("clesp", 1, clesp);
    addCaminho(&classeEsp, &cam); 
    Sleep(1);

    addRest(&cam); 
    Sleep(1);

    addRest(&cam); 
    Sleep(1);

    printf("Esse é o caminho pelo qual você \nirá percorrer:\n\n");

    imprime_caminho(&cam);

    continuar();


    //Primeiro combate
    printf("Vamos ver como você se sai no   \nseu primeiro combate.\n");
    printf("\nOs monstros possuem valores mí- \nnimos e máximos de ataque e es- \ncudo. Eles podem efetuar uma jo-\ngada por rodada utilizando esses\nvalores.\n\n");
    CardStack descarte;
    initCardStack(&descarte);
    Card drawnCard;
    do{
        if(cam.cam_no->isrest){
            jogador->life = 90;
            cam.cam_no = cam.cam_no->prox;
        }
        while(isEntityAlive(jogador) && isEntityAlive(cam.cam_no->entity)){
            //Mantém o jogador sempre com 5 cartas
            int v = countPlayerHand(&jogador->player->hand);
            for(int i=5; i>v; i--){
                if (popCard(&jogador->player->deck, &drawnCard)) {
                    insertPlayerHandCard(&jogador->player->hand, drawnCard);
                }    
            }
            while(isEntityAlive(cam.cam_no->entity)){
                int op=0, resp=1;
                printf("\nSua mão:");
                printPlayerHand(&jogador->player->hand);
                printMonster(cam.cam_no->entity);
                printPlayer(jogador);
                printf("Deseja continuar?\n(1)-SIM\n(0)-NÃO\n");
                scanf("%d", &resp);
                if(!resp) break;
                printf("\nQual carta deseja utilizar?\n");
                scanf("%d", &op);
                if(op > countPlayerHand(&jogador->player->hand)) {
                    printf("\nDigite novamente qual carta deseja utilizar?\n");
                    scanf("%d", &op);              
                }
                EntityAction(jogador, cam.cam_no->entity, (void*) searchPlayerHandCard2(&jogador->player->hand, op), &j1, &descarte);
            }
            EntityAction(cam.cam_no->entity, jogador, (void*) cam.cam_no->entity->monster->action, NULL, NULL);
            Megumi_Reset(jogador, cam.cam_no->entity);
        } 


        //adicionar a pilha de descarte
        //e adicionar o nivel
        savedData.playedCards = &descarte;
        strcpy(savedData.playerName, playerName);
        strcpy(savedData.playerLevel, cam.cam_no->entity->monster->clas);
        save_playedCard("save.data",&savedData);

        // Verifique o resultado da partida e exiba uma mensagem apropriada

        if(!strcmp(cam.cam_no->entity->monster->clas, "clesp")){
            printf("\nParabéns %s! Você venceu o jogo!\n", playerName);
            break;
        }else if (isEntityAlive(jogador)) {
            printf("\nParabéns %s! Você venceu o monstro: %s!\n", playerName, cam.cam_no->entity->monster->clas);
        } else {
            printf("Você perdeu...\n");
            GameCredits(); // Exiba os créditos do jogo 
            break;
        }        


        mergeCards(&jogador->player->deck, &descarte, jogador->player);
        shuffleCardStack(&jogador->player->deck);
        shuffleCardStack(&jogador->player->deck);
        shuffleCardStack(&jogador->player->deck);

        int r;
        do{
            if(cam.cam_no->rest != NULL){
                printf("\nVocê deseja continuar o proximo combate ou descaçar (0: Combate | 1: Descançar): ");
                scanf(" %d", &r);
            }else r = 0;
        }while( ! (r == 1 || r == 0));
        if(r){
            cam.cam_no = cam.cam_no->rest;
            printf("\nVocê ira batalhar com o monstro: %s\n", cam.cam_no->prox->entity->monster->clas);
            continuar();
            continue;
        }   

        cam.cam_no = cam.cam_no->prox;
        printf("\nVocê ira batalhar com o monstro: %s\n", cam.cam_no->entity->monster->clas);
        continuar();

    }while(cam.cam_no !=  NULL);
    SetConsoleOutputCP(CPAGE_DEFAULT);
    return 0;
}