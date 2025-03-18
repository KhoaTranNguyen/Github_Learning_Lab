#include <stdio.h>
#include <stdlib.h>

void mergeParts(int *arr, int left, int mid, int right, int *counter) {
    int i = left, j = mid + 1;
    int k = 0;
    int size = right - left + 1; // Size of the temporary array
    int *temp = (int *)malloc(size * sizeof(int)); // Dynamically allocate memory for temp

    while (i <= mid && j <= right) {
        (*counter)++; // Increment the counter for each comparison
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
        arr[left + i] = temp[i];
    }

    free(temp); // Free the allocated memory
}

void mergeSort(int *arr, int left, int right, int *counter) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    mergeSort(arr, left, mid, counter);
    mergeSort(arr, mid + 1, right, counter);

    mergeParts(arr, left, mid, right, counter);
}

int main() {
    int arr[3][20] = {
        {1, 16, 12, 26, 25, 35, 33, 58, 45, 42, 56, 67, 83, 75, 74, 86, 81, 88, 99, 95},
        {1, 17, 21, 42, 24, 27, 32, 35, 45, 47, 57, 23, 66, 69, 70, 76, 87, 85, 95, 99},
        {22, 20, 81, 38, 95, 84, 99, 12, 79, 44, 26, 87, 96, 10, 48, 80, 1, 31, 16, 92}
    };

    for (int n = 0; n < 3; n++) {
        int x = sizeof(arr[n]) / sizeof(arr[n][0]);
        int counter = 0;
        mergeSort(arr[n], 0, x - 1, &counter);
        for (int i = 0; i < x; i++) {
            printf("%d ", arr[n][i]);
        }
        printf("[eff_arr_%d = %d]\n", n + 1, counter);
    }

    return 0;
}