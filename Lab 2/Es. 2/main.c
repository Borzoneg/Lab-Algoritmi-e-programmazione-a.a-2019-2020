#include <stdio.h>

const int N = 30;
const int R = 1000;

typedef struct {
    char codiceTratta[N];
    char partenza[N];
    char destinazione[N];
    char data[N];
    char oraPart[N];
    char oraArr[N];
    int ritardo;
} rigaLog;

int leggiFile(char filename[N], rigaLog dati[R]);
// int leggicomando();

int main() {

    printf("Hello, World!\n");
    return 0;
}