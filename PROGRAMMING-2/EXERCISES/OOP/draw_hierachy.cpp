#include <iostream>
using namespace std;

class Shape {
    public:
        Shape() {}
        virtual void draw() {cout << "Shape ";}
};

class Circle: public Shape {
    public:
        Circle() {}
        void draw() {cout << "◯ ";}
};

class Square: public Shape {
    public:
        Square() {}
        void draw() {cout << "▢ ";}
};

class Triangle: public Shape {
    public:
        Triangle() {}
        void draw() {cout << "△ ";}
};

int main(){
    Circle c;
    Square sq;
    Triangle tr;

    Shape* array[3] = { &c, &sq, &tr };

    for (int i = 0; i < 3; i++) {
        array[i]->draw();
    }

    return 0;
}