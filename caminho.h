#ifndef CAMINHO_H
#define CAMINHO_H
#include <stdio.h>
#include <stdlib.h>

typedef int tp_item;

typedef struct tp_no {
    tp_item info;
    struct tp_no *prox;
} tp_caminho;

// Inicialização da lista
tp_caminho *inicializa_caminho() {
    return NULL;
}

int caminho_vazio(tp_caminho *lista) {
    if (lista == NULL)
        return 1;
    return 0;
}

tp_caminho *aloc_caminho() {
    tp_caminho *novo_no;
    novo_no = (tp_caminho *)malloc(sizeof(tp_caminho));
    return novo_no;
}

int insere_caminho_no_fim(tp_caminho **lista, tp_item e) {
    tp_caminho *novo_no, *atu;
    novo_no = aloc_caminho();
    if (novo_no == NULL)
        return 0;
    novo_no->info = e;
    novo_no->prox = NULL;
    if (caminho_vazio(*lista)) {
        *lista = novo_no;
    } else {
        atu = *lista;
        while (atu->prox != NULL) {
            atu = atu->prox;
        }
        atu->prox = novo_no;
    }
    return 1;
}

void imprime_caminho(tp_caminho *lista) {
    tp_caminho *atu;
    atu = lista;
    while (atu != NULL) {
        printf("%d\n", atu->info);
        atu = atu->prox;
    }
}

int remove_caminho(tp_caminho **lista, tp_item e) {
    tp_caminho *ant, *atu;
    atu = *lista;
    ant = NULL;
    while ((atu != NULL) && (atu->info != e)) {
        ant = atu;
        atu = atu->prox;
    }
    if (atu == NULL)
        return 0;
    if (ant == NULL) {
        *lista = atu->prox;
    } else {
        ant->prox = atu->prox;
    }
    free(atu);
    atu = NULL;
    return 1;
}

tp_caminho *busca_caminho(tp_caminho *lista, tp_item e) {
    tp_caminho *atu;
    atu = lista;
    while ((atu != NULL) && (atu->info != e)) {
        atu = atu->prox;
    }
    if (atu == NULL)
        return NULL;
    return atu;
}

int tamanho_caminho(tp_caminho *lista) {
    int cont = 0;
    tp_caminho *atu;
    atu = lista;
    while (atu != NULL) {
        cont++;
        atu = atu->prox;
    }
    return cont;
}

void destroi_caminho(tp_caminho **lista) {
    tp_caminho *atu;
    atu = *lista;
    while (atu != NULL) {
        *lista = atu->prox;
        free(atu);
        atu = *lista;
    }
    *lista = NULL;
}

// Remoção de Elemento na Posição
int remove_elemento_posicao(tp_caminho **lista, int posicao) {
    if (caminho_vazio(*lista) || posicao < 0) {
        return 0; // Não é possível remover de lista vazia ou posição inválida.
    }

    if (posicao == 0) {
        tp_caminho *temp = *lista;
        *lista = (*lista)->prox;
        free(temp);
        return 1; // Remoção bem-sucedida.
    }

    tp_caminho *anterior = NULL;
    tp_caminho *atu = *lista;
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
