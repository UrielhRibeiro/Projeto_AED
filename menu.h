#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

void GameStart(){

    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    char playerName[20];
    printf("Seja bem vindo jogador!\n");
    printf("insira aqui seu nome:");
    scanf("%s",playerName);
    printf("Olá, %s!",playerName);

    SetConsoleOutputCP(CPAGE_DEFAULT);
}

void GameCredits(){

    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    printf("------------Créditos------------\n");
    printf("--------------------------------\n");
    printf("---------Colaboradores----------\n");
    printf("--------------------------------\n");
    printf("----------Andrei Rehem----------\n");
    printf("--------Guilherme Gradin--------\n");
    printf("--------Miguel Bernardino-------\n");
    printf("---------Uriel Henrique---------\n");
    printf("--------------------------------\n");

    SetConsoleOutputCP(CPAGE_DEFAULT);
}

void menu(){

    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    char option[8];
    int validOption;
    printf("---------Nome do Jogo-----------\n");
    printf("--------------------------------\n");
    printf("------------Jogar---------------\n");
    printf("-----------Créditos-------------\n");
    printf("--------------------------------\n");
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
    else{
        printf("Opcao invalida,tente novamente");
    }
    }while(!validOption);



    SetConsoleOutputCP(CPAGE_DEFAULT);
}

#endif