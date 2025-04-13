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

            if (isEmpty(newStack, false))
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

    bool result = isEmpty(newStack, false);

    freeStack(&newStack);

    return result ? 1 : 0;
}

Stack* postfixEval(char input[]) {
    printf("postfix: %s\n", input);
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

    return newStack;
}

int main() {
    char input[50] = "[a+b{1*2]9*1}+(2-1)";

    if (matchingBrackets(input)) {
        printf("Brackets match!\n");
    } else {
        printf("Brackets do NOT match!\n");
    }

    char postfix[50] = "43731*+9-";

    Stack* eval = postfixEval(postfix);
    isEmpty(eval, true);

    return 0;
}
