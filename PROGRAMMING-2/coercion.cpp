#include <iostream>
using namespace std;

void show(double x) {
    cout << "Value: " << x << endl;
}

void show(float x) {
    cout << "Value: " << x << endl;
}

int main() {
    float a = 3.141592;             // ~7 decima digits
    double b = 3.141592653589793;   // ~15-16 decimal digits
    show(a);
    show(b);

    int c;
    show(c);
    show(static_cast<float>(c));
}