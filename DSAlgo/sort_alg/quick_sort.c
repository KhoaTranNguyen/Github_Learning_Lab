#include <stdio.h>

// Function to find the median of three and return a pointer to the median value
int* pivotChosen(int *a, int *b, int *c) {
    if ((*a > *b && *a < *c) || (*a > *c && *a < *b)) return a;  // a is the median
    if ((*b > *a && *b < *c) || (*b > *c && *b < *a)) return b;  // b is the median
    return c;  // c is the median
}

// Swap function
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Partition function using the two-pointer method
int partition(int Arr[], int left, int right) {
    int mid = (left + right) / 2;
    int* pivotPtr = pivotChosen(&Arr[left], &Arr[mid], &Arr[right]);
    int pivotValue = *pivotPtr;

    // Move pivot to the end
    // Only swap if pivotPtr is not already at Arr[right]
    if (pivotPtr != &Arr[right]) {
        swap(pivotPtr, &Arr[right]);
    }

    int P1 = left;        // Pointer moving from left to right
    int P2 = right - 1;   // Pointer moving from right to left

    while (1) {
        // Move P1 right skipping elements smaller than the pivot
        while (P1 <= P2 && Arr[P1] < pivotValue) P1++;

        // Move P2 left skipping elements greater than the pivot
        while (P1 <= P2 && Arr[P2] > pivotValue) P2--;

        // If P1 has crossed P2, stop
        if (P1 >= P2) break;

        // Swap elements at P1 and P2
        swap(&Arr[P1], &Arr[P2]);

        // Move P1 and P2 further
        P1++;
        P2--;
    }

    // Swap P1 with pivot (now at rightmost position)
    swap(&Arr[P1], &Arr[right]);

    return P1;  // New pivot position
}

// QuickSort function
void quickSort(int Arr[], int left, int right) {
    if (left < right) {
        int pivotIndex = partition(Arr, left, right);

        quickSort(Arr, left, pivotIndex - 1);
        quickSort(Arr, pivotIndex + 1, right);
    }
}

// Main function
int main() {
    int Arr[] = {1,3,5,7,9,10,8,6,4,2};
    int size = sizeof(Arr) / sizeof(int);

    quickSort(Arr, 0, size - 1);
    
    for (int i = 0; i < size; i++) {
        printf("%d ", Arr[i]);
    }
    printf("\n");

    return 0;
}