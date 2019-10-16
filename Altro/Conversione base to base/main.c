#include <stdio.h>
#include <math.h>
#include <time.h>

const int N = 20;

void DtoB0(int dec, int bin[N]);
void DtoB(int dec, int bin[N]);

int main() {
    clock_t begin = clock();

    int a = 45;
    int b[N];
    DtoB(a, b);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spent: %f", time_spent);
    return 0;
}

// il vettore del numero binario è al contrario
void DtoB0(int dec, int bin[N]){
    int bin0[N];
    int i, j, k;
    for(i=0; dec>0; i++){
        bin0[i] = dec % 2;
        dec /= 2;
    }
    bin0[i] = -1;
    i--;
    for(j=0, k=i; j<=i; j++, k--){
        bin[j] = bin0[k];
    }
    bin[j] = -1;
}

// il vettore del numero binario è già girato nel verso giusto
void DtoB(int dec, int bin[N]){
    double n = log2(dec);
    int i;
    double power;

    for(i=n, bin[i+1] = -1; i >= 0 && dec > 0; i--){
        power = pow(2, i);
        if((dec - power) >= 0){
            bin[i] = 1;
            dec -= power;
        }
        else
            bin[i] = 0;

    }
}