#include <iostream>
// #include <stdlib.h>
// #define min(a,b) (((a)<(b))?(a):(b))
// #define max(a,b) (((a)>(b))?(a):(b))

int max_sub_sum(int *arr, int last){
    int *p = &arr[0];
    int maxx = *p;
    int cursum = 0;

    while (p < &arr[last]){
        if (cursum + *p >= 0){
            maxx = std::max(maxx, cursum + *p);
            cursum += *p;
        }
        else cursum = 0;
        maxx = std::max(maxx, *p);
        p++;
    }
    return maxx;
}

int main(){
    int size;
    std::cout<<"Size: ";
    std::cin>>size;
    int* arr = new int[size];
    // arr = (int *)calloc(size, sizeof(int));
    for (int i=0; i<size; i++){
        std::cin>>arr[i];
    }
    
    int maxx = max_sub_sum(arr, size);
    std::cout<<"Max Sub_sum: "<<maxx<<"\n";

    delete []arr;
}