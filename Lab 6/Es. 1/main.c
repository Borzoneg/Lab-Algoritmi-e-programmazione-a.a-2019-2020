#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int src;
    int dest;
}ramo;

ramo* leggiFile(char *filename, int *nNodi, int *nRami);
int checkSolution(int pos, ramo* listaRami, int nRami, int *sol);
int powerSet(int pos, int *sol, int k, int start, int count, ramo* listaRami, int nRami);

int main() {
    int nNodi, nRami, count;
    ramo *listaRami = leggiFile("grafo", &nNodi, &nRami);
    int *soluzione = malloc(sizeof(ramo) * nNodi);

    count = powerSet(0, soluzione, nNodi, 0, 0, listaRami, nRami);
    printf("Ci sono %d vertex cover del grafo", count);
    return 0;
}


ramo* leggiFile(char *filename, int *nNodi, int *nRami){
    int i;
    ramo *listaRami;
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d %d", nNodi, nRami);
    listaRami = malloc(sizeof(ramo*) * (*nRami));
    for(i=0; i < *nRami; i++){
        fscanf(fp, "%d %d", &listaRami[i].src, &listaRami[i].dest);
    }
    return listaRami;
}


int checkSolution(int pos, ramo* listaRami, int nRami, int *sol){
    int i, j, ramiCov = 0;
    int check[nRami];
    for(i=0; i<nRami; i++)
        check[i] = 0;

    for(i=0; i<pos; i++){
        for(j=0; j<nRami; j++){
            if(sol[i] == listaRami[j].dest && !check[j]){
                    ramiCov++;
                    check[j] = 1;
            }
            if(sol[i] == listaRami[j].src && !check[j]){
                ramiCov++;
                check[j] = 1;
            }
        }
    }
    if(ramiCov >= nRami)
        return 1;
    return 0;
}


int powerSet(int pos, int *sol, int k, int start, int count, ramo* listaRami, int nRami){
    int i;
    if(start>=k) {
        if(checkSolution(pos, listaRami, nRami, sol)) {
            for (i = 0; i < pos; i++)
                printf("%d\t", sol[i]);
            printf("\nFine insieme %d\n\n", count + 1);
            return count + 1;
        }
        return count;
    }

    for(i=start; i<k; i++){
        sol[pos] = i;
        count = powerSet(pos+1, sol, k, i+1, count, listaRami, nRami);
    }
    count = powerSet(pos, sol, k, k, count, listaRami, nRami);
    return count;
}