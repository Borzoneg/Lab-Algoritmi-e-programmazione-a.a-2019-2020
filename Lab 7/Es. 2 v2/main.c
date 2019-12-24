#include <stdio.h>
#include <stdlib.h>
#define P 4

// zaffiri, rubino, topazio, smeraldo
typedef struct{
    int nPietre;
    int valore;
    char nome;
}pietra;
int disposizioniConRip(int pos, pietra *val, pietra *sol, int n, int k, int *maxLenght, int *rip, pietra *bestSol, int maxRip, int price, int ripCons);
pietra *generaDati(int *nPietre);
int checkSolution(pietra *sol, int lenght, pietra* val);

int main() {
    int i, c, maxRip, somma = 0, maxLenght;
    int rip[P*2] = {0};
    int a[P*2];
    sscanf("6 5 7 2 2 15 2 21 5", "%d %d %d %d %d %d %d %d %d",&a[0], &a[1], &a[2], &a[3], &a[4],
           &a[5], &a[6], &a[7], &maxRip);
    pietra *dati = generaDati(a);
    for(i=0; i<(P); i++)
        somma +=a[i];
    pietra sol[somma], bestSol[somma];
    c = disposizioniConRip(0, dati, sol, P, somma, &maxLenght, rip, bestSol, maxRip, 0, 0);
    printf("Lunghezza: %d\tPrezzo: %d\n", maxLenght, c);
    for(i=0; i<maxLenght; i ++)
        printf("%c ", bestSol[i].nome);
    return 0;
}


int disposizioniConRip(int pos, pietra *val, pietra *sol, int n, int k, int *maxLenght, int *rip, pietra *bestSol, int maxRip, int price, int ripCons){
    int i, j, pruning, locPrice = 0;
    if(pos>0 && (pruning = checkSolution(sol, pos, val)) == 1){
        for(i=0; i<pos; i++)
            locPrice += sol[i].valore;
        if(locPrice > price){
            for(i=0; i<pos; i++)
                bestSol[i] = sol[i];
            price = locPrice;
            *maxLenght = pos;
        }
    }
    if(!pruning)
        return price;
    if(pos >= k)
        return price;
    for(i=0; i<n; i++){
        if(sol[pos-1].nome == val[i].nome) {
            ripCons = 2;
            for(j=pos-1; sol[j].nome == sol[j-1].nome; j--)
                ripCons++;
        }
        if(ripCons > maxRip)
            i++;
        ripCons = 0;
        while(rip[i]+1 > val[i].nPietre)
            i++;
        if(i >= n)
            return price;
        sol[pos] = val[i];
        rip[i]++;
        price = disposizioniConRip(pos + 1, val, sol, n, k, maxLenght, rip, bestSol, maxRip, price, ripCons);
        rip[i]--;
    }
    return price;
}


int disposizioniRip(int pos, int *val, int *sol, int n, int k, int price){
    int i;
    if(pos >= k){
        for(i=0; i<pos; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return price + 1;
    }
    for(i=0; i<n; i++){
        sol[pos] = val[i];
        price = disposizioniRip(pos+1, val, sol, n, k, price);
    }
    return price;
}


int checkSolution(pietra *sol, int lenght, pietra *val){
    int i, nzaffiri=0, nsmeraldi=0;
    if(sol[lenght-1].nome == val[3].nome)
        nsmeraldi++;
    if(sol[lenght-1].nome == val[0].nome)
        nzaffiri++;
    for(i=0; i<lenght-1; i++){
        if(sol[i].nome == val[0].nome){
            nzaffiri++;
            if(sol[i+1].nome == val[2].nome || sol[i+1].nome == val[3].nome)
                return 0;
        }
        if(sol[i].nome == val[1].nome){
            if(sol[i+1].nome == val[0].nome || sol[i+1].nome == val[1].nome)
                return 0;
        }
        if(sol[i].nome == val[2].nome){
            if(sol[i+1].nome == val[2].nome || sol[i + 1].nome == val[3].nome)
                return 0;
        }
        if(sol[i].nome == val[3].nome){
            nsmeraldi++;
            if(sol[i+1].nome == val[0].nome || sol[i+1].nome == val[1].nome)
                return 0;
        }
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

