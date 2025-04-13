#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

Stack* createStack(){
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    newStack->data = false;
    newStack->number = 0;
    newStack->expression = '\0';
    newStack->next = NULL;
    return newStack;
}

bool isEmpty(Stack* head, bool report) {
    if (!report) {
        return (head == NULL || !head->data);
    }
    else {
        int value;
        if (pop(&head, true, &value, NULL)) {
            if (isEmpty(head, false)) {
                printf("Nothing left. Eval is %d!\n", value);
                freeStack(&head);
            }
            else {
                Stack* current = head;
                while (current != NULL) {
                    printf("%d ", current->number);
                    Stack* temp = current;
                    current = current->next;
                    free(temp);
                }
                printf("left!\n");
            }
            return false;  // Since stack is not empty, but it is for reporting only, not meant for logic
        }
        
        return true; //Cannot pop, stack is empty
    }
}


bool pop(Stack** stack, bool getNum, int* out_num, char* out_ch) {
    if (isEmpty(*stack, false)) {
        printf("pop: Empty stack\n");
        return false;
    }

    Stack* temp = *stack;

    // If only one node
    if (temp->next == NULL) {
        if (!getNum && out_ch) {
            *out_ch = temp->expression;
            printf("pop: %c\n", *out_ch);
        } else if (getNum && out_num) {
            *out_num = temp->number;
            printf("pop: %d\n", *out_num);
        }

        free(temp);
        *stack = NULL;
        return true;
    }

    // Traverse to second-last node
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    Stack* last = temp->next;

    if (!getNum && out_ch) {
        *out_ch = last->expression;
        printf("pop: %c\n", *out_ch);
    } else if (getNum && out_num) {
        *out_num = last->number;
        printf("pop: %d\n", *out_num);
    }

    free(last);
    temp->next = NULL;
    return true;
}

bool peek(Stack* stack, bool getNum, int* out_num, char* out_ch) {
    if (isEmpty(stack, false)) {
        printf("top: Empty stack\n");
        return false;
    }

    Stack* temp = stack;

    // Traverse to last node
    while (temp->next != NULL) {
        temp = temp->next;
    }

    if (!getNum && out_ch) {
        *out_ch = temp->expression;
        printf("top: %c\n", *out_ch);
    } else if (getNum && out_num) {
        *out_num = temp->number;
        printf("top: %d\n", *out_num);
    }

    return true;
}

bool push(Stack** stack, int num, char ch){
    
    if((*stack) == NULL) {
        (*stack) = createStack();
        (*stack)->data = true;
        (*stack)->number = num;
        (*stack)->expression = ch;
    }
    else if (!(*stack)->data) {
        (*stack)->data = true;
        (*stack)->number = num;
        (*stack)->expression = ch;
    }
    else {
        Stack* temp = *stack;
        while (temp->next != NULL){
            temp = temp->next;
        }
        Stack* newStack = createStack();
        temp->next = newStack;
        newStack->data = true;
        newStack->number = num;
        newStack->expression = ch;
    }

    if (ch != '\0'){
        printf("push: %c\n", ch);
    }
    else{
        printf("push: %d\n", num);
    }

    return true;
}

void freeStack(Stack** stack){
    Stack* current = *stack;
    while (current != NULL){
        Stack* temp = current;
        current = current->next;
        free(temp);
    }
}