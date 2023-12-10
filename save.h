#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include "carta.h"
#include "Ientity.h"

#define MAX_PLAYER_NAME 50


typedef struct SaveData {
    char playerName[MAX_PLAYER_NAME]; // Nome do jogador
    int playerLevel; // Nível alcançado pelo jogador
    CardStack playedCards; // Pilha de cartas jogadas
} SaveData;

// Função para salvar os dados do jogo em um arquivo
void save_playedCard(const char *nomeArquivo, const SaveData *dados) {
    FILE *arquivo = fopen(nomeArquivo, "wb"); // Abre o arquivo em modo de escrita binária

    if (arquivo != NULL) {
        // Escreve os dados da estrutura SaveData no arquivo
        fwrite(dados, sizeof(SaveData), 1, arquivo);
        fclose(arquivo); // Fecha o arquivo após a escrita
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }
}

// Função para carregar os dados do jogo de um arquivo
void load_savedCard(const char *nomeArquivo, SaveData *dados) {
    FILE *arquivo = fopen(nomeArquivo, "rb"); // Abre o arquivo em modo de leitura binária

    if (arquivo != NULL) {
        // Lê os dados da estrutura SaveData do arquivo
        fread(dados, sizeof(SaveData), 1, arquivo);
        fclose(arquivo); // Fecha o arquivo após a leitura
    } else {
        printf("Erro ao abrir o arquivo para leitura.\n");
    }
}

// Função para imprimir as informações das cartas jogadas e do jogador
void print_playedCard(SaveData *dados) {
    printf("Essas foram as cartas jogadas ao longo do jogo:\n");
    printCardStack(&dados->playedCards); // Chama a função para imprimir a pilha de cartas
    printf("Nome do jogador: %s\n", dados->playerName); // Imprime o nome do jogador
    printf("Nível alcançado: %d\n", dados->playerLevel); // Imprime o nível alcançado pelo jogador
}

#endif // SAVE_H
