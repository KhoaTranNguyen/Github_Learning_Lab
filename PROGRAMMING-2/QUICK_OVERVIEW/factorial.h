#pragma once
#include <iostream>
using namespace std;

long long int factorial(const int& num) {
    if (num == 1) return 1;
    return num*factorial(num-1);
}