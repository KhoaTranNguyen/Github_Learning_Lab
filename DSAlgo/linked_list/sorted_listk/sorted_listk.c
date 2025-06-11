#include <stdio.h>
#include <stdlib.h>

typedef struct Number {
    int data;
    struct Number* next; // Pointer to the next number
} Number;

void printListOfNumber(Number* head){
    Number *current = head;
    while (current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
}

void addNum(Number** head, int num) {
    Number* newNum = (Number*)malloc(sizeof(Number));
    newNum->data = num;
    newNum->next = NULL; // Initialize the next pointer

    if (*head == NULL || (*head)->data >= num){
        newNum->next = *head;
        *head = newNum;
        return;
    }

    Number* current = *head;
    Number *prev = NULL;

    while(current != NULL && current->data < num){
        prev = current;
        current = current->next;
    }

    prev->next = newNum;
    newNum->next = current;
}

void main(){
    Number* numberList = NULL;
    int num;
    int count = 0;

    while(count < 5){
        printf("Add %d/5 number: ", count);
        scanf(" %d", &num);
        addNum(&numberList, num);
        count++;
    }

    printListOfNumber(numberList);
}