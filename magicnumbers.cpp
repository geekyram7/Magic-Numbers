#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
    struct node *prev;
} node;

node* create_node(int value) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void initMagicSquare(int squareSize, node **square) {
    int num = 1;
    for (int i = 0; i < squareSize; i++) {
        for (int j = 0; j < squareSize; j++) {
            square[i * squareSize + j] = create_node(num++);
        }
    }
}

void displaySquare(int squareSize, node **square) {
    printf("\n");
    for (int i = 0; i < squareSize; i++) {
        for (int j = 0; j < squareSize; j++) {
            printf("%d\t", square[i * squareSize + j]->value);
        }
        printf("\n");
    }
    printf("\n");
}

int isMagicSquare(int squareSize, node **square) {
    int targetSum = squareSize * (squareSize * squareSize + 1) / 2;
    int rowSum, colSum, diag1Sum = 0, diag2Sum = 0;

    for (int i = 0; i < squareSize; i++) {
        rowSum = 0;
        colSum = 0;
        for (int j = 0; j < squareSize; j++) {
            rowSum += square[i * squareSize + j]->value;
            colSum += square[j * squareSize + i]->value;
        }
        if (rowSum != targetSum || colSum != targetSum) {
            return 0;
        }
        diag1Sum += square[i * squareSize + i]->value;
        diag2Sum += square[i * squareSize + (squareSize - i - 1)]->value;
    }

    if (diag1Sum != targetSum || diag2Sum != targetSum) {
        return 0;
    }
    return 1;
}

void swapNodes(node **square, int num1, int num2, int squareSize) {
    node *node1 = NULL, *node2 = NULL;
    for (int i = 0; i < squareSize * squareSize; i++) {
        if (square[i]->value == num1) {
            node1 = square[i];
        }
        if (square[i]->value == num2) {
            node2 = square[i];
        }
    }
    if (node1 && node2) {
        int temp = node1->value;
        node1->value = node2->value;
        node2->value = temp;
    }
}

int main() {
    int size;
    printf("Welcome to the Magic Square Game!\n");
    printf("Choose the size of the magic square to solve (3, 4, 5, ...): ");
    scanf("%d", &size);

    if (size < 3) {
        printf("Invalid size. Exiting...\n");
        return 1;
    }

    node **magicSquare = (node **)malloc(sizeof(node *) * size * size);
    initMagicSquare(size, magicSquare);

    printf("\nRearrange the numbers to form a magic square.\n");
    while (!isMagicSquare(size, magicSquare)) {
        displaySquare(size, magicSquare);
        int num1, num2;
        printf("Enter two numbers to swap (separated by space): ");
        scanf("%d %d", &num1, &num2);
        swapNodes(magicSquare, num1, num2, size);
    }

    displaySquare(size, magicSquare);
    printf("\nCongratulations! You solved the magic square!\n");

    for (int i = 0; i < size * size; i++) {
        free(magicSquare[i]);
    }
    free(magicSquare);

    return 0;
}
