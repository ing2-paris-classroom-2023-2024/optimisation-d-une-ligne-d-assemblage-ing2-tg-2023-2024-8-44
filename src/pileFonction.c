#include <stdio.h>
#include <stdlib.h>

// Structure de la pile
typedef struct {
    int *array;     // tableau dynamique pour stocker les éléments de la pile
    int capacity;   // capacité maximale de la pile
    int top;        // indice du sommet de la pile
} Stack;

// Initialiser une pile vide
void initializeStack(Stack *stack, int capacity) {
    stack->array = (int *)malloc(capacity * sizeof(int));
    if (stack->array == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;
    stack->top = -1;  // La pile est vide initialement
}

// Vérifier si la pile est vide
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Vérifier si la pile est pleine
int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

// Empiler un élément sur la pile
void push(Stack *stack, int item) {
    if (isFull(stack)) {
        fprintf(stderr, "La pile est pleine. Impossible d'ajouter un nouvel élément.\n");
        return;
    }
    stack->array[++stack->top] = item;
}

// Dépiler un élément de la pile
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "La pile est vide. Impossible de dépiler un élément.\n");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top--];
}

// Afficher les éléments de la pile
void display(Stack *stack) {
    if (isEmpty(stack)) {
        printf("La pile est vide.\n");
        return;
    }
    printf("Contenu de la pile :\n");
    for (int i = 0; i <= stack->top; ++i) {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

// Libérer la mémoire allouée pour la pile
void freeStack(Stack *stack) {
    free(stack->array);
}

int main() {
    Stack myStack;
    int capacity = 5;

    initializeStack(&myStack, capacity);

    push(&myStack, 1);
    push(&myStack, 2);
    push(&myStack, 3);

    display(&myStack);

    printf("Élément dépilé : %d\n", pop(&myStack));

    display(&myStack);

    freeStack(&myStack);

    return 0;
}