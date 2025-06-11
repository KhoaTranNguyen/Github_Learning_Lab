// queue.c

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* createQueue(int number) {
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->number = number;
    newQueue->next = NULL;
    return newQueue;
}

bool isEmpty(Queue* head) {
    return (head == NULL);
}

bool enqueue(Queue** queue, int num) {
    if (*queue == NULL) {
        *queue = createQueue(num);
    } else {
        Queue* temp = *queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = createQueue(num);
    }

    printf("insert: %d\n", num);
    return true;
}

bool dequeue(Queue** head) {
    if (*head == NULL) {
        printf("delete: head NULL\n");
        return false;
    }

    Queue* temp = *head;
    *head = (*head)->next;
    printf("delete: %d\n", temp->number);
    free(temp);
    return true;
}

bool print(Queue* head) {
    if (isEmpty(head)) {
        printf("print: Queue NULL\n");
        return false;
    }

    Queue* current = head;
    printf("queue: ");
    while (current != NULL) {
        printf("%d ", current->number);
        current = current->next;
    }
    printf("\n");
    return true;
}
