#include <iostream>

void mergeParts(int *arr, int left, int mid, int right){
    int i = left, j = mid + 1;
    int k = 0;
    int* temp = new int[right - left + 1];

    while (i <= mid && j <= right){
        // i: left → mid, j: mid+1 → right
        int nextValue;

        if (arr[i] < arr[j]) nextValue = arr[i++];
        else nextValue = arr[j++];

        temp[k++] = nextValue;
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int i = 0; i < k; i++)
        arr[left+i] = temp[i];

    delete []temp;
}

void mergeSort(int *arr, int left, int right){
    if (left>=right) return;
        
    int mid = (left + right)/2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    mergeParts(arr, left, mid, right);
}

int main(){
    int size;
    std::cout<<"Size: ";
    std::cin>>size;
    int *arr = new int[size];
    std::cout<<"Elements: "<<std::endl;
    for (int *p = arr; p < &arr[size]; p++){
        std::cin>>*p;
    }
    mergeSort(arr, 0, size-1);
    for (int *p = arr; p < &arr[size]; p++){
        std::cout<<*p<<" ";
    } 
    std::cout<<"[Sorted]"<<std::endl;
    delete []arr;
}