#include <iostream>
using namespace std;

class C {
    protected: int x;
};

class C1: public C {
    public: void h() {
        C *obj;
        C1 *obj1;
        C2 *obj2;
        C3 *obj3;
        
        obj->x;
        obj1->x;
        obj2->x;
        obj3->x;
    }
};

class C2: public C1 {};

class C3: public C {};