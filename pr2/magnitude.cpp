#include <iostream>
#include <fstream>
#include <string>
#include <complex>

using namespace std;

void swap(complex<double> *a, complex<double> *b) {
    complex<double> temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(complex<double> *a, int size) {
    for (int i = 1; i < size; ++i) {
        int j = i;
        while (j > 0 && abs(a[j - 1]) > abs(a[j])) {
            swap(&a[j], &a[j - 1]);
            j--;
        }
    }
}

int main() {
    ifstream my_file("magnitude_ex.txt");

    if (!my_file) {
        cout << "Error: Unable to open the file." << endl;
        return 1;
    }

    string line;
    int size;

    if (getline(my_file, line)) {
        size = stoi(line);
    } else {
        cout << "Error: Empty file" << endl;
        return 1;
    }

    // Dynamic allocation
    complex<double>* arr = new complex<double>[size];
    float real, imag;
    int loop = 0;

    // Read complex numbers
    while (loop < size && my_file >> real >> imag) {
        arr[loop++] = complex<double>(real, imag);
    }

    insertion_sort(arr, size);
    if (loop < size) {
        cout << "Error: Not enough numbers in file" << endl;
        delete[] arr;  // Clean up before exit
        return 1;
    }
    
    // Print first 5 elements or all if size < 5
    for (int idx = 0; idx < 5 && idx < size; idx++) {
        cout << arr[idx] << " ";
    }
    cout << endl;

    delete[] arr;  // Release memory
    my_file.close();
    return 0;
}