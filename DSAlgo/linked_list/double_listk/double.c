#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double.h"

void insertNode(Node** head, Node** newNode, int* index, bool sort) {
    // Allocate new node if not already provided
    if (*newNode == NULL) {
        *newNode = (Node*)malloc(sizeof(Node));
        int temp;
        printf("Enter element: ");
        scanf("%d", &temp);
        (*newNode)->data = temp;
        (*newNode)->prev = NULL;
        (*newNode)->next = NULL;
    }
    
    // Get index from user if it's NULL
    int realIndex = 0;
    if (index == NULL && sort == false){
        printf("Enter index: ");
        scanf("%d", &realIndex);
    }
    else if (index != NULL && sort == false){
        realIndex = *index;
    }

    Node* current = *head;
    Node* prev = NULL;
    int countIndex = 0;

    if (sort == false){
        while (current != NULL && countIndex != realIndex) {
            prev = current;
            current = current->next;
            countIndex++;
        }
    }
    else if (sort == true){
        while (current != NULL && current->data < (*newNode)->data) {
            prev = current;
            current = current->next;
        } 
    }

    // Insert at head
    if (prev == NULL) {
        (*newNode)->next = *head;
        if (*head != NULL) {
            (*head)->prev = *newNode;
        }
        *head = *newNode;
    }
    // Insert at given position
    else {
        prev->next = *newNode;
        (*newNode)->prev = prev;
        (*newNode)->next = current;
        if (current != NULL) {
            current->prev = *newNode;
        }
    }
}

Node* createList(){
    int size;
    printf("Enter linked list size: ");
    scanf(" %d", &size);

    Node* newList = NULL;
    for (int i = 0; i < size; i++){
        int temp;
        printf("Enter %d/%d element: ", i + 1, size);
        scanf(" %d", &temp);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = temp;
        newNode->prev = NULL;
        newNode->next = NULL;
        int index = -1;
        insertNode(&newList, &newNode, &index, false);
    }

    return newList;
}

void printList(Node* head){
    if (head == NULL){
        printf("(empty list)\n");
        return;
    }

    Node* current = head;
    while (current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void deleteNode(Node** head, int* index){
    // Get index from user if it's NULL
    int realIndex = 0;
    if (index == NULL) {
        printf("Enter index: ");
        scanf("%d", &realIndex);
    } else {
        realIndex = *index;
    }

    Node* current = *head;
    Node* prev = NULL;
    int countIndex = 0;
    while (current != NULL && countIndex != realIndex) {
        prev = current;
        current = current->next;
        countIndex++;
    }

    // Delete at head
    if (prev == NULL) {
        if (*head == NULL)
            return;
        if (current->next != NULL){
            current->next->prev = NULL;
            *head = current->next;
        }
        free(current);
        return;
    }
    // Delete at given position
    else if (current != NULL){
        prev->next = current->next;
        current->next->prev = prev;
        free(current);
    }
    return;
}

void findNode(Node** head, int* index){
    // Get index from user if it's NULL
    int realIndex = 0;
    if (index == NULL) {
        printf("Enter index: ");
        scanf("%d", &realIndex);
    } else {
        realIndex = *index;
    }

    Node* current = *head;
    int countIndex = 0;
    while (current != NULL && countIndex != realIndex) {
        current = current->next;
        countIndex++;
    }

    // Delete at head
    if (current == NULL){
        printf("Not found\n");
    }
    else{
        printf("Result at index %d: %d\n", realIndex, current->data);
    }
}

Node* sortList(Node** head){
    Node* current = *head;
    Node* newList = NULL;

    while (current != NULL){
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = current->data;
        newNode->prev = NULL;
        newNode->next = NULL;
        insertNode(&newList, &newNode, NULL, true);
        current = current->next;
    }

    return newList;
}

void freeList(Node* head){
    while (head != NULL){
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}