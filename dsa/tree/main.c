#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "..\queue\queue.h"

typedef struct BinaryTree {
    int data;
    struct BinaryTree* Left;
    struct BinaryTree* Right;
} BinaryTree;

BinaryTree* createTree(int data) {
    BinaryTree* newBranch = (BinaryTree*)malloc(sizeof(BinaryTree));
    newBranch->data = data;
    newBranch->Left = newBranch->Right = NULL;
    return newBranch;
}

int main() {
    char sequence[100];
    printf("Input an array of number (space separated): ");
    scanf("%s ", sequence);
    return 0;
}