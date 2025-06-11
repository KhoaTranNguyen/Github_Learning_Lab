#include <iostream>
using namespace std;

class A1 {
    public:
        A1() {cout << "A1" << endl;}
};

class A2 {
    public:
        A2() {cout << "A2" << endl;}
};

class B1 {
    public:
        B1() {cout << "B1" << endl;}
};

class B2 {
    public:
        B2() {cout << "B2" << endl;}
};

class C1: public A1, public A2 {
    public:
        C1() {cout << "C1" << endl;}
};

class C2: public B1, public B2 {
    public:
        C2() {cout << "C2" << endl;}
};

class D: public C1, public C2 {
    public:
        D() {cout << "D" << endl;}
};

int main() {
    D obj;
    return 0;
}

// A1
// A2
// C1
// B1
// B2
// C2
// D