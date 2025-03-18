#include <stdio.h>

void swap(int *xp, int *yp){
    int temp;
    temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int insertion_sort(int *arr, int size){
    int counter = 0;
    for (int *p = &arr[0]; p < &arr[size]; p++){
        for(int *i = p; i > &arr[0] && *(i-1)>*i; i--){
            swap(i, i-1);
            counter++;
        }
    }
    return counter;
}

int main(){
    int arr[3][20] = {
        {1, 16, 12, 26, 25, 35, 33, 58, 45, 42, 56, 67, 83, 75, 74, 86, 81, 88, 99, 95},
        {1, 17, 21, 42, 24, 27, 32, 35, 45, 47, 57, 23, 66, 69, 70, 76, 87, 85, 95, 99},
        {22, 20, 81, 38, 95, 84, 99, 12, 79, 44, 26, 87, 96, 10, 48, 80, 1, 31, 16, 92}
    };

    for(int n = 0; n<3; n++){ 
        int x = sizeof(arr[n]) / sizeof(int);
        int efficiency = insertion_sort(arr[n], x);
        for (int i = 0; i<x; i++){
            printf("%d ", arr[n][i]);
        }
        printf("[eff_arr_%d = %d]\n", n+1, efficiency);
    }
}