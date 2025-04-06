#include <stdio.h>

void function(int n){
    if(n<=1) return;
    for(int i=1; i<=3; i++){
        function(n-1);
    }
}

int main(){
    function(3);
}