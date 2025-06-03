#include <iostream>
#include <math.h>
#include <cstdlib>  // cho rand()
#include <ctime>    // cho time()
using namespace std;

class Complex {
private:
    double real;
    double imag;
public:
    Complex(): real(0), imag(0) {}
    Complex(double r, double i): real(r), imag(i) {}

    double modulus() const {
        return sqrt(real * real + imag * imag);
    }

    bool operator>(const Complex& other) const {
        return this->modulus() > other.modulus();
    }

    Complex operator=(const Complex& other) {
        if (this != &other) {  // phòng trường hợp tự gán
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Complex& t) {
        if (t.imag >= 0)
            os << t.real << "+" << t.imag << "i";
        else
            os << t.real << t.imag << "i";
        return os;
    }
};

void mergeParts(Complex *arr, int left, int mid, int right){
    int i = left, j = mid + 1;
    int k = 0;
    Complex* temp = new Complex[right - left + 1];

    while (i <= mid && j <= right){
        // i: left → mid, j: mid+1 → right
        Complex nextValue;

        if (arr[i] > arr[j]) nextValue = arr[i++];
        else nextValue = arr[j++];

        temp[k++] = nextValue;
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int i = 0; i < k; i++)
        arr[left+i] = temp[i];

    delete []temp;
}

void mergeSort(Complex *arr, int left, int right){
    if (left>=right) return;
        
    int mid = (left + right)/2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    mergeParts(arr, left, mid, right);
}

int main() {
    int size = 5;
    Complex* arr = new Complex[size];  // cấp phát mảng động size phần tử kiểu int

    srand(time(nullptr));  // khởi tạo seed cho rand()

    for (int i = 0; i < size; i++) {
        double real = rand() % 100;  // random 0-99
        double imag = rand() % 100;  // random 0-99
        arr[i] = Complex(real, imag);
    }

    mergeSort(arr, 0, size-1);

    // In mảng
    for (int i = 0; i < size; i++) {
        cout << arr[i].modulus() << " ";
    }
    cout << std::endl;

    // Giải phóng bộ nhớ sau khi dùng xong
    delete[] arr;

    return 0;
}