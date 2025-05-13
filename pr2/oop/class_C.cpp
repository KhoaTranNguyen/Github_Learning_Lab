#include <iostream>
using namespace std;

class C {
    protected: int x;
    public: void f(){
        cout << "C::f()" << endl;
    };
};
class C1: public C {
    protected: int x1;
    public: void h(C *obj){
        C1* objz;
        objz->x1;
        C1* objx;
        objx->x1;
        C2 *obj2;
        C3 *obj3;
        C1* obj1;
        obj1->x;
        obj->x;
        obj2->x;
        obj3->x;
    };
};
class C2: public C1 {
    public: int x2;
};
class C3: public C {
    public: f(){
        cout << "C3::f()" << endl;
        C3* obj3;
        obj3->x;
    };
};

int main() {
    C1 obj1;
    obj1.x;     //allowed, x is protected in class C
    obj1.f();   //allowed, f() is public in class C
    obj1.x1;  //allowed, x1 is protected in class C1
    obj1.x2;  //not allowed, x2 is not in C or C1
}