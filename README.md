# 💻 Projeto AED - Slay the Spire 💻

## Contexto do projeto 📖: 

Slay the Spire é um jogo de cartas com elementos de roguelike desenvolvido e publicado pela Mega Crit Games, em 2019. Nele, o jogador constrói um baralho poderoso para enfrentar
inimigos, com uma jogabilidade dinâmica e desafios procedurais.

## Objetivo do projeto 💡: 

Criar um jogo inspirado no Slay the Spire utilizando a linguagem C para que o jogador possa avançar no mapa para derrotar o chefe no final.

## Como jogar ❓:

- O jogo é de um jogador contra o computador.
- O jogador inicia o jogo com um deck de 10 cartas, posicionado no início do mapa.

## Especificações do projeto ⚙️: 

 - O programa deve ser projetado para um jogador x computador.
   
 - O programa deve solicitar o nome dos jogadores.
   
 - Os monstros, cartas, encontros e o jogador, devem podem ser construídos
   livremente, desde que sigam as especificações.
   
 - Devem ser feitos pelo menos 5 monstros diferentes (sendo um deles o
   Chefe final).
   
 - Devem ser feitas, pelo menos 4, cartas de cada tipo (ataque, defesa e
  efeitos especiais), de diferentes níveis (1-4) com diferentes valores e
  custos.

 - O programa deve fazer uso das estruturas de dados e algoritmos mais
   adequados ao problema.

 - Dentre as estruturas de dados lineares utilizadas no programa, uma delas
   pelo menos deve ser implementada através de alocação dinâmica.

 - Para cada jogador, deve-se armazenar em disco as cartas lançadas à mesa
   em cada combate, e até que nível ele chegou. Essa informação pode ser
   solicitada para ser aprela.
  


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CARTAS 5
#define MAX_DECKS 3

typedef struct {
    int dados[MAX_CARTAS];
    int topo;
} Pilha;

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int estaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

int estaCheia(Pilha *pilha) {
    return pilha->topo == MAX_CARTAS - 1;
}

void empilhar(Pilha *pilha, int carta) {
    if (!estaCheia(pilha)) {
        pilha->topo++;
        pilha->dados[pilha->topo] = carta;
    }
}

int desempilhar(Pilha *pilha) {
    if (!estaVazia(pilha)) {
        int carta = pilha->dados[pilha->topo];
        pilha->topo--;
        return carta;
    }
    return -1; // Retorna um valor inválido para indicar falha
}

int jogarJogo() {
    Pilha decks[MAX_DECKS];
    int deckEscolhido, cartasRemovidas = 0, carta, soma = 0;

    for (int i = 0; i < MAX_DECKS; i++) {
        inicializarPilha(&decks[i]);
        for (int j = 0; j < MAX_CARTAS; j++) {
            carta = rand() % 10 + 1; // Gerando cartas aleatórias de 1 a 10
            empilhar(&decks[i], carta);
        }
    }

    printf("Escolha um deck (0, 1 ou 2): ");
    scanf("%d", &deckEscolhido);

    while (cartasRemovidas < 3) {
        printf("Escolha uma carta para remover do deck (1 a 5): ");
        scanf("%d", &carta);
        if (carta >= 1 && carta <= 5) {
            carta = desempilhar(&decks[deckEscolhido]);
            if (carta != -1) {
                soma += carta;
                cartasRemovidas++;
            } else {
                printf("Seleção de carta inválida.\n");
            }
        } else {
            printf("Seleção de carta inválida.\n");
        }
    }

    if (soma % 3 == 0) {
        printf("Parabéns! Você venceu.\n");
        return 1;
    } else {
        printf("Desculpe, você não venceu desta vez.\n");
        return 0;
    }
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    jogarJogo();
    return 0;
}

