#include <iostream>

int factorial(int num){
    if (num == 0) return 1;
    return num*factorial(num-1);
}

int main(){
    int num;
    std::cin>>num;
    int fact = factorial(num);
    std::cout<<fact<<"\n";
}