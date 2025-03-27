#include <stdio.h>
#include <stdlib.h>

void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(int arr[], int size, int num_bins, int min, int max){
    int range = max - min + 1;
    int **bins = (int **)calloc(num_bins, sizeof(int *));
    int *counts = (int *)calloc(num_bins, sizeof(int));

    for (int i = 0; i < num_bins; i++){
        counts[i] = 0;
        bins[i] = (int*)calloc(size, sizeof(int));
    }

    for (int i = 0; i < size; i++){
        int bin_index = (arr[i] * num_bins) / range;
        if (bin_index <= 0){
            bin_index = 1;
        }
        bins[bin_index-1][counts[bin_index-1]] = arr[i];
        counts[bin_index-1]++;
    }
    
    int index = 0;
    for (int i = 0; i < num_bins; i++) {
        if (counts[i] > 0) {
            insertionSort(bins[i], counts[i]); // Sort the bin
            for (int j = 0; j < counts[i]; j++) {
                arr[index++] = bins[i][j]; // Concatenate sorted bins back to arr
            }
        }
    }
}

void min_max(int arr[], int size, int *min, int *max){
    *min = arr[0];
    *max = arr[0];
    for(int i=1; i<size; i++){
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

int main(){
    int myArr[] = {5,1,2,3,4,3,2,1,1,5,4,5};
    int size = sizeof(myArr) / sizeof(int);
    int num_bins = 5;

    int min, max;
    min_max(myArr, size, &min, &max);

    bucketSort(myArr, size, num_bins, min, max);

    for (int i = 0; i < size; i++) {
        printf("%d ", myArr[i]);
    }
    printf("\n");
}