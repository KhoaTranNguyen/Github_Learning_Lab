#include <stdio.h>
#include <stdlib.h>

void mergeParts(int *arr, int left, int mid, int right) {
    int i = left, j = mid + 1;
    int k = 0;
    int size = right - left + 1; // Size of the temporary array
    int *temp = (int *)calloc(size, sizeof(int)); // Dynamically allocate memory for temp

    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    // Copy the sorted elements back into the original array
    for (int i = 0; i < size; i++) {
        if (arr[left + i] != temp[i])
            arr[left + i] = temp[i];
    }

    free(temp); // Free the allocated memory
}

void mergeSort(int *arr, int left, int right) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    mergeParts(arr, left, mid, right);
}

int main(){
    int Arr[] = {1, 16, 12, 26, 25, 35, 33, 58, 45, 42, 56, 67, 83, 75, 74, 86, 81, 88, 99, 95};
    int size = sizeof(Arr) / sizeof(int);
    
    mergeSort(Arr, 0, size-1);

    for (int i = 0; i < size; i++){
        printf("%d ", Arr[i]);
    } printf("\n");
}