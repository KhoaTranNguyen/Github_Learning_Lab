#include <stdio.h>
#include <stdlib.h>

typedef struct Number {
    int data;
    struct Number* next; // Pointer to the next number
} Number;

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

void printListOfNumber(Number* head1, Number* head2){
    Number *curr1 = head1;
    Number *curr2 = head2;
    
    int count1 = 1;
    while (curr2 != NULL){
        while(curr1 != NULL){
            if(count1 == curr2->data){
                break;
            }
            curr1 = curr1->next;
            count1++;
        }
        if (curr1 == NULL){
            printf("[Error: No position %d of L]", curr2->data);
            return;
        }
        printf("%d ", curr1->data);
        curr2 = curr2->next;
    }
}

void main(){
    Number* P = NULL;
    Number* L = NULL;
    int num;
    int sizeL = 0;
    int sizeP = 0;

    while(sizeL < 5){
        printf("Add %d/5 number for L: ", sizeL);
        scanf(" %d", &num);
        addNum(&L, num);
        sizeL++;
    }

    while(sizeP < 3){
        printf("Add %d/3 number for P: ", sizeP);
        scanf(" %d", &num);
        addNum(&P, num);
        sizeP++;
    }

    printListOfNumber(L, P);
}