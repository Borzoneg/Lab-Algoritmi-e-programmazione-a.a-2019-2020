#include <stdio.h>

#define N 8

void stampaCodifica (void *p, int size, int bigEndian);
int isBigEndian(void);
void toBin(int bin [N], int dec);

int main() {
    double a;
    float af;
    double ad;
    long double ald;
    int bigEndian;

    printf("Inserire un numero: ");
    scanf("%lf", &a);

    af = (float)a;
    ad = (double)a;
    ald = (long)a;

    bigEndian = isBigEndian();

    stampaCodifica((void*)&af, sizeof(af), bigEndian);
    stampaCodifica((void*)&ad, sizeof(ad), bigEndian);
    stampaCodifica((void*)&ald, sizeof(ald), bigEndian);

    return 0;
}


int isBigEndian(){
    int a =256, b = 0;
    unsigned char *c;
    c = (unsigned char*)&a;
    b = (int)*c;
    return b;
}


void stampaCodifica (void *p, int size, int bigEndian) {
    int i, k;
    int byte[8];
    unsigned char a[size];
    unsigned char *b = p;

    printf("%d Byte, %d Bit\n", size, 8*size);

    for (i = 0; i < size; i++) {
        a[i] = *(b + i);
    }

    // Big endian
    if (bigEndian) {
    }
    // Little endian
    else {
        for (i = size - 1; i >= 0; i--) {
            toBin(byte, a[i]);
            for (k = 0; k < 8; k++) {
                printf("%d", byte[k]);
            }
            printf(" ");
        }
        printf("\n");
    }
}


void toBin(int bin [N], int dec){
    int bin0[N] = {0};
    int i, j, k;
    for(i=0; dec>0; i++){
        bin0[i] = dec % 2;
        dec /= 2;
    }
    for(j=0, k=(N-1); j<=(N-1); j++, k--){
        bin[j] = bin0[k];
    }
}