#include <stdio.h>
#include <stdlib.h>

int majority( int *a, int N);

int main() {
    int N = 21;
    int a[] = {2, 3, 2, 3, 3, 5, 5,
               3, 3, 3, 3, 3, 5, 4,
               2, 3, 5, 4, 3, 3, 1};
    printf("%d", majority(a, N));
    return 0;
}


int majority(int *a, int N){
    int l = 0, i, k = 0, sx, dx, Nmezzi = N/2, dispari = 0;
    // Gestisco i vettori di lunghezza dispari
    if(N%2 != 0)
        dispari = 1;
    int c[(N/2)+dispari], b[(N/2)];

    // Se sono arrivato ad avere un vettore si lunghezza 1 mi trovo in un caso terminale, il maggioritario di un
    // vettore di lunghezza uno è l'unico elemento quindi lo ritorno
    if(N == 1)
        return a[0];

    // Se il vettore ha lunhgezza maggiore di 1 lo divido
    else{
        // Inizializzo i due vettori
        for(i=0; i<Nmezzi; i++){
            b[i] = a[i];
            c[i] = a[i+Nmezzi];
        }
        // Metto l'elemento che rimane fuori per i vettori di lunghezza dispari
        if(dispari)
            c[(N/2)] = a[N-1];
       // Itero sui due sottovettori sinistro e destro
       sx =  majority(b, N/2);
       dx = majority(c, N/2);
    }
    // Una volta che ho ritornato il maggioritario del vettore di lunghezza 1 controllo, contando quante volte appare,
    // se l'elemento è maggioritario anche nel sottovettore superiore
    // sia per il vettore di sx
    if(sx != -1){
        while(l < N){
            if(sx == a[l])
                k++;
            l++;
        }
        // Se il numero di apparizioni del numero lo rende un maggioritario lo ritorno
        if(k > N/2)
            return sx;
    }
    l=0;
    k=0;
    // che di dx
    if(dx != -1) {
        while (l < N) {
            if (dx == a[l])
                k++;
            l++;
        }
        if(k > (N/2))
            return dx;
    }
    // se non ho elementi maggioritari in un vettore a 2 o più elementi ritorno -1 in modo che i sottovettori superiori
    // non entrino in queste due iterazioni
    return -1;
}
