#include <iostream>

using namespace std;

class C {  
    protected: int x;  
    public: void f(){};
        // friend class C1;  
};  
 
class C1: public C {  
    protected: int x1;  
    public:
    void h(){
        cout << x;
        C objc;     objc.x;
        C *obj;     obj->x;
        C1 *obj1;   obj1->x;
        C2 *obj2;   obj2->x;
        C3 *obj3;   obj3->x;
    };  
        
};  

class C2: public C1 {  
    public: int x2;  
};  

class C3: public C {  
    public: void f(){};  
}; 

int main() {
    C1 obj1;
    obj1.f();
    return 0;
}