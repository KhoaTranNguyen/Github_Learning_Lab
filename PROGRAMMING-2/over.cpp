#include <iostream>
using namespace std;

class Point {
public:
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y) {}
    virtual void hello_xy() {cout << "x, y: " << x << " " << y;}
};

class Point3D: public Point {
public:
    int z;
    Point3D(int x, int y, int z): Point(x, y), z(z) {}
    void hello_z() {
        cout << "z: " << z;
    }
};

int main() {
    Point* p = new Point(3, 4);
    Point3D* cp = reinterpret_cast<Point3D*>(p);
    if (cp == nullptr) cout << "false";
    else cp->hello_z();

    Point p1;
    p1.hello_xy();
}