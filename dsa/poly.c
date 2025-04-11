#include <stdio.h>
#include <stdlib.h>

typedef struct Poly {
    int coef;
    int exp;
    struct Poly* next;
} Poly;

void addElePoly(Poly **head, Poly **newEle) {
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
            else if (prev != NULL){
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

Poly* createPoly(int order){
    printf("%dth Polynomial\n", order);

    int size;
    printf("Enter the poly size: ");
    scanf(" %d", &size);

    Poly* newPoly = NULL;
    printf("Format: coef exp\n");
    for (int i = 0; i < size; i++){
        printf("Enter %d/%d Elemn: ", i + 1, size);

        int coef = 0, exp = 0;
        scanf(" %d", &coef);
        if ((coef > 0 && coef != 1) || coef == -1){
            printf("\033[A\033[%dCx^", 18);  // Move cursor up one line and 17 characters right (to where user typed) to print with x^
            scanf("%d", &exp);
            if (exp == 1){
                printf("\033[A\033[%dC  \n", 19);
            }
            else if (exp == 0){
                if (coef != -1)
                    printf("\033[A\033[%dC   \n", 18);
                else printf("\033[A\033[%dC1  \n", 18);
            }
        }
        else if (coef < 0 && coef != -1){
            printf("\033[A\033[%dCx^", 19);
            scanf("%d", &exp);
            if (exp == 1){
                printf("\033[A\033[%dC  \n", 20);
            }
            else if (exp == 0)
                printf("\033[A\033[%dC   \n", 19);
        }
        else if (coef == 1){
            printf("\033[A\033[%dC x^", 16);
            scanf("%d", &exp);
            if (exp == 1){
                printf("\033[A\033[%dC  \n", 18);
            }
            else if (exp == 0)
                printf("\033[A\033[%dC1  \n", 17);
        }

        if (coef != 0){
            Poly* newElement = (Poly*)malloc(sizeof(Poly));
            newElement->coef = coef;
            newElement->exp = exp;
            newElement->next = NULL;
            addElePoly(&newPoly, &newElement);
        }
    }

    return newPoly;
}

Poly* addPolyPoly(Poly* head1, Poly* head2){
    if (head1 == NULL)
        return head2;
    else if (head2 == NULL)
        return head1;

    Poly* newPoly = NULL;
    Poly* current1 = head1;
    Poly* current2 = head2;

    while (current1 != NULL && current2 != NULL){
        
        if (current1->exp > current2->exp){
            Poly* newElement = (Poly*)malloc(sizeof(Poly));
            newElement = current1;
            current1 = current1->next;
            addElePoly(&newPoly, &newElement);
        }
        else if (current1->exp < current2->exp){
            Poly* newElement = (Poly*)malloc(sizeof(Poly));
            newElement = current2;
            current2 = current2->next;
            addElePoly(&newPoly, &newElement);
        }
        else if (current1->exp == current2->exp){
            if (current1->coef + current2->coef != 0){
                Poly* newElement = (Poly*)malloc(sizeof(Poly));
                newElement->coef = current1->coef + current2->coef;
                newElement->exp = current1->exp;
                addElePoly(&newPoly, &newElement);
            }
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    while(current1 != NULL){
        Poly* newElement = (Poly*)malloc(sizeof(Poly));
        newElement = current1;
        current1 = current1->next;
        addElePoly(&newPoly, &newElement);
    }
    while(current2 != NULL){
        Poly* newElement = (Poly*)malloc(sizeof(Poly));
        newElement = current2;
        current2 = current2->next;
        addElePoly(&newPoly, &newElement);
    }
    return newPoly;
}

Poly* mulPolyPoly(Poly* head1, Poly* head2){
    if (head1 == NULL)
        return head2;
    else if (head2 == NULL)
        return head1;

    Poly* newPoly = NULL;
    Poly* current1 = head1;

    while (current1 != NULL){
        Poly* current2 = head2;
        while (current2!= NULL){
            Poly* newElement = (Poly*)malloc(sizeof(Poly));
            newElement->exp = current1->exp + current2->exp;
            newElement->coef = (current1->coef)*(current2->coef);
            newElement->next = NULL;
            addElePoly(&newPoly, &newElement);
            current2 = current2->next;
        }
        current1 = current1->next;
    }

    return newPoly;
}

void printPoly(Poly* head){
    Poly* current = head;
    if (current == NULL){
        printf("(empty list)\n");
        printf("----\n");
        return;
    }
    printf("Result: ");
    while (current != NULL){
        if (current != head){
            if(current->coef > 0){
                printf("+ ");
            }
            else if (current->coef < 0){
                printf("- ");
            }
        }
        
        if ((current->coef != 1 && current->coef != -1) ||
            (current->exp == 0 && current->coef != 0)){
            if (current->coef < 0 && current != head)
                printf("%d", abs(current->coef));
            else printf("%d", current->coef);
        }
        else if (current == head && current->coef == -1){
            printf("-");
        }

        if (current->exp != 1 && current->exp != 0)
            printf("x^%d", current->exp);
        else if (current->exp == 1)
            printf("x");
        printf(" ");
        current = current->next;
    }
    printf("\b\n----\n");
}

void main(){
    Poly* firstPoly = createPoly(1);
    printPoly(firstPoly);
    Poly* secondPoly = createPoly(2);
    printPoly(secondPoly);

    Poly* thirdPoly = addPolyPoly(firstPoly, secondPoly);
    printf("Adding 2 Polynomials\n");
    printPoly(thirdPoly);

    Poly* fourthPoly = mulPolyPoly(firstPoly, secondPoly);
    printf("Multiplying 2 Polynomials\n");
    printPoly(fourthPoly);
}