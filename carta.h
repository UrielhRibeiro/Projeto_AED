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

/* Verifica se há pelo menos 1 carta igual a outra dentro de uma única pilha */
int hasSameCardInStack(CardStack stack, Card selected_card) {
    if (stack.top == NULL) {
        fprintf(stderr, "Erro: A pilha está vazia.\n");
        return 0;
    }

    CardStack tempStack;
    initCardStack(&tempStack);

    int hasSame = 0;

    while (stack.top != NULL) {
        Card card1;
        if (!popCard(&stack, &card1)) {
            fprintf(stderr, "Erro ao remover carta da pilha.\n");
            return 0;
        }
        pushCard(&tempStack, &card1);

        while (tempStack.top != NULL) {
            Card card2;
            popCard(&tempStack, &card2);
            pushCard(&stack, &card2);

            if (strcmp(card1.type, card2.type) == 0 &&
                card1.energy_cost == card2.energy_cost &&
                card1.power == card2.power) {
                hasSame = 1;
                break; // Carta encontrada
            }
        }

        if (hasSame) {
            break;
        }
    }

    // Restaurar a pilha original
    while (tempStack.top != NULL) {
        Card card1;
        popCard(&tempStack, &card1);
        pushCard(&stack, &card1);
    }

    clearCardStack(&tempStack);

    return hasSame;
}


/**** Deletar um Carta ****/

int DeleteCard(){







    
}



