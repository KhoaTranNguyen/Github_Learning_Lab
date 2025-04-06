#include <stdio.h>

int main() {
    int arr[] = {1, 1, 1, 2, 3, 5, 7, 9, 9, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int max_count = 1;
    int current_count = 1;
    int result = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            current_count++;
            if (current_count > max_count) {
                max_count = current_count;
                result = arr[i];
            }
        } else {
            current_count = 1;
        }
    }
    
    printf("%d\n", result);  // Output: 1
    return 0;
}