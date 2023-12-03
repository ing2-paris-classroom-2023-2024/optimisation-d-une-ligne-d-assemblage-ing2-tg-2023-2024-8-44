#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

// Initialiser une pile vide
void initializeStack(Stack *stack, int capacity) {
    stack->operation = (int *)malloc(capacity * sizeof(int));
    if (stack->operation == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;
    stack->nbOpe=0;
    stack->top = -1;  // La pile est vide initialement
}

// Vérifier si la pile est vide
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Vérifier si la pile est pleine
int isFull(Stack *stack, float tempsDeCyleMax, float tempsDeCycleOp) {
    return (stack->top == stack->capacity - 1|| stack->tempsDeCyle+tempsDeCycleOp>=tempsDeCyleMax);
}

// Empiler un élément sur la pile
int push(Stack *stack, int item, float tempsDeCyleMax,float tempsDeCycleOp, int degre) {
    if (isFull(stack,tempsDeCyleMax,tempsDeCycleOp)||degre == -1) {
//       \\
        return 0;
    }
    stack->operation[++stack->top] = item;
    stack->tempsDeCyle+=tempsDeCycleOp;
    stack->nbOpe++;
    return 1;
}

// Dépiler un élément de la pile
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "La pile est vide. Impossible de dépiler un élément.\n");
        exit(EXIT_FAILURE);
    }
    return stack->operation[stack->top--];
}

// Afficher les éléments de la pile
void display(Stack *stack) {
    if (isEmpty(stack)) {
        printf("La pile est vide.\n");
        return;
    }
    printf("Contenu de la pile :\n");
    for (int i = 0; i <= stack->top; ++i) {
        printf("%d ", stack->operation[i]);
    }
    printf("\ntemps de cycle de la station : %f\n",stack->tempsDeCyle);
}

// Libérer la mémoire allouée pour la pile
void freeStack(Stack *stack) {
    free(stack->operation);
}