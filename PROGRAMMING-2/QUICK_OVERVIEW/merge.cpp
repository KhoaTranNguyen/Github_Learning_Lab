#include <iostream>
using namespace std;

void mergePart(int* arr, const int& left, const int& mid, const int& right) {
    int i = left, j = mid + 1;
    int k = 0; // temp: idx
    int* temp = new int[right - left + 1];

    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while(i <= mid) temp[k++] = arr[i++];
    while(j <= right) temp[k++] = arr[j++];

    for (int m = 0; m < k; m++) {
        arr[left+m] = temp[m];
    }
    delete []temp;
}

void mergeSort(int* arr, const int& left, const int& right) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    mergePart(arr, left, mid, right);
}

int main() {
    int size;
    cout << "Size: ";
    cin >> size;
    int* arr = new int[size];
    cout << "Elements: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i]; // E.g: 1 3 4 5 6
    }
    mergeSort(arr, 0, size - 1);
    for (int k = 0; k < size; k++) {
        cout << arr[k] << " ";
    }
    cout << "[Sorted]" << endl;
}