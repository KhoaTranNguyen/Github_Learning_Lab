// stack.h
#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct Stack{  
    bool data;  
    int number;   
    char expression;
    struct Stack* next;
} Stack;

Stack* createStack();
bool isEmpty(Stack* head, bool report);
bool pop(Stack** stack, bool getNum, int* out_num, char* out_ch);
bool peek(Stack* stack, bool getNum, int* out_num, char* out_ch);
bool push(Stack** stack, int num, char ch);
void freeStack(Stack** stack);

#endif