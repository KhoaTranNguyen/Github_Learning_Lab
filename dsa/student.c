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

    printf("Enter name: ");
    scanf("%s", newStudent->name);

    printf("Enter ID: ");
    scanf(" %d", &newStudent->student_id);  // Notice the space

    printf("Enter GPA: ");
    scanf(" %f", &newStudent->gpa);         // Notice the space

    newStudent->next = *head;
    *head = newStudent;
}

Student* findLastStudent(Student **head){
    Student* lastStudent = NULL;

    Student* current = *head;
    while(current != NULL){
        if (current->next == NULL){
            lastStudent = current;
            break;
        }
        current = current->next;
    }

    return lastStudent;
}

void addLastStudent(Student **head){

    Student* newStudent = (Student*) malloc(sizeof(Student));

    printf("Enter name: ");
    scanf("%s", newStudent->name);

    printf("Enter ID: ");
    scanf(" %d", &newStudent->student_id);  // Notice the space

    printf("Enter GPA: ");
    scanf(" %f", &newStudent->gpa);         // Notice the space

    Student* lastStudent = findLastStudent(head);

    lastStudent->next = newStudent;
}

void deleteStudentInfo (Student **head, int cs) {
    if (*head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    int selectedID, deletedStudent = 0;
    char selectedName[100];
    if (cs == 6){
        printf("Enter the student ID to delete: ");
        scanf(" %d", &selectedID);
    }
    else if (cs == 7){
        printf("Enter the student name to delete: ");
        scanf(" %s", selectedName);
    }

    Student *current = *head;
    Student *previous = NULL;

    while (current != NULL) {

        if ((cs == 6 && current->student_id == selectedID) ||
            (cs == 7 && strcmp(current->name, selectedName) == 0)) {
            
            if (previous == NULL) // Deleting the head node
                *head = current->next;
            else // Deleting a node after head
                previous->next = current->next;

            free(current);

            if (cs == 6){
                printf("Student with ID %d has been deleted.\n", selectedID);
                return;
            }
            else if (cs == 7){
                deletedStudent++;
            }
        }

        previous = current;
        current = current->next;

    }
    if (cs == 6)
        printf("Student with ID %d not found.\n", selectedID);
    else
        printf("%d students with the Name: %s has been deleted.\n", deletedStudent, selectedName);
}

void swap(Student *xp, Student *yp) {
    // Temporary variables to hold the data
    char tempName[100];
    int tempID;
    float tempGPA;

    // Swap name
    strcpy(tempName, xp->name);
    strcpy(xp->name, yp->name);
    strcpy(yp->name, tempName);

    // Swap student ID
    tempID = xp->student_id;
    xp->student_id = yp->student_id;
    yp->student_id = tempID;

    // Swap GPA
    tempGPA = xp->gpa;
    xp->gpa = yp->gpa;
    yp->gpa = tempGPA;
}

void sortListbyGPA(Student **head){
    if (*head == NULL || (*head)->next == NULL) {
        // List is empty or has only one node, no need to sort
        return;
    }

    Student *current = *head;
    
    while(current != NULL){
        Student *temp = current;
        Student *i = current->next;
        while (i != NULL){
            if (i->gpa < temp->gpa)
                temp = i;
            i = i->next;
        }
        if(current != temp)
            swap(current, temp);

        current = current->next;
    }
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
                    displayProgress("This is the end of the list..", 2);
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
            case 6:
                {
                    deleteStudentInfo(&studentList, 6);
                    displayProgress("", 2);
                }
                break;
            case 7:
                {
                    deleteStudentInfo(&studentList, 7);
                    displayProgress("", 2);
                }
                break;
            case 8:
                {
                    sortListbyGPA(&studentList);
                    printAllStudentInfo(studentList);
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