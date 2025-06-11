#include <iostream>
#include "Complex.h"
#include "Quadrilaterals.h"
#include "CSStudent.h"

using namespace std;

int main() {
    srand(time(0));
    Array_of_Complex ac(10);
    ac.detail();

    Array_of_Quadrilaterals aq(10);
    aq.detail();

    CSStudent khoa;
    khoa.type_in();
    khoa.detail();
    return 0;
}