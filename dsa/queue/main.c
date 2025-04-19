// main.c

#include <stdio.h>
#include "queue.h"

int main() {
    Queue* newQueue = NULL;

    enqueue(&newQueue, 1);
    enqueue(&newQueue, 2);
    enqueue(&newQueue, 3);

    print(newQueue);

    dequeue(&newQueue);
    dequeue(&newQueue);

    print(newQueue);

    return 0;
}
