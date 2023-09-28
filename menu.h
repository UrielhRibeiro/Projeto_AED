#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

char* GameStart(){
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
    static char playerName[20];
    char option[8];
    int validOption;
    printf("Seja bem vindo jogador!\n");
    printf("insira aqui seu nome:");
     fgets(playerName, sizeof(playerName), stdin);
    playerName[strcspn(playerName, "\n")] = '\0';
    printf("Ola, %s\n",playerName);
    printf("Voce gostaria de iniciar o tutorial?\n");
     do{
        scanf("%s",option);
        if (stricmp(option, "sim")==0){
         validOption=1;
    }
        else if(stricmp(option, "nao")==0){
         break;
         
    }
        else{
         printf("Opcao invalida,tente novamente");
    }
    }while(!validOption);

    return playerName;
    SetConsoleOutputCP(CPAGE_DEFAULT);
}

void GameCredits(){
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
    printf("-----------Creditos-------------\n");
    printf("--------------------------------\n");
    printf("---------Colaboradores----------\n");
    printf("--------------------------------\n");
    printf("---------Andrei Rehem-----------\n");
    printf("--------Guilherme Gradin--------\n");
    printf("-------Miguel Bernardino--------\n");
    printf("--------Uriel Henrique----------\n");
    printf("--------------------------------\n");
     SetConsoleOutputCP(CPAGE_DEFAULT);
}


void startMenu(){
     UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
    setlocale(LC_ALL,"Portuguese");
    char option[8];
    int validOption;
    printf("--------Nome do Jogo-----------\n");
    printf("-------------------------------\n");
    printf("-----------Jogar---------------\n");
    printf("----------Creditos-------------\n");
    printf("------------Sair---------------\n");
    printf("-------------------------------\n");
    printf("digite aqui sua opção:");
    do{
    scanf("%s",option);
    if (stricmp(option, "jogar")==0){
        GameStart();
        validOption=1;
    }
    else if(stricmp(option, "creditos")==0){
        GameCredits();
        validOption=1;
    }
    else if (stricmp(option, "sair") == 0) {
            printf("Obrigado por jogar! Saindo do jogo...\n");
            break;
        }
    else{
        printf("Opcao invalida,tente novamente.");
    }
    }while(!validOption);
 SetConsoleOutputCP(CPAGE_DEFAULT);
}

#endif


