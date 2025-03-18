#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id;
    int age;
    char name[20];
    float salary;
} Worker;

void swap(Worker *xp, Worker *yp){
    Worker temp;
    temp = *xp;
    *xp = *yp;
    *yp = temp;
}

Worker *insertion_sort(Worker *a, int size){
    Worker *p = &a[0];
    while (p < &a[size]){
        Worker *i = p;
        while(i > &a[0] && (*(i-1)).salary<(*i).salary){
            swap(i, i-1);
            i--;
        }
        p++;
    }
}

int main(){
    int size;
    printf("Quantity: ");
    scanf("%d", &size);
    Worker *arrWorker;
    arrWorker = (Worker *)malloc(size*sizeof(Worker));
    float salary_sum = 0.0f;
    printf("Id Name Age Salary: \n");
    for (int idx = 0; idx < size; idx++){
        Worker* d1 = &arrWorker[idx];
        printf("%d: ", idx);
        scanf("%d %s %d %f", &(*d1).id, (*d1).name, &(*d1).age, &(*d1).salary);
        salary_sum += (*d1).salary;
    }

    insertion_sort(arrWorker, size);
    printf("Reformat...\n");
    for (int u = 0; u < size; u++){
        Worker* d1 = &arrWorker[u];
        printf("%d: %d %s %d %.2f\n", u, (*d1).id, (*d1).name, (*d1).age, (*d1).salary);
    }
    return 0;
}