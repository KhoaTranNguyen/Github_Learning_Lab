#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Counter;

int main() {
    int arr[] = {2, 1, 1, 3, 5, 7, 9, 9, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    Counter *counters = NULL;
    int size = 0;
    int capacity = 0;
    
    int max_count = 0;
    int result = -1;
    
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        int found = 0;
        
        // Check if the current number exists in the counters array
        for (int j = 0; j < size; j++) {
            if (counters[j].value == num) {
                counters[j].count++;
                if (counters[j].count > max_count) {
                    max_count = counters[j].count;
                    result = num;
                }
                found = 1;
                break;
            }
        }
        
        // If not found, add a new entry to the counters array
        if (!found) {
            if (size >= capacity) {
                int new_capacity = (capacity == 0) ? 1 : capacity * 2;
                Counter *new_counters = realloc(counters, new_capacity * sizeof(Counter));
                if (!new_counters) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(1);
                }
                counters = new_counters;
                capacity = new_capacity;
            }
            counters[size].value = num;
            counters[size].count = 1;
            if (1 > max_count) {
                max_count = 1;
                result = num;
            }
            size++;
        }
    }
    
    printf("%d\n", result);
    
    free(counters);
    
    return 0;
}