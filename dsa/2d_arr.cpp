#include <iostream>

int main(){
    int x, y;
    std::cin>>x>>y;

    int arr[x][y];
    int sum = 0;
    for (int row=0; row<x; row++){
        for(int column=0; column<y; column++){
            std::cin>>arr[row][column];
            sum += arr[row][column];
        }
    }
    
    return 0;
}