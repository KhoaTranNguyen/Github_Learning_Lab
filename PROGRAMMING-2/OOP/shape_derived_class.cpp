#include <iostream>
using namespace std;

class Shape {
    protected:
        int edge_num;
        int length;
    public:
        Shape(int e, int len) : edge_num(e), length(len) {}
        virtual int circuit() const { return edge_num * length; }  // Use a function instead
};

class Rectangle: public Shape {
    protected:
        int width;
    public:
        Rectangle(int w, int len) : Shape(4, len), width(w) {}
        // Optionally override circuit() if width is different from length
        int circuit() const override {
            return 2 * (length + width);
        }
};

class Triangle: public Shape {
    public:
        Triangle(int len) : Shape(3, len) {}
};

int main(){
    Shape s(3, 4);
    cout << s.circuit() << endl;

    Triangle t(4);
    cout << t.circuit() << endl;

    Rectangle r(3, 3);
    cout << r.circuit() << endl;
    return 0;
}