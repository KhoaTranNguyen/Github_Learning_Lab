#include <stdio.h>
#include <stdlib.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

int max_sub_sum(int* arr, int last){
    int *p = &arr[0];
    int maxx = *p;
    int cursum = 0;

    while (p < &arr[last]){
        if(cursum + *p >= 0){
            maxx = max(maxx, cursum + *p);
            cursum += *p;
        }
        else cursum = 0;
        maxx = max(maxx, *(p));
        p++;
    }
    return maxx;
}

int main(){
    int size;
    printf("Size: ");
    scanf("%d", &size);
    int *arr;
    arr = (int *)calloc(size, sizeof(int));
    for (int i = 0; i<size; i++){
        scanf("%d", &arr[i]);
    }

    int maxx = max_sub_sum(arr, size);
    printf("Max Sub_sum: %d\n", maxx);

    free(arr);
}