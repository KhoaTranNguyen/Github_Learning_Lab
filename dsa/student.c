#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include <unistd.h> // For sleep function

// Define the structure for a student
typedef struct Student {
    char name[100];
    int student_id;
    float gpa;
    struct Student* next; // Pointer to the next student
} Student;

// Function to create an empty linked list
Student* createEmptyList(Student* head) {
    // If the list is not empty, free all existing nodes
    if (head != NULL) {
        Student* current = head;
        Student* nextNode;

        while (current != NULL) {
            nextNode = current->next; // Store the next node
            free(current);            // Free the current node
            current = nextNode;       // Move to the next node
        }
    }
    return NULL; // Return NULL to indicate the list is now empty
}

// Function to print the number of nodes in the list
int printNumberOfNodes(Student *head){
    Student *current = head;
    Student *nextNode;
    int nodes_number = 0;
    while (current != NULL){
        nodes_number++;
        nextNode = current->next;
        current = nextNode;
    }
    return nodes_number;
}

void printAllStudentInfo(Student *head){
    Student *current = head;
    while (current != NULL){
        sleep(1);
        printf("Name: %s | ID: %d | GPA: %.2f\n", current->name, current->student_id, current->gpa);
        sleep(1);
        current = current->next;
    }
}

void addFirstStudent(Student **head){
    Student *newStudent = (Student*) malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter name: ");
    scanf("%s", newStudent->name);

    printf("Enter ID: ");
    scanf(" %d", &newStudent->student_id);  // Notice the space

    printf("Enter GPA: ");
    scanf(" %f", &newStudent->gpa);         // Notice the space

    Student* lastStudent = NULL;

    Student* current = head;
    while (current != NULL) {
        if (current->next == NULL) {
            lastStudent = current;  // Found the last node
            break;
        }
        current = current->next;
    }
}

void addLastStudent(Student **head){
    Student *newStudent = (Student*) malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter name: ");
    scanf("%s", newStudent->name);

    printf("Enter ID: ");
    scanf(" %d", &newStudent->student_id);  // Notice the space

    printf("Enter GPA: ");
    scanf(" %f", &newStudent->gpa);         // Notice the space

    newStudent->next = *head;
    *head = newStudent;
}

int main() {
    Student* studentList = NULL; // Initialize the linked list as empty
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                studentList = createEmptyList(studentList);
                displayProgress("", 3);
                displayProgress("The linked list has been created and is now empty.", 1);
                break;
            case 2:
                {
                    int numberOfNodes = printNumberOfNodes(studentList);
                    displayProgress("", 2);
                    printf("Current nodes in the list: %d.", numberOfNodes);
                    displayProgress("", 2);
                }
                break;
            case 3:
                {
                    displayProgress("", 2);
                    printAllStudentInfo(studentList);
                    displayProgress("This is the last student of the list..", 2);
                }
                break;
            case 4:
                {
                    addFirstStudent(&studentList);
                    displayProgress("", 2);
                }
                break;
            case 5:
                {
                    addLastStudent(&studentList);
                    displayProgress("", 2);
                }
                break;
            case 9:
                // Free the list before exiting
                studentList = createEmptyList(studentList);
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}