#include <stdio.h>

const int N = 20;

//void bubbleSort(int v[N]);
void insertionSort(int v[N], int lenght);
void selectionSort(int v[N], int lenght);
void shellSort(int v[N], int lenght);

int main() {
    int b[] = {0, 4, 3, 7, 5, 4, 3, 22, 65};
    //selectionSort(b, 9);
    //insertionSort(b, 9);
    shellSort(b, 9);
    return 0;
}


void insertionSort(int v[N], int lenght){
    printf("\nInsertion sort:\n");
    int i, j, temp, scambi=0, iter=0, iterint=0;
    for(i=1; i<lenght; i++){
        temp = v[i];
        for(j=i-1; j>=0 && temp < v[j]; j--){
            v[j+1] = v[j];
            scambi++;
            iterint++;
        }
        printf("Iterazioni del ciclo interno: %d\n", iterint);
        iter += iterint;
        iterint = 0;
        v[j+1] = temp;
    }
    iter += i;
    printf("Iterazioni del ciclo Esterno: %d\n", i);
    printf("Numero di scambi: %d\n", scambi);
    printf("Iterazioni totali: %d\n", iter);
}


void selectionSort(int v[N], int lenght){
    printf("\nSelection sort:\n");
    int i, j, scambi=0, temp, indice, iter=0, iterint=0;
    for(i=0; i<lenght; i++){
        indice = i;
        for(j=i+1; j<lenght; j++){
            iterint++;
            if(v[j] < v[indice]){
                indice = j;
            }
        }

        printf("Iterazioni del ciclo interno: %d\n", iterint);
        iter += iterint;
        iterint=0;

        if(indice != i) {
            scambi++;
            temp = v[i];
            v[i] = v[indice];
            v[indice] = temp;
        }
    }
    // iter+=i;
    printf("Iterazioni del ciclo Esterno: %d\n", i);
    printf("Numero di scambi: %d\n", scambi);
    printf("Iterazioni totali: %d\n", iter);

}


void shellSort(int v[N], int lenght){
    printf("\nShellsort:\n");
    int i, j, h, temp, scambi=0, iter=0, iterint=0;
    for(i=0+h; i<lenght; i++){
        temp = v[i];
        for(j=i+h; j<lenght && temp < v[j]; j+=h){
            v[j+h] = v[j];

            scambi++;
            iterint++;
        }
        printf("Iterazioni del ciclo interno: %d\n", iterint);
        iter += iterint;
        iterint = 0;
        v[j+1] = temp;
    }
    iter += i;
    printf("Iterazioni del ciclo Esterno: %d\n", i);
    printf("Numero di scambi: %d\n", scambi);
    printf("Iterazioni totali: %d\n", iter);
}
