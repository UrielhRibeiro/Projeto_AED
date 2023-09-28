#include <stdio.h>
#include <locale.h>
#include <string.h>

void GameStart(){
    char playerName[20];
    printf("Seja bem vindo jogador!\n");
    printf("insira aqui seu nome:");
    scanf("%s",playerName);
    printf("Ola, %s",playerName);

}

void GameCredits(){
    printf("-----------Creditos------------\n");
    printf("--------------------------------\n");
    printf("---------Colaboradores----------\n");
    printf("--------------------------------\n");
    printf("---------Andrei Rehem-----------\n");
    printf("--------Guilherme Gradin--------\n");
    printf("-------Miguel Bernardino--------\n");
    printf("--------Uriel Henrique----------\n");
    printf("--------------------------------\n");
}


int main(){
    setlocale(LC_ALL,"Portuguese");
    char option[8];
    int validOption;
    printf("--------Nome do Jogo-----------\n");
    printf("-------------------------------\n");
    printf("-----------Jogar---------------\n");
    printf("----------Creditos-------------\n");
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
    else{
        printf("Opcao invalida,tente novamente");
    }
    }while(!validOption);

        
   
    return 0;
}
