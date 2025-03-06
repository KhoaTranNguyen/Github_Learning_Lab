#include <iostream>
#include "swap.h"
// #include <math.h>

int swap(int *xp, int *yp){
    int temp;
    temp = *xp;
    *xp = *yp;
    *yp = temp;
    return 0;
}

int max_sub_arr(int *c_arr, int x){
    int *pnter = &c_arr[0];
    int maxx = *pnter;
    int cursum = 0;
    while (pnter < &c_arr[x]){
        if (cursum + *pnter >= 0){
            maxx = std::max(maxx, cursum + *pnter);
            cursum += *pnter;
        }
        else{
            cursum = 0;
        }
        maxx = std::max(maxx, *pnter);
        pnter++;
    }
    return maxx;
}

int main(){
    int x;
    std::cin>>x;
    int arr[x];
    int c_arr[x];
    for (int i=0; i<x; i++){
        std::cin>>arr[i];
        c_arr[i] = arr[i];
    }
    
    int *pnter = &arr[0];
    int arr_sum = 0;

    while (pnter < &arr[x]){
        arr_sum += *pnter;
        int *ipnter = pnter;
        while(ipnter > &arr[0] && *(ipnter-1)>*ipnter){
            swap(ipnter, ipnter-1);
            ipnter -= 1;
        }
        pnter++;
    }
    for (int i=0; i<x; i++){
        std::cout<<arr[i]<<", ";
    }
    std::cout<<arr_sum<<"\n";
    
    int maxx = max_sub_arr(c_arr, x);
    std::cout<<maxx<<"\n";
}