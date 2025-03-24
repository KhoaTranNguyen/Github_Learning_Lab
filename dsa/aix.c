#include <stdio.h>

long long int main(){
    long long int Arr[] = {1, 2, 3, 4, 5};
    long long int sizeofArr = sizeof(Arr)/sizeof(long long int);
    long long int sumofArr = 0;
    long long int myNum;

    scanf("%lld", &myNum);

    for(long long int i=0; i < sizeofArr; i++){
        myNum *= myNum;
        sumofArr += Arr[i]*myNum;
    }

    printf("%lld", sumofArr);
}