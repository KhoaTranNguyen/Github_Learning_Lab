#include <stdio.h>
#include <unistd.h>
#include <string.h>

// ANSI escape code to save and restore cursor position
void displayProgress(const char* message, int duration) {
    const char* spinner = "\\-/|";
    int spinnerLen = 4;

    // Print the message
    printf("%s", message);
    fflush(stdout);

    // Animate the spinner right after the message
    for (int i = 0; i < duration; i++) {
        printf("%c", spinner[i % spinnerLen]);
        fflush(stdout);
        sleep(1);

        // Move cursor back one character to replace spinner
        printf("\b");
        fflush(stdout);
    }

    // Clear spinner at end (optional)
    printf(" \n");
}

// Function to display the menu and handle user input
void displayMenu() {
    printf("-----\n");
    printf("Menu:\n");
    printf("1. Create an empty linked list of students\n");
    printf("2. Print the number of nodes in the list\n");
    printf("3. Print all information of all students\n");
    printf("4. Enter information of a student and add he/her at the beginning of the list\n");
    printf("5. Enter information of a student and add he/her at the end of the list\n");
    printf("9. Exit\n");
}                               
