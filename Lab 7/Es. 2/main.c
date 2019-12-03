#include <stdio.h>
#include <stdlib.h>
#define P 4

// zaffiri, rubino, topazio, smeraldo
typedef struct{
    int nPietre;
    int valore;
    char nome;
}pietra;
int disposizioniConRip(int pos, pietra *val, pietra *sol, int n, int k, int *maxLenght, int *rip, pietra *bestSol, int maxRip, int maxValue);
pietra *generaDati(int *nPietre);
int checkSolution(pietra *sol, int lenght, pietra* val, int maxRip);

int main() {
    int i, c, maxRip, somma = 0, maxLenght;
    int rip[P*2] = {0};
    int a[P*2];
    sscanf("10 7 8 10 17 16 18 17 3", "%d %d %d %d %d %d %d %d %d",&a[0], &a[1], &a[2], &a[3], &a[4],
                &a[5], &a[6], &a[7], &maxRip);
    pietra *dati = generaDati(a);
    for(i=0; i<(P); i++)
        somma +=a[i];
    pietra sol[somma], bestSol[somma];
    c = disposizioniConRip(0, dati, sol, P, somma, &maxLenght, rip, bestSol, maxRip, 0);
    printf("Lunghezza: %d\tPrezzo: %d\n", maxLenght, c);
    for(i=0; i<maxLenght; i ++)
        printf("%c ", bestSol[i].nome);
    return 0;
}


int disposizioniConRip(int pos, pietra *val, pietra *sol, int n, int k, int *maxLenght, int *rip, pietra *bestSol, int maxRip, int maxValue){
    int i, pruning=1, somma;
    if (pos>0 && (pruning = checkSolution(sol, pos, val, maxRip)) == 1) {
        for(i=0, somma=0; i<pos; somma+=sol[i].valore, i++);
        if(somma>maxValue){
            maxValue = somma;
            *maxLenght = pos;
            for(i=0; i<pos;i++)
                bestSol[i] = sol[i];
        }
    }
    if(!pruning)
        return maxValue;
    if(pos>=k)
        return maxValue;
    for(i=0; i<n; i++){
        if(rip[i]+1 <= val[i].nPietre){
            sol[pos] = val[i];
            rip[i]++;
            maxValue = disposizioniConRip(pos + 1, val, sol, n, k, maxLenght, rip, bestSol, maxRip, maxValue);
            rip[i]--;
        }
        i++;
        if(rip[i]+1 <= val[i].nPietre){
            sol[pos] = val[i];
            rip[i]++;
            maxValue = disposizioniConRip(pos + 1, val, sol, n, k, maxLenght, rip, bestSol, maxRip, maxValue);
            rip[i]--;
        }
        i++;
        if(rip[i]+1 <= val[i].nPietre){
            sol[pos] = val[i];
            rip[i]++;
            maxValue = disposizioniConRip(pos + 1, val, sol, n, k, maxLenght, rip, bestSol, maxRip, maxValue);
            rip[i]--;
        }
        i++;
        if(rip[i]+1 <= val[i].nPietre){
            sol[pos] = val[i];
            rip[i]++;
            maxValue = disposizioniConRip(pos + 1, val, sol, n, k, maxLenght, rip, bestSol, maxRip, maxValue);
            rip[i]--;
        }
    }
    return maxValue;
}


int checkSolution(pietra *sol, int lenght, pietra *val, int maxRip){
    int i, nzaffiri=0, nsmeraldi=0, ripCons = 0;
    char lastVal = ' ';
    for(i=0; i<lenght-1; i++){
        if(sol[i].nome == val[0].nome){
            if(lastVal == sol[i].nome)
                ripCons++;
            else{
                lastVal = sol[i].nome;
                ripCons = 1;
            }
            nzaffiri++;
            if(sol[i+1].nome == val[2].nome || sol[i+1].nome == val[3].nome)
                return 0;
        }
        if(sol[i].nome == val[1].nome){
            if(lastVal == sol[i].nome)
                ripCons++;
            else{
                lastVal = sol[i].nome;
                ripCons = 1;
            }
            if(sol[i+1].nome == val[0].nome || sol[i+1].nome == val[1].nome)
                return 0;
        }
        if(sol[i].nome == val[2].nome) {
            if(lastVal == sol[i].nome)
                ripCons++;
            else{
                lastVal = sol[i].nome;
                ripCons = 1;
            }
            if(sol[i+1].nome == val[2].nome || sol[i + 1].nome == val[3].nome)
                return 0;
        }
        if(sol[i].nome == val[3].nome){
            if(lastVal == sol[i].nome)
                ripCons++;
            else{
                lastVal = sol[i].nome;
                ripCons = 1;
            }
            nsmeraldi++;
            if(sol[i+1].nome == val[0].nome || sol[i+1].nome == val[1].nome)
                return 0;
        }
        if(ripCons>maxRip)
            return 0;
    }
    if(nzaffiri>nsmeraldi)
        return 2;
    return 1;
}


pietra *generaDati(int *nPietre){
    int i;
    pietra *dati = malloc(sizeof(pietra)*4);
    for(i=0; i<P; i++){
        dati[i].valore = nPietre[i+4];
        dati[i].nPietre = nPietre[i];
    }
    dati[0].nome = 'z';
    dati[1].nome = 'r';
    dati[2].nome = 't';
    dati[3].nome = 's';
    return dati;
}