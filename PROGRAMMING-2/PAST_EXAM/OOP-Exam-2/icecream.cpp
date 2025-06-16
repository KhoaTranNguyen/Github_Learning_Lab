#include "IceCream.h"

int main() {
    IceCream ic0;
    ic0.describe();

    IceCream ic1(10.5, 2.3, 1.2);
    ic1.describe();

    IceCream ic2(15, 5.2, 7.5);
    ic2.describe();

    IceCream ic3(ic1);
    ic3.describe();

    ic3 = ic2 - ic1;
    ic3.describe();

    cout << "Is ic2 <= ic3? " << (ic2 <= ic3) << endl;

    ic3 = ic1;
    ic3.describe();

    cout << "Is ic3 <= ic1? " << (ic3 <= ic1) << endl;

    return 0;
}