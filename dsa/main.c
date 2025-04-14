#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"

bool matchingBrackets(char input[]) {
    Stack* newStack = createStack();

    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];

        if (ch == '(' || ch == '[' || ch == '{') {
            push(&newStack, 0, ch);
        }
        
        else if (ch == ')' || ch == ']' || ch == '}') {
            printf("reach: %c\n", ch);

            if (isEmpty(newStack))
                return 0;
            
            char top;
            pop(&newStack, false, NULL, &top);

            if (!((ch == ')' && top == '(') ||
                  (ch == ']' && top == '[') ||
                  (ch == '}' && top == '{'))) {
                return 0;
            }
        }
    }

    bool result = isEmpty(newStack);
    
    freeStack(&newStack);

    return result ? 1 : 0;
}

bool postfixCheck(const char input[]) {
    printf("postfix: %s\n", input);

    // Must start with a digit
    if (!(input[0] >= '0' && input[0] <= '9')) return 0;

    int operandCount = 0;
    int operatorCount = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];

        if (ch >= '0' && ch <= '9') {
            operandCount++;
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // Must have at least 2 operands to apply an operator
            if (operandCount < 2) return 0;

            operandCount--;  // two operands reduced to one after operation
            operatorCount++;
        }
        else {
            // Invalid character
            return 0;
        }
    }

    // At the end, there must be exactly one operand (the result)
    return operandCount == 1;
}

Stack* postfixEval(char input[]) {
    Stack* newStack = createStack();

    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];

        if (ch == '+' || ch == '*' || ch == '-' || ch == '/') {
            int arg1;
            int arg2;
            int result = 0;

            printf("reach: %c\n", ch);
            pop(&newStack, true, &arg1, NULL);
            pop(&newStack, true, &arg2, NULL);

            switch (ch) {
                case '+':
                    result = arg2 + arg1;
                    break;
                case '-':
                    result = arg2 - arg1;
                    break;
                case '*':
                    result = arg2 * arg1;
                    break;
                case '/':
                    result = arg2 / arg1;
                    break;
            }

            push(&newStack, result, '\0');
        } else if ('0' <= ch && ch <= '9') {
            push(&newStack, ch - '0', '\0'); // push char digit
        }
    }

    int final;
    if (pop(&newStack, true, &final, NULL)) {
        if (isEmpty(newStack)) {
            printf("Eval is %d!\n", final);
            freeStack(&newStack);
        }
        else {
            Stack* current = newStack;
            while (current != NULL) {
                printf("%d ", current->number);
                Stack* temp = current;
                current = current->next;
                free(temp);
            }
            printf("left!\n");
        }
    }

    return NULL;
}
 int main() {
    // char input[50] = "[a+b{1*2]9*1}+(2-1)";

    // if (matchingBrackets(input)) {
    //     printf("Brackets match!\n");
    // } else {
    //     printf("Brackets do NOT match!\n");
    // }

    char postfix[50] = "321*+98--";

    // postfixEval(postfix);
    
    int check = postfixCheck(postfix);
    printf("%d\n", check);

    return 0;
}
