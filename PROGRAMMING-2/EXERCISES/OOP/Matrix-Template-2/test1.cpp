#include <iostream>
#include "Matrix.h"

#define NAMED_MATRIX(T, var, rows, cols) Matrix<T> var(rows, cols, #var)
#define DECLARE_MATRIX(T, name, ...) Matrix<T> name(#name, { __VA_ARGS__ })

int main() {
    // Create 3x3 matrix of doubles
    DECLARE_MATRIX(double, A, 
        {1.0, 2.0, 3.0}, 
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0} //max row
    );

    std::cout << A;
    std::cout << A.frobenius() << std::endl;
    std::cout << A.row_sum_norm() << std::endl;
    std::cout << A.total_norm() << std::endl;
    return 0;
}
