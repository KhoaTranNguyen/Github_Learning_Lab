#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Quadrilaterals {
    private:
        double width;
        double height;
        double size;
        
    public:
        Quadrilaterals(): width(1), height(1), size(1) {}
        Quadrilaterals(double w, double h): width(w), height(h), size(abs(width) * abs(height)) {}
//        Quadrilaterals(double w, double h, double s): width(w), height(h), size(s) {}

        void print()            {cout << size;}
        double area()           {return abs(width) * abs(height);}

        const double w()        {return abs(width);}
        const double h()        {return abs(height);}
        const double s()        {return abs(size);}
};



class Rectangle: public Quadrilaterals {
    public:
        Rectangle():                                    Quadrilaterals() {}
        Rectangle(double w, double h):                  Quadrilaterals(w, h) {}
//        Rectangle(double w, double h, double s):    Quadrilaterals(w, h, s) {}
};

class Parallelogram: public Quadrilaterals {
    public:
        Parallelogram():                                Quadrilaterals() {}
        Parallelogram(double w, double h):              Quadrilaterals(w, h) {}
//        Parallelogram(double w, double h, double s):    Quadrilaterals(w, h, s) {}
};

class Trapezium: public Quadrilaterals {
    private:
        double s_width;
        double l_width;

    public:
        Trapezium():                                   Quadrilaterals(), s_width(1), l_width(1) {}
        Trapezium(double s_w, double l_w, double h):   Quadrilaterals((s_w + l_w) / 2, h), s_width(s_w), l_width(l_w) {}
//        Trapezium(double s_w, double l_w, double h, double s):  Quadrilaterals((s_w + l_w) / 2, h, s), s_width(s_w), l_width(l_w) {}

        const double s_w()      {return abs(s_width);}
        const double l_w()      {return abs(l_width);}
};



class Array_of_Quadrilaterals {
    private:
        unsigned num_element;
        Quadrilaterals *arr;
    
    public:
        Array_of_Quadrilaterals(): num_element(0), arr(nullptr) {}
        Array_of_Quadrilaterals(const unsigned& num): num_element(num) {

            arr = new Quadrilaterals[num];

            for (int i = 0; i < num; i++) {
                unsigned r = rand() % 3;

                if (r == 0)         arr[i] = Rectangle(rand() % 100, rand() % 100);
                if (r == 1)         arr[i] = Parallelogram(rand() % 100, rand() % 100);
                if (r == 2)         arr[i] = Trapezium(rand() % 100, rand() % 100, rand() % 100);
            }

        }

        void detail() {
            for (int i = 0; i < num_element; i++) {
                if (i % 3 == 0)     cout << "Index " << i << ", Type: Rectangle, Area: ";
                if (i % 3 == 1)     cout << "Index " << i << ", Type: Parallegoram, Area: ";
                if (i % 3 == 2)     cout << "Index " << i << ", Type: Trapezium, Area: ";

                cout << arr[i].s() << endl;
            }
            cout << "---------------------------------------" << endl;
        }

        ~Array_of_Quadrilaterals() {delete []arr;}
};