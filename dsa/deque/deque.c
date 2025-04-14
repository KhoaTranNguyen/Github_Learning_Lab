#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Deque { 
    int number;
    struct Deque* next;
} Deque;

Deque* createNode(int num) {
    Deque* newNode = (Deque*)malloc(sizeof(Deque));
    newNode->number = num;
    newNode->next = NULL;
    return newNode;
}

bool isEmpty(Deque* head) {
    return (head == NULL);
}

bool push(Deque** head, int num) {
    Deque* newNode = createNode(num);
    newNode->next = *head;
    *head = newNode;

    printf("push: %d\n", num);
    return true;
}

bool pop(Deque** head) {
    if (isEmpty(*head)) {
        printf("pop: head NULL\n");
        return false;
    }

    Deque* temp = *head;
    *head = (*head)->next;
    printf("pop: %d\n", temp->number);
    free(temp);
    return true;
}

bool inject(Deque** head, int num) {
    Deque* newNode = createNode(num);

    if (isEmpty(*head)) {
        *head = newNode;
    } else {
        Deque* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    printf("inject: %d\n", num);
    return true;
}

bool eject(Deque** head) {
    if (isEmpty(*head)) {
        printf("eject: head NULL\n");
        return false;
    }

    // Only one node
    if ((*head)->next == NULL) {
        printf("eject: %d\n", (*head)->number);
        free(*head);
        *head = NULL;
        printf("(empty list)\n");
    } else {
        Deque* current = *head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        Deque* temp = current->next;
        printf("eject: %d\n", temp->number);
        free(temp);
        current->next = NULL;
    }

    return true;
}

bool print(Deque* head) {
    if (isEmpty(head)) {
        printf("print: Deque NULL\n");
        return false;
    }

    Deque* current = head;
    printf("print: ");
    while (current != NULL) {
        printf("%d ", current->number);
        current = current->next;
    }
    printf("\n");
    return true;
}

int main() {
    // Initialize the deque as empty
    Deque* newDeque = NULL;

    push(&newDeque, 10);
    push(&newDeque, 20);
    push(&newDeque, 30);
    print(newDeque);

    inject(&newDeque, 40);
    inject(&newDeque, 50);
    print(newDeque);

    pop(&newDeque);
    pop(&newDeque);
    print(newDeque);

    eject(&newDeque);
    eject(&newDeque);
    print(newDeque);

    return 0;
}