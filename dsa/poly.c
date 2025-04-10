#include <stdio.h>
#include <stdlib.h>

typedef struct Poly {
    int exp;
    int coef;
    struct Poly* next;
} Poly;

void addPoly(Poly **head, Poly **newEle) {
    Poly* current = *head;
    Poly* prev = NULL;

    // Traverse the list to find the correct position
    while (current != NULL && current->exp > (*newEle)->exp) {
        prev = current;
        current = current->next;
    }

    if (current != NULL && current->exp == (*newEle)->exp) {
        // Combine coefficients if exponents are the same
        current->coef += (*newEle)->coef;
        if (current->coef == 0){
            if (prev == NULL){
                *head = current->next;
            }
            else{
                prev->next = current->next;
            }
            free(current);
        }
        free(*newEle); // Free the redundant node
    } else {
        // Insert the new node
        if (prev == NULL) {
            // Insert at the head
            (*newEle)->next = *head;
            *head = *newEle;
        } else {
            // Insert in the middle or at the end
            prev->next = *newEle;
            (*newEle)->next = current;
        }
    }
}

void printPoly(Poly* head){
    Poly* current = head;
    if (current == NULL){
        printf("(empty list)\n");
        return;
    }
    while (current != NULL){
        if (current != head){
            if(current->coef >= 0){
                printf("+ ");
            }
            else if (current->coef < 0){
                printf("- ");
            }
        }
        if (current->coef != 1 && current->coef != -1){
            if (current->coef < 0)
                printf("%d", abs(current->coef));
            else printf("%d", current->coef);
        }
        else if (current == head && current->coef == -1){
            printf("-");
        }
        printf("x^%d ", current->exp);
        current = current->next;
    }
}

Poly* createPoly(int order){
    printf("%dth Polynomial\n", order);

    int size;
    printf("Enter the poly size: ");
    scanf(" %d", &size);

    Poly* newSeq = NULL;
    printf("Format: coef exp\n");
    for (int i = 0; i < size; i++){
        int exp = 0, coef = 0;
        printf("Enter %d/%d Polys: ", i + 1, size);
        scanf(" %d", &coef);
        if ((coef >= 0 && coef != 1) || coef == -1)
            printf("\033[A\033[%dCx^", 18);  // Move cursor up one line and 17 characters right (to where user typed) to print with x^
        else if (coef < 0)
            printf("\033[A\033[%dCx^", 19);
        else if (coef == 1)
            printf("\033[A\033[%dC x^", 16);
        scanf("%d", &exp);

        Poly* newElement = (Poly*)malloc(sizeof(Poly));
        newElement->exp = exp;
        newElement->coef = coef;
        newElement->next = NULL;
        addPoly(&newSeq, &newElement);
    }

    return newSeq;
}

void main(){
    Poly* firstPoly = createPoly(1);
    printPoly(firstPoly);
}