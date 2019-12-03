#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N 12
#define P 4

// zaffiri, smeraldi, rubini, topazi
typedef struct{
    int codicePietra;
    int n;
}pietra;
int disposizioniConRip(int pos, pietra *val, int *sol, int n, int k, int maxLenght, int *rip, int *bestSol);
pietra *generaDati(int *nPietre);
int checkSolution(int *sol, int lenght);

int main() {
    int i, c;
    int rip[P] = {0};
    int a[P];
    FILE *fp = fopen("e1_easy_test_set.txt", "r");
    int nrig;
    fscanf(fp, "%d", &nrig);
    nrig = 1;
    for(i=0; i<nrig; i++) {
        //fscanf(fp, "%d %d %d %d", &a[0], &a[2], &a[3], &a[1]);
        sscanf("10 10 9 10", "%d %d %d %d",&a[0], &a[2], &a[3], &a[1]);
        pietra *dati = generaDati(a);
        int somma = a[0] + a[1] + a[2] + a[3];
        int sol[somma], bestSol[somma];
        c = disposizioniConRip(0, dati, sol, P, somma, 0, rip, bestSol);
        printf("Lunghezza: %d\n", c);
    }
//    printf("\nTempo speso: %f[s]", (double)(end - begin) / CLOCKS_PER_SEC);
    return 0;
}


int disposizioniConRip(int pos, pietra *val, int *sol, int n, int k, int maxLenght, int *rip, int *bestSol){
    int i, pruning=1;
    if (pos>0 && (pruning = checkSolution(sol, pos))) {
        if(pos>maxLenght){
            maxLenght = pos;
            for(i=0; i<pos; i++)
                bestSol[i] = sol[i];
        }
    }
    if(!pruning)
        return maxLenght;
    if(pos>=k)
        return maxLenght;
    for(i=0; i<n; i++){
        if(rip[i]+1 <= val[i].n){
            sol[pos] = val[i].codicePietra;
            rip[i]++;
            maxLenght = disposizioniConRip(pos + 1, val, sol, n, k, maxLenght, rip, bestSol);
            rip[i]--;
        }
        i++;
        if(rip[i]+1 <= val[i].n){
            sol[pos] = val[i].codicePietra;
            rip[i]++;
            maxLenght = disposizioniConRip(pos + 1, val, sol, n, k, maxLenght, rip, bestSol);
            rip[i]--;
        }
        i++;
        if(rip[i]+1 <= val[i].n){
            sol[pos] = val[i].codicePietra;
            rip[i]++;
            maxLenght = disposizioniConRip(pos + 1, val, sol, n, k, maxLenght, rip, bestSol);
            rip[i]--;
        }
        i++;
        if(rip[i]+1 <= val[i].n){
            sol[pos] = val[i].codicePietra;
            rip[i]++;
            maxLenght = disposizioniConRip(pos + 1, val, sol, n, k, maxLenght, rip, bestSol);
            rip[i]--;
        }
    }
    return maxLenght;
}


int checkSolution(int *sol, int lenght){
    int i;
    for(i=0; i<lenght-1; i++){
        switch (sol[i]){
            case 0:
                if(sol[i+1] == 1 || sol[i+1] == 3)
                    return 0;
                break;
            case 1:
                if(sol[i+1] == 0 || sol[i+1] == 2)
                    return 0;
                break;
            case 2:
                if(sol[i+1] == 0 || sol[i+1] == 2)
                    return 0;
                break;
            case 3:
                if(sol[i+1] == 1 || sol[i+1] == 3)
                    return 0;
                break;
        }
    }
    return 1;
}


pietra *generaDati(int *nPietre){
    int i;
    pietra *dati = malloc(sizeof(pietra)*4);
    for(i=0; i<P; i++){
        dati[i].codicePietra = i;
        dati[i].n = nPietre[i];
    }
    return dati;
}