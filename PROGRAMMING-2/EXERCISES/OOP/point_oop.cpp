#include <iostream>

class Point {
    private:
    int x,y; //coordinates
    
    public:
    Point(int xVal = 0, int yVal = 0) { x = xVal; y = yVal; }
    int getX() { return x; }
    int getY() { return y; }
    };

int main() {
    Point p1(3, 4); // Create a Point object with x=3 and y=4
    std::cout << "Point coordinates: (" << p1.getX() << ", " << p1.getY() << ")" << std::endl;
    return 0;
}