// queue.h

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct Queue {
    int number;
    struct Queue* next;
} Queue;

Queue* createQueue(int number);
bool isEmpty(Queue* head);
bool enqueue(Queue** queue, int num);
bool dequeue(Queue** head);
bool print(Queue* head);

#endif // QUEUE_H
