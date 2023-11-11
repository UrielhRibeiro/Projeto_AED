#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

// Função para obter o nome do jogador e configurar a página de código UTF-8
char* GameStart(){
    // Configuração da página de código para UTF-8
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    static char playerName[20]; // Variável para armazenar o nome do jogador
    //char option[8]; //Variável para armazenar opção escolhida
    //int validOption;//Variável para checar validez da opçãoo

    printf("Seja bem-vindo jogador!\n");
    printf("Insira aqui seu nome: ");
    // Usando fgets para ler uma linha, incluindo espaços em branco
    scanf(" %[^\n]s", playerName);
    //fgets(playerName, sizeof(playerName), stdin);
    playerName[strcspn(playerName, "\n")] = '\0'; // Remove a quebra de linha do final

    
    printf("Olá, %s!\n",playerName);
    /*printf("Você gostaria de iniciar o tutorial?\n('sim' ou 'nao')\n");
    //fazendo checagem de validez da opção
    do {
        scanf("%s",option);
        if (stricmp(option, "sim") == 0) {
            validOption = 1;
        } else if (stricmp(option, "nao") == 0) {
            continue;
        } else {
            printf("Opção inválida, tente novamente.");
        }
    } while (!validOption);
    */

    // Restaura a página de código padrão
    SetConsoleOutputCP(CPAGE_DEFAULT);

    return playerName;
}

// Função para exibir os créditos do jogo 
void GameCredits(){
    
    // Configuração da página de código para UTF-8
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    printf("------------Créditos------------\n");
    printf("--------------------------------\n");
    printf("----------Colaboradores---------\n");
    printf("--------------------------------\n");
    printf("----------Andrei Rehem----------\n");
    printf("--------Guilherme Gradin--------\n");
    printf("--------Miguel Bernardino-------\n");
    printf("---------Uriel Henrique---------\n");
    printf("--------------------------------\n");

    // Restaura a página de código padrão
    SetConsoleOutputCP(CPAGE_DEFAULT);
}

// Função para iniciar o menu do jogo 
void startMenu(){
    
    // Configuração da página de código para UTF-8
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    char option[8];
    int validOption;

    printf("----------JUJUTSU ROAD----------\n");
    printf("--------------------------------\n");
    printf("--------------Jogar-------------\n");
    printf("------------Créditos------------\n");
    printf("--------------Sair--------------\n");
    printf("--------------------------------\n");
    printf("Digite aqui sua opção:\n(Escreva em letras minúsculas sem acento)\n");
    //fazendo checagem de validez da opção e chamando função de acordo com a escolha
    do {
        scanf("%s",option);
        if (stricmp(option, "jogar") == 0) {
            //GameStart();
            validOption = 1;
        } else if (stricmp(option, "creditos") == 0) {
            GameCredits();
            validOption = 1;
        } else if (stricmp(option, "sair") == 0) {
            printf("Obrigado por jogar! Saindo do jogo...\n");
            break;
        } else {
            printf("Opção inválida, tente novamente.");
        }
    } while (!validOption);

    // Restaura a página de código padrão
    SetConsoleOutputCP(CPAGE_DEFAULT);
}

void continuar(){

    // Configuração da página de código para UTF-8
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    int conf=0;
    do{

        printf("\nDigite 1 para continuar...\n");
        scanf("%d", &conf);
        printf("\n");

    }while(!conf);

    // Restaura a página de código padrão
    SetConsoleOutputCP(CPAGE_DEFAULT);

}

#endif