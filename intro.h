#ifndef INTRO_H
#define INTRO_H

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

//Introdução do jogo
void intro(){

    // Configuração da página de código para UTF-8
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    printf("\n");
    printf("\n--------------------------------\n");
    printf("|No Japão, por ano, há mais de |\n|10 mil casos de desaparecimen-|\n|tos e mortes sem explicações. |\n|São resultados de maldições.  |\n");
    printf("--------------------------------\n");
    printf("\n--------------------------------\n");
    printf("|Maldições se originam das emo-|\n|ções negativas sentidas pelos |\n|humanos, e se manifestam ator-|\n|mentando o resto da população.|\n");
    printf("--------------------------------\n");
    printf("\n--------------------------------\n");
    printf("|Para combatê-las, há os Feiti-|\n|ceiros Jujutsu, pessoas trei- |\n|nadas para controlar a energia|\n|amaldiçoada e ultilizá-la para|\n|exorcizar as maldições.       |\n");
    printf("--------------------------------\n");
    printf("\n--------------------------------\n");
    printf("|Nessa aventura, viva como um  |\n|Feiticeiro Jujutsu e exorcize |\n|todas as maldições que encon- |\n|trar!                         |\n");
    printf("--------------------------------\n");
    printf("\n\n");

    SetConsoleOutputCP(CPAGE_DEFAULT);
}

#endif