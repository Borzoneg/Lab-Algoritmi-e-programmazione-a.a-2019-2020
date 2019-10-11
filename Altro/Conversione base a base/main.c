#include <stdio.h>
#include <math.h>
void DtoB(int a);
void BtoD(int bin[], int lenght);
void XtoY(int x, int y);

int main() {
    DtoB(45);
    return 0;
}


void DtoB(int a){
    double b = (double)a;
    int i;
    int k = sqrt(b);
    for(i= 0, k--; i<k; i++){

    }
    printf("%d %.2f", k, pow(2, 6));

}


void BtoD(int bin[], int lenght){

}


void XtoY(int x, int y){

}
