#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 255

typedef struct{
    int nBrani;
    char **canzoni;
}amico;

amico *leggiFile(char *filename, int *nA);
int trovaTotCanzoni(int amici, int nCanzoni[amici]);
int creaPLaylist(int pos, amico* lista, char **sol, int nAmici, int start, int count);

int main() {
    int nAmici, i, j;
    amico *r;

    r = leggiFile("brani.txt", &nAmici);

    char** sol= malloc(sizeof(char*)*nAmici);
    for(i=0; i<nAmici; i++){
        sol[i] = malloc(sizeof(char)*N);
    }
//
//    for(i=0; i<nAmici; i++){
//        printf("%d", r[i].nBrani);
//        for(j=0; j<r[i].nBrani; j++)
//            printf("\n%s", r[i].canzoni[j]);
//        printf("\n");}
    creaPLaylist(0, r, sol, nAmici, 0, 0);
    return 0;
}

amico *leggiFile(char *filename, int *nA){
    int nBrani, i, j;
    FILE *fp = fopen(filename, "r");
    if(fp==NULL)
        exit(2);
    fscanf(fp, "%d", nA);
    amico *dati = malloc(sizeof(amico) * (*nA));
    for(i=0; i < *nA; i++){
        fscanf(fp, "%d", &nBrani);
        dati[i].nBrani = nBrani;
        dati[i].canzoni = malloc(sizeof(char*) * nBrani);
        for(j=0; j<nBrani; j++) {
            dati[i].canzoni[j] = malloc(sizeof(char)*N);
            fscanf(fp, "%s", dati[i].canzoni[j]);
        }
    }
    return dati;
}
//
//
//int trovaTotCanzoni(int amici, int nCanzoni[amici]){
//    int i, somma = 0;
//    for(i=0; i<amici; i++)
//        somma +=nCanzoni[i];
//    return somma;
//}
//

int creaPLaylist(int pos, amico *lista, char *sol[N], int nAmici, int start, int count){
    int i;
    if(pos >= nAmici){
//        printf("Inizio playlist %d\n\n", count);
//        for(i=0; i<nAmici; i++)
//            printf("%s\n",sol[i]);
//        printf("Fine playlist\n\n");
        return count+1;
    }
    for(i=start; i<lista[pos].nBrani; i++){
        sol[pos] = lista[pos].canzoni[i];
        printf("Pos: %d\tI: %d\tCanzone: %s\tnBrani: %d\n", pos, i, sol[pos], lista[pos].nBrani);
        creaPLaylist(++pos, lista, sol, nAmici, i, count);
    }
    return count;
}