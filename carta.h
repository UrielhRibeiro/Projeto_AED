#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Card {
    char type[20];
    char name[20];
    int energy_cost;
    int power;
    struct Card *next;
} Card;

typedef struct CardStack {
    Card *top;
} CardStack;

/* Inicializa a pilha de cartas */
void initCardStack(CardStack *stack) {
    stack->top = NULL;
}

/* Adiciona uma carta à pilha de cartas */
int pushCard(CardStack *stack, const Card *newCard) {
    Card *card = (Card *)malloc(sizeof(Card));
    if (card == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para a carta.\n");
        exit(1);
    }
    strcpy(card->name, newCard->name);
    strcpy(card->type, newCard->type);
    card->energy_cost = newCard->energy_cost;
    card->power = newCard->power;
    card->next = stack->top;
    stack->top = card;
    return 1;
}

/* Remove o primeiro elemento da pilha de cartas */
int popCard(CardStack *stack, Card *data) {
    if (stack->top == NULL) {
        fprintf(stderr, "Erro: Tentativa de remover de uma pilha vazia.\n");
        return 0; // Pilha vazia
    }
    Card *temp = stack->top;
    stack->top = temp->next;
    if (data != NULL) {
        strcpy(data->name, temp->name);
        strcpy(data->type, temp->type);
        data->energy_cost = temp->energy_cost;
        data->power = temp->power;
    }
    free(temp);
    return 1;
}

/* Libera a memória ocupada pela pilha de cartas */
void clearCardStack(CardStack *stack) {
    while (stack->top != NULL) {
        popCard(stack, NULL);
    }
}

/* Verifica se há pelo menos 1 carta igual a outra */
int hasSameCard(const CardStack *stack1, const CardStack *stack2) {
    if (stack1->top == NULL || stack2->top == NULL) {
        fprintf(stderr, "Erro: Pelo menos uma das pilhas está vazia.\n");
        return 0;
    }

    CardStack tempStack1, tempStack2;
    initCardStack(&tempStack1);
    initCardStack(&tempStack2);

    int hasSame = 0;

    while (stack1->top != NULL) {
        Card card1;
        if (!popCard((CardStack *)stack1, &card1)) {
            fprintf(stderr, "Erro ao remover carta da primeira pilha.\n");
            return 0;
        }
        pushCard(&tempStack1, &card1);

        while (stack2->top != NULL) {
            Card card2;
            if (!popCard((CardStack *)stack2, &card2)) {
                fprintf(stderr, "Erro ao remover carta da segunda pilha.\n");
                return 0;
            }
            pushCard(&tempStack2, &card2);

            if (strcmp(card1.type, card2.type) == 0 &&
                card1.energy_cost == card2.energy_cost &&
                card1.power == card2.power) {
                hasSame = 1;
                break; // Carta encontrada
            }
        }

        while (tempStack2.top != NULL) {
            Card card2;
            popCard(&tempStack2, &card2);
            pushCard((CardStack *)stack2, &card2);
        }

        if (hasSame) {
            break;
        }
    }

    // Restaurar as pilhas originais
    while (tempStack1.top != NULL) {
        Card card1;
        popCard(&tempStack1, &card1);
        pushCard((CardStack *)stack1, &card1);
    }

    clearCardStack(&tempStack1);
    clearCardStack(&tempStack2);

    return hasSame;
}
