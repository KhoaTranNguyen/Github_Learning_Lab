#include <iostream>

using namespace std;

class Circle {
    private:
        int radius;
    public:
        Circle(): radius(0) {}
        Circle(const int& radius): radius(radius) {}

        void describe() const {
            cout << "radius: " << radius << endl;
        }

        const Circle operator+(const Circle& other) const {
            return Circle(radius + other.radius);
        }
};

template<class T>
class Data {
    private:
        T data_1;
        T data_2;
    public:
        Data(T data_1, T data_2): data_1(data_1), data_2(data_2) {}
        
        T sum() const{
            return data_1 + data_2;
        }
};