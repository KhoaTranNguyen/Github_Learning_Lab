#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

class Complex {
    private:
        double real;
        double imaginary;
        double modulus;
    
    public:
        Complex(): real(0), imaginary(0), modulus(0) {}
        Complex(const double& a, const double& b): real(a), imaginary(b), modulus(sqrt(a*a + b*b)) {}

        bool operator> (const Complex& other) const {
            return modulus > other.modulus;
        }

        Complex& operator= (const Complex& other) {
            if (this != &other) {
                real = other.real;
                imaginary = other.imaginary;
                modulus = other.modulus;
            }

            return *this;
        }

        void set_real(const double& a)  {real = a;  modulus = sqrt(real * real + imaginary * imaginary);}
        void set_imaginary(const double& b)  {imaginary = b;  modulus = sqrt(real * real + imaginary * imaginary);}
        string modul() const {return to_string(modulus);}
};


class Array_of_Complex {
    private:
        unsigned num_element;
        Complex* arr;

        void merge_parts(Complex* arr, unsigned left, unsigned mid, unsigned right) {
            unsigned i = left, j = mid + 1;
            unsigned k = 0; // temp idx: right

            Complex* temp = new Complex[right - left + 1];
            
            while (i <= mid && j <= right) {
                if (arr[i] > arr[j]) temp[k++] = arr[i++];
                else    temp[k++] = arr[j++];
            }

            while (i <= mid)     temp[k++] = arr[i++];
            while (j <= right)   temp[k++] = arr[j++];

            for (unsigned m = 0; m < k; m++)    arr[left + m] = temp[m];
                
            delete []temp;
        }

        void merge_sort(Complex* arr, unsigned left, unsigned right) {
            if (left >= right) return;

            unsigned mid = (left + right) / 2;

            merge_sort(arr, left, mid);
            merge_sort(arr, mid + 1, right);
            merge_parts(arr, left, mid, right);
        }
    
    public:
        Array_of_Complex(): num_element(0), arr(nullptr) {}
        Array_of_Complex(unsigned num): num_element(num), arr(nullptr) {

            if (num == 0) {return;}

            arr = new Complex[num];
            
            for (unsigned i = 0; i < num; i++) {
                arr[i].set_real(rand() % 100);
                arr[i].set_imaginary(rand() % 100);
            }
            merge_sort(arr, 0, num - 1);

        }

        void detail() {
            if (arr) {
                cout << "Decreasing array of complex number: "    << endl;
                for (unsigned i = 0; i < num_element; i++) { 
                    cout << arr[i].modul() << ","                 << endl;  
                }
                cout << "---------------------------------------" << endl;
            }
        }

        ~Array_of_Complex() {delete []arr;}
};