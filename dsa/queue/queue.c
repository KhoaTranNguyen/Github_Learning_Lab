#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue{ 
    bool data;
    int number;
    struct Queue* next;
} Queue;

Queue* createQueue(){
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->data = false;
    newQueue->number = 0;
    newQueue->next = NULL;
    return newQueue;
}

bool isEmpty(Queue* head) {
    return (head == NULL || !head->data);
}

bool insert(Queue** queue, int num){
    
    if((*queue) == NULL) {
        (*queue) = createQueue();
        (*queue)->data = true;
        (*queue)->number = num;
    }
    else if (!(*queue)->data) {
        (*queue)->data = true;
        (*queue)->number = num;
    }
    else {
        Queue* temp = *queue;
        while (temp->next != NULL){
            temp = temp->next;
        }
        Queue* newQueue = createQueue();
        newQueue->data = true;
        newQueue->number = num;
        temp->next = newQueue;
    }

    printf("insert: %d\n", num);

    return true;
}

bool delete(Queue** head) {
    // Check if the queue is empty
    if (*head == NULL) {
        printf("delete: head NULL\n");
        return false; // Return false to indicate the queue is empty
    }

    // Delete the head node
    Queue* temp = *head;
    *head = (*head)->next; // Move the head pointer to the next node
    printf("delete: %d\n", temp->number);
    free(temp);

    return true; // Return true to indicate successful deletion
}

bool print(Queue* head) {
    if (isEmpty(head)) {
        printf("print: Queue NULL\n");
        return false;
    }

    Queue *current = head;
    printf("queue: ");
    while (current != NULL && current->data == true) {
        printf("%d ", current->number);
        current = current->next;
    }
    printf("\n");
    return true;
}

int main() {
    Queue* newQueue = createQueue();
    insert(&newQueue, 1);
    insert(&newQueue, 2);
    insert(&newQueue, 3);
    print(newQueue);
    delete(&newQueue);
    return 0;
}