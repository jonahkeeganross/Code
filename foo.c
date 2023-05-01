#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


/*
 * Write a recursive program that implements the following function
 * foo(N) = foo(N - 1) + foo(N - 2) + foo(N - 3) + foo(N - 4) + 1
 */


int _findFooValue(int n, int n_1, int n_2, int n_3, int n_4);
int findFooValue(int n);

int main(){
    // runs the main function
    int N;


    printf("Enter a value for n: ");
    scanf("%d", &N);


    int finalFoo = 0;
   
    finalFoo += findFooValue(N);


    printf("Foo(%d) = %d\n", N, finalFoo);

    return 0;
}

int findFooValue(int n){
    return _findFooValue(n, 3, 6, 2, 7);
}


int _findFooValue(int n, int n_1, int n_2, int n_3, int n_4){
    // finds the value based on the equation above with a recursive function using only one recursive call

    if(n == 0){
        return n_1;
    }
    else if(n == 1){
        return n_2;
    }
    else if(n == 2){
        return n_3;
    }
    else if(n == 3){
        return n_4;
    }
    else{
        return _findFooValue(n - 1, n_2, n_3, n_4, n_4 + n_3 + n_2 - n_1 + 1);
    }
}

