#include <iostream>
#include "Matrix.h"

#define NAMED_MATRIX(T, var, rows, cols) Matrix<T> var(rows, cols, #var)
#define DECLARE_MATRIX(T, name, ...) Matrix<T> name(#name, { __VA_ARGS__ })

int main() {
    // Create 2x3 matrix of doubles
    DECLARE_MATRIX(double, A, 
        {1.0, 2.0, 3.0}, 
        {4.0, 5.0, 6.0}
    );

    // Create 3x2 matrix of doubles
    DECLARE_MATRIX(double, B, 
        {7.0, 8.0}, 
        {9.0, 10.0}, 
        {11.0, 12.0}
    );

    // Multiply A * B
    Matrix<double> C = A * B;

    std::cout << "Matrix A:\n" << A << "\n";
    std::cout << "Matrix B:\n" << B << "\n";
    std::cout << "Matrix C = A * B:\n" << C << "\n";

    // Expected C:
    // [ 58  64 ]
    // [139 154 ]

    return 0;
}
