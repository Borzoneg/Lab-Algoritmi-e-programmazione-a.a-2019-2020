#include <stdio.h>
#include <stdlib.h>

int majority( int *a, int N);

int main() {
    int N = 21;
    int a[] = {2, 3, 2, 3, 3, 5, 5,
               3, 3, 3, 3, 3, 5, 4,
               2, 3, 5, 4, 3, 3, 1};
    int M = 5;
    int b[] = { 2,3,2,3,3};

    printf("%d", majority(a, N));
    return 0;
}


int majority( int *a, int N){
    int l = 0, i, k = 0, sx, dx, Nmezzi = N/2, dispari = 0;
    if(N%2 != 0)
        dispari = 1;
    int c[(N/2)+dispari], b[(N/2)];

    if(N == 1)
        return a[0];

    else{
        for(i=0; i<Nmezzi; i++){
            b[i] = a[i];
            c[i] = a[i+Nmezzi];
        }
        if(dispari)
            c[(N/2)] = a[N-1];
       sx =  majority(b, N/2);
       dx = majority(c, N/2);
    }

    if(sx != -1){
        while(l < N){
            if(sx == a[l])
                k++;
            l++;
        }
        if(k > N/2)
            return sx;
    }
    l=0;
    k=0;
    if(dx != -1) {
        while (l < N) {
            if (dx == a[l])
                k++;
            l++;
        }
        if(k > (N/2))
            return dx;
    }
    return -1;
}
