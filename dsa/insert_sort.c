#include <stdio.h>

void insert_sort(int *arr, int size) {
    for (int i = 1; i < size; i++){
        int key = arr[i];
        int j = i - 1;
        // Shift elements that are greater than key to one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main(){
    int Arr[] = {1, 16, 12, 26, 25, 35, 33, 58, 45, 42, 56, 67, 83, 75, 74, 86, 81, 88, 99, 95};
    int size = sizeof(Arr) / sizeof(int);
    
    insert_sort(Arr, size);

    for (int i = 0; i < size; i++){
        printf("%d ", Arr[i]);
    } printf("\n");
}