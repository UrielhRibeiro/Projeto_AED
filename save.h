#include "carta.h"
#include "entity.h"

struct SaveData {
    CardStack playedCards;
};

// Função para salvar dados em um arquivo
void save_playedCard(const char *nomeArquivo, const struct SaveData *dados){

    FILE *arquivo = fopen(nomeArquivo, "wb"); // "wb" para abrir o arquivo em modo de escrita binária

    if (arquivo != NULL) {
        fwrite(dados, sizeof(struct SaveData), 1, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }
}

// Função para carregar dados de um arquivo
void load_savedCard(const char *nomeArquivo, struct SaveData *dados){
    FILE *arquivo = fopen(nomeArquivo, "rb"); // "rb" abre o arquivo em modo de leitura binária

    if (arquivo != NULL) {
        fread(dados, sizeof(struct SaveData), 1, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo para leitura.\n");
    }
}