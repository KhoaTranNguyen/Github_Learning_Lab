#include "beverage.h"

int main() {
    Beverage b0;
    b0.describe();

    Beverage b1(10.5, 2.3, 1.2);
    b1.describe();

    Beverage b2(15, 2.2, 0.5);
    b2.describe();

    Beverage b3(b1);
    b3.describe();

    b3 = b1 + b2;
    b3.describe();

    cout << "Is b3 = b1? " << (b3 == b1) << endl;

    b3 = b1;
    b3.describe();
    
    cout << "Is b3 = b1? " << (b3 == b1) << endl;
    return 0;
}