#ifndef CARTA_H
#define CARTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

typedef struct Card{
    char type[20];
    char name[20];
    char desc[500];
    int energy_cost;
    int power;
    int quantity;
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


/* Verifica se duas cartas são iguais */
int areCardsEqual(const Card *card1, const Card *card2) {
    if (strcmp(card1->type, card2->type) == 0 &&
        card1->energy_cost == card2->energy_cost &&
        card1->power == card2->power) {
        return 1; // Cartas são iguais
    } else {
        return 0; // Cartas não são iguais
    }
}


/**** Deletar um Carta ****/
int DeleteCard(CardStack *stack, Card *selected_card){

    if(stack -> top == NULL){
        fprintf(stderr, "Erro: A pilha está vazia.\n");
        return 0;
    } 

    CardStack tempStack; // Pilha auxiliar de cartas para ajudar a encontrar a carta e excluir 
    initCardStack(&tempStack); // Iniciliazar a pilha de cartas temporárias  

    int cardFound = 0; // Verificar de carta encontrada

      while (stack->top != NULL) { 
        Card card;
        if (!popCard(stack, &card)) {
            fprintf(stderr, "Erro ao remover carta da pilha.\n");
            return 0;
        }

        // Verificação de atribtuos da carta para remover ela 
        // Se for igual a carta selecionada (struct), em todos os atribtuos retorna 1 => carta excluída
        if (strcmp(card.type, selected_card->type) == 0 && 
            card.energy_cost == selected_card->energy_cost &&
            card.power == selected_card-> power) {
            cardFound = 1;
            continue; // Carta encontrada e excluída
        }

        pushCard(&tempStack, &card);
        
    }

    // Restaurar a pilha original pois ela foi invertida com a adição de uma pilha temporária
    // A pilha original agora não tem a carta que foi excluída 
    while (tempStack.top != NULL) {
        Card card;
        popCard(&tempStack, &card);
        pushCard(stack, &card);
    }

    clearCardStack(&tempStack); //Excluir a pilha temporária 

    if (cardFound) {
        return 1; // Carta encontrada e excluída com sucesso
    } else {
        fprintf(stderr, "Erro: A carta não foi encontrada na pilha de cartas! \n");
        return 0; // Carta não encontrada
    }
}


/* Embaralha as cartas na pilha */
void shuffleCardStack(CardStack *stack) {
    if (stack->top == NULL) {
        fprintf(stderr, "Erro: A pilha está vazia.\n");
        return;
    }

    // Inicializa a aleatoriedade com base no tempo atual
    srand(time(NULL));

    Card *cardsArray[100]; // Aqui eu assumi um valor abritário, mas pode mudar.
    int numCards = 0;

    // Copia as cartas da pilha para um array
    while (stack->top != NULL) {
        Card *card = (Card *)malloc(sizeof(Card));
        if (card == NULL) {
            fprintf(stderr, "Erro: Falha na alocação de memória para embaralhar as cartas.\n");
            exit(1);
        }
        popCard(stack, card);
        cardsArray[numCards++] = card;
    }

    // Embaralha as cartas no array
    for (int i = numCards - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        if (i != j) {
            // Troca as posições das cartas
            Card *temp = cardsArray[i];
            cardsArray[i] = cardsArray[j];
            cardsArray[j] = temp;
        }
    }

    // Empilha as cartas embaralhadas de volta na pilha original
    for (int i = 0; i < numCards; i++) {
        pushCard(stack, cardsArray[i]);
        free(cardsArray[i]); // Libera a memória alocada para o array
    }
}

void printCardStack(CardStack *stack){

    //Modifica a linguagem na qual o texto sai no terminal, aceitando assim os assentos e caracteres especiais
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    //Copia a carta no topo da stack para realizar a impressão
    Card *aux;
    int cont=1;
    aux = stack->top;
    while (aux != NULL)
    {
        //Imprime a carta e passa para a próxima
        printf("\nCARTA %d %s\nNome: %s\nCusto: %d EA\nForça: %d\n", cont, aux->type, aux->name, aux->energy_cost, aux->power);
        aux = aux->next;
        cont ++;
    }

    //Volta a linguagem do terminal para o padrão
    SetConsoleOutputCP(CPAGE_DEFAULT);
}

#endif
