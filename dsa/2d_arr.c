#include <stdio.h>
#include <stdlib.h>

int main(){
    int x, y;
    scanf("%d %d", &x, &y);
    int **arr;
    int sum = 0;
    arr = (int **)calloc(x, sizeof(int *));
    for(int i = 0; i < x; i++){
        arr[i] = (int *) calloc(y, sizeof(int));
        for (int j = 0; j < y; j++){
            scanf("%d", &arr[i][j]);
            sum += arr[i][j];
        }
    }
    printf("Sum: %d\n", sum);

    int **arrT;
    arrT = (int **)calloc(y, sizeof(int *));
    for(int u = 0; u < y; u++){
        arrT[u] = (int *)calloc(x, sizeof(int));
    }

    for (int i = 0; i<x; i++){
        for(int j = 0; j<y; j++){
            arrT[j][i] = arr[i][j];
        }
    }

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            printf("%d  ", arr[i][j]);
            if (j == x - 1){
                printf("\n");
            }
        }
        free(arr[i]);
    }
    free(arr);

    for(int u = 0; u < y; u++){
        for(int v = 0; v < x; v++){
            printf("%d  ", arrT[u][v]);
            if (v == x - 1){
                printf("\n");
            }
        }
        free(arrT[u]);
    }
    free(arrT);

    return 0;
}