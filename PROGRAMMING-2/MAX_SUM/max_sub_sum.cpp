#include <iostream>

int max_sub_sum(int *c_arr, int x){
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
    std::cout<<"Size: ";
    std::cin>>x;
    int arr[x];
    for (int i=0; i<x; i++){
        std::cin>>arr[i];
    }
    
    int maxx = max_sub_sum(arr, x);
    std::cout<<"Max Sub_sum: "<<maxx<<"\n";
}