#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"

bool matchingBrackets(char input[]) {
    printf("------\nChecking brackets: %s..\n\n", input);

    Stack* newStack = createStack();

    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];

        if (ch == '(' || ch == '[' || ch == '{') {
            push(&newStack, 0, ch);
        }
        
        else if (ch == ')' || ch == ']' || ch == '}') {
            printf("reach: %c\n", ch);

            if (isEmpty(newStack)){
                printf("\nBrackets do NOT match!\n");
                return false;
            }
            
            char top;
            pop(&newStack, false, NULL, &top);

            if (!((ch == ')' && top == '(') ||
                  (ch == ']' && top == '[') ||
                  (ch == '}' && top == '{'))) {
                printf("\nBrackets do NOT match!\n");
                return false;
            }
        }
    }

    bool result = isEmpty(newStack);
    
    freeStack(&newStack);

    if (result) {
        printf("\nBrackets match!\n");
        return true;
    } else {
        printf("\nBrackets do NOT match!\n");
        return false;
    }
}

bool postfixCheck(const char input[]) {
    printf("------\nChecking postfix: %s...\n", input);

    // Must start with a digit
    if (!(input[0] >= '0' && input[0] <= '9')) return false;

    int operandCount = 0;
    int operatorCount = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];

        if (ch >= '0' && ch <= '9') {
            operandCount++;
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // Must have at least 2 operands to apply an operator
            if (operandCount < 2) {
                printf("Invalid!\n");
                return false;
            }

            operandCount--;  // two operands reduced to one after operation
            operatorCount++;
        }
        else {
            // Invalid character
            printf("Invalid!\n");
            return false;
        }
    }

    // At the end, there must be exactly one operand (the result)
    if (operandCount == 1) {
        printf("Valid!\n");
        return true;
    }
    else {
        printf("Invalid!\n");
        return false;
    }
}

Stack* postfixEval(char input[]) {
    printf("------\nEvaluating postfix: %s..\n\n", input);

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
            printf("\nSuccess!\nEval is %d!\n", final);
            freeStack(&newStack);
        }
        else {
            Stack* current = newStack;
            printf("\n");
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

int priority(char c) {
    
    if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

bool InfixToPostfix(char input[], char* postfix) {
    
    matchingBrackets(input);

    Stack* tempStack = createStack();

    printf("------\nConverting infix...\n\n");
    for (int i = 0; input[i] != '\0'; i++) {
        if ('0' <= input[i] && input[i] <= '9'){
            strncat(postfix, &input[i], 1);
        }
        else {
            if (input[i] == '(') {
                push(&tempStack, 0, input[i]);
            }
            else if (input[i] == ')') {
                char temp = '\0';
                while (temp != '(' && !isEmpty(tempStack)) {
                    pop(&tempStack, false, NULL, &temp);
                    if (temp != '(') {
                        strncat(postfix, &temp, 1);
                    }
                }
            }
            else {
                char top;
                peek(tempStack, false, NULL, &top);
                if (priority(input[i]) > priority(top) ||
                    isEmpty(tempStack) || contain(tempStack, false, 0, '(')) {
                        push(&tempStack, 0, input[i]);
                    }
                else {
                    while (priority(input[i]) <= priority(top)) {
                        pop(&tempStack, false, NULL, &top);
                        strncat(postfix, &top, 1);
                    }
                    push(&tempStack, 0, input[i]);
                }
            }
        }
    }

    while (!isEmpty(tempStack)) {
        char top;
        pop(&tempStack, false, NULL, &top);
        strncat(postfix, &top, 1);
    }

    printf("\nConverted: %s\n", postfix);

    bool check = postfixCheck(postfix);
    if (check != true) {
        printf("------\nConvert failed!\n");
        return false;
    }

    printf("------\nConverted success!\n\ninfix: %s\npostfix: %s\n", input, postfix);
    return true;
}

int main() {
    char input[50] = "[a+b{1*2]9*1}+(2-1)";

    matchingBrackets(input);

    char postFix[50] = "122+3*+456+/-";

    postfixEval(postFix);
    postfixCheck(postFix);
    
    char infix[50] = "(1+(1+2)*3)-(4/(5+6))"; //112+3*+456+/-
    char postfix[50];
    postfix[0] = '\0'; // ✅ important!
    if (InfixToPostfix(infix, postfix))
        postfixEval(postfix);

    return 0;
}
