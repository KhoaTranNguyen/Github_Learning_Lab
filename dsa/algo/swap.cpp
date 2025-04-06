#include <iostream>

int swap(int *x, int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int main(){
    int x = 10;
    int y = 11;
    swap(&x, &y);
    std::cout << x << " " << y;
}