#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double.h"

bool request(const char* message){
    char ans;
    printf("%s (yes/no): ", message);
    scanf(" %c", &ans);
    if (ans == 'y') return true;
    else if (ans == 'n') return false;
}

void main(){
    Node* newList = createList();
    printList(newList);

    bool insert = request("Insert new node");
    if (insert == true){
        Node* newNode = NULL;
        insertNode(&newList, &newNode, NULL, false);
        printList(newList);
    }
    
    bool delete = request("Delete a node");
    if (delete == true){
        deleteNode(&newList, NULL);
        printList(newList);
    }

    bool find = request("Find a node");
    if (find == true){
        findNode(&newList, NULL);
    }

    bool sort = request("Sort the list");
    if (sort == true){
        Node* sortedList = sortList(&newList);
        freeList(newList);  // Free the old list
        newList = sortedList;
        printList(sortedList);
    }
}