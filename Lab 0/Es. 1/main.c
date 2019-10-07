#include <stdio.h>

const int N = 30;
int findLenght(int a[N], int n) {
    int i = 0;
    int lenght = 0;
    int maxlenght = 0;
    while (i < n) {
        //printf("%d", a[i]);
        if (a[i] != 0) {
            lenght++;
            if(lenght > maxlenght)
                maxlenght = lenght;
        }
        else
            lenght = 0;
        i++;
    }
    return maxlenght;
}

void printsV(int a[N], int lenght){
    int i = 0;
    int index;
    int c = 0;
    while(i < 10){
        if (a[i] != 0) {
            c++;
            if(c==lenght) {
                for(int j=lenght -1 ; j>=0; j--){
                    //devo stampre a partire dalla i a cui sono arrivato e poi i successivi
                    //lenght numeri
                    index = i - j;
                    printf("%d", a[index]);
                }
                printf("\n");
            }
            }
        else
            c = 0;
        i++;
    }
}

int main() {
    int a [N];
    int l = 0, temp;
    for(int i = 0; i<N; i++){
        printf("inserire elemento %d (inserire -1 per terminare)", i);
        scanf("%d", &temp);
        if(temp == -1)
            break;
        a[i] = temp;
        l++;
    }
    int b = findLenght(a, l);
    //printf("%d", b);
    printsV(a, b);
    return 0;
}
