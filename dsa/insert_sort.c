#include <stdio.h>

void swap(int *xp, int *yp){
    int temp;
    temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void insert_sort(int *arr, int size){

    for (int *p = &arr[0]; p < &arr[size]; p++){
        for(int *i = p; i > &arr[0] && *(i-1) > *i; i--){
            swap(i, i-1);
        }
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