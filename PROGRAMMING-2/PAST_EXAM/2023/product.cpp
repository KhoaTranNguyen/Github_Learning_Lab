#include <iostream>
#include "Product.h"

using namespace std;

int main() {
    Product m0;
    m0.describe();

    Product m1(10.5, 2.3, 1.2);
    m1.describe();

    Product m2(15, 2.2, 0.5);
    m2.describe();

    Product m3(m1);
    m3.describe();

    m3 = m1 + m2;
    m3.describe();

    cout << "Is m3 = m1? " << (m3 == m1) << endl;

    m3 = m1;
    m3.describe();

    cout << "Is m3 = m1? " << (m3 == m1) << endl;

    return 0;
}