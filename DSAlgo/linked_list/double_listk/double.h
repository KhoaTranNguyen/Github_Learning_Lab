// double.h
#ifndef DOUBLE_H
#define DOUBLE_H

#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

void insertNode(Node** head, Node** newNode, int* index, bool sort);
Node* createList();
void printList(Node* head);
void deleteNode(Node** head, int* index);
void findNode(Node** head, int* index);
bool request(const char* message);
Node* sortList(Node** head);
void freeList(Node* head);

#endif