#include <stdio.h>

void swap(int *xp, int *yp){
    int temp;
    temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sel_sort(int *Arr, int more_than_last){

    int *ptr = &Arr[0];

    while (ptr < &Arr[more_than_last]){

        int *store_smaller_idx = ptr;
        for(int *i = ptr+1; i < &Arr[more_than_last]; i++){
            if(*i < *store_smaller_idx)
                store_smaller_idx = i;
        }

        if(ptr != store_smaller_idx){
            swap(ptr, store_smaller_idx);
        }

        ptr++;
    }
}

int main(){
    int Arr[] = {1, 16, 12, 26, 25, 35, 33, 58, 45, 42, 56, 67, 83, 75, 74, 86, 81, 88, 99, 95};
    int size = sizeof(Arr) / sizeof(int);
    
    sel_sort(Arr, size);

    for (int i = 0; i < size; i++){
        printf("%d ", Arr[i]);
    } printf("\n");
}