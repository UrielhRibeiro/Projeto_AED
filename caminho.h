#ifndef CAMINHO_H
#define CAMINHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entity.h"

typedef entity tp_item; // Define o tipo de dado que será armazenado no caminho

typedef struct tp_no {
    tp_item *monster;
    struct tp_no *prox;
} tp_no;

typedef struct tp_caminho {

    tp_no *ini;

} tp_caminho;

// Inicialização do caminho
void inicializa_caminho(tp_caminho *cam) {
    cam->ini = NULL;
}

int caminho_vazio(tp_caminho *caminho) {
    if (caminho->ini == NULL)
        return 1;
    return 0; // Retorna 1 se o caminho estiver vazio, senão retorna 0
}

tp_no *aloc_caminho() {
    tp_no *novo_no;
    novo_no = (tp_no *)malloc(sizeof(tp_no)); // Aloca espaço para um novo nó
    return novo_no;
}

int insere_caminho_no_fim(tp_caminho *caminho, tp_item *e) {
    tp_no *novo_no, *atu;
    novo_no = aloc_caminho(); // Aloca um novo nó
    if (novo_no == NULL || !isEntityAMonster(e)) return 0; // Retorna 0 se a alocação falhar
    novo_no->monster = e;
    novo_no->prox = NULL;
    if (caminho_vazio(caminho)) {
        caminho->ini = novo_no; // Se o caminho estiver vazio, o novo nó torna-se o primeiro
    } else {
        atu = caminho->ini;
        while (atu->prox != NULL) {
            atu = atu->prox;
        }
        atu->prox = novo_no; // Adiciona o novo nó no final do caminho
    }
    return 1; // Retorna 1 indicando sucesso na inserção
}

void imprime_caminho(tp_caminho *caminho) {
    tp_no *atu;
    atu = caminho->ini;
    printf("%s",atu->monster->monster->clas);
    while (atu != NULL) {
        printf("%s\n", atu->monster->monster->clas); // Imprime o valor do nó
        atu = atu->prox;
    }
}

int remove_caminho(tp_caminho *caminho, tp_item *e) {
    tp_no *ant, *atu;
    atu = caminho->ini;
    ant = NULL;
    while ((atu != NULL) && (atu->monster != e)) {
        ant = atu;
        atu = atu->prox;
    }
    if (atu == NULL)
        return 0; // Retorna 0 se o elemento não foi encontrado no caminho
    if (ant == NULL) {
        caminho->ini = atu->prox; // Remove o primeiro nó
    } else {
        ant->prox = atu->prox; // Remove um nó que não é o primeiro
    }
    free(atu); // Libera a memória do nó removido
    atu = NULL;
    return 1; // Retorna 1 indicando sucesso na remoção
}

tp_no *busca_caminho(tp_caminho *caminho, tp_item *e) {
    tp_no *atu;
    atu = caminho->ini;
    while ((atu != NULL) && (atu->monster != e)) {
        atu = atu->prox;
    }
    if (atu == NULL)
        return NULL; // Retorna NULL se o elemento não foi encontrado no caminho
    return atu; // Retorna um ponteiro para o nó contendo o elemento encontrado
}

int tamanho_caminho(tp_caminho *caminho) {
    int cont = 0;
    tp_no *atu;
    atu = caminho->ini;
    while (atu != NULL) {
        cont++;
        atu = atu->prox;
    }
    return cont; // Retorna o número de elementos no caminho
}

void destroi_caminho(tp_caminho *caminho) {
    tp_no *atu;
    atu = caminho->ini;
    while (atu != NULL) {
        caminho->ini = atu->prox;
        free(atu); // Libera a memória de cada nó
        atu = caminho->ini;
    }
    caminho->ini = NULL;
}

// Remoção de Elemento na Posição
int remove_elemento_posicao(tp_caminho *caminho, int posicao) {
    if (caminho_vazio(caminho) || posicao < 0) {
        return 0; // Não é possível remover de caminho vazio ou posição inválida.
    }

    if (posicao == 0) {
        tp_no *temp = caminho->ini;
        caminho->ini = caminho->ini->prox;
        free(temp);
        return 1; // Remoção bem-sucedida.
    }

    tp_no *anterior = NULL;
    tp_no *atu = caminho->ini;
    int contador = 0;

    while (atu != NULL && contador < posicao) {
        anterior = atu;
        atu = atu->prox;
        contador++;
    }

    if (atu == NULL) {
        return 0; // Posição inválida.
    }

    anterior->prox = atu->prox;
    free(atu);

    return 1; // Remoção bem-sucedida.
}

#endif
