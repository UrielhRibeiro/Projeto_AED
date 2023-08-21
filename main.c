#include <stdio.h>
#include <locale.h>

typedef char tipo_carta;

typedef struct cartaNo{
    tipo_carta card;
    cartaNo *prox;
}cartaNo;

typedef struct carta{
    cartaNo *topo;
}carta;

typedef struct player{
    carta deck;  
}player;

int main(){
    setlocale(LC_ALL,"Portuguese");
    
    printf("Projeto Iniciado");

    return 0;
}
