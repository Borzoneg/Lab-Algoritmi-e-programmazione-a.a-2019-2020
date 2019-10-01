#include <stdio.h>

int findLenght(int a[10]) {
    int i = 0;
    int lenght = 0;
    int maxlenght;
    while (i < 10) {
        //printf("%d", a[i]);
        if (a[i] != 0) {
            lenght++;
            maxlenght = lenght;
        }
        else
            lenght = 0;
        i++;
    }
    return maxlenght;
}

void printsV(int a[10], int lenght){
    int i = 0;
    int c = 0;
    while(i < 10){

        if (a[i] != 0) {
            c++;
            if(c==lenght)
                printf("%d %d %d\n", a[i-2], a[i-1], a[i]);
        }
        else
            c = 0;
        i++;
    }
}

int a [10] = {1, 3, 4, 0, 1, 0, 9, 4, 2, 0};
int main() {
    int b = findLenght(a);
    //printf("%d", b);
    printsV(a, b);
    return 0;
}
