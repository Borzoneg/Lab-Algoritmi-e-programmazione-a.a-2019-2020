#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int inizio;
    int fine;
    int durata;
}att;

int attInters(att a1, att a2);
int generaSol(att *val, int n, att *sol);
att max(att a1, att a2);

int main() {
    FILE *fp = fopen("att.txt", "r");
    int i, nrig, max;
    fscanf(fp, "%d", &nrig);
    att *dati = malloc(sizeof(att)*nrig);
    att *sol = malloc(sizeof(att)*nrig);
    for(i=0; i<nrig; i++){
        fscanf(fp, "%d %d", &dati[i].inizio, &dati[i].fine);
    }
    for(i=0; i<nrig; i++){
        dati[i].durata = dati[i].fine - dati[i].inizio;
    }
    max = generaSol(dati, nrig, sol);
    printf("Durata max: %d con soluzione:\n",max);
    for(i=0; sol[i].durata != -1; i++)
        printf("%d %d\n", sol[i].inizio, sol[i].fine);
    return 0;
}


int generaSol(att *val, int n, att *sol){
    int i, j, maxLen = 0;
    att maxLoc;
    for(i=0, j=0; i<n; i++, j++){
        maxLoc = val[i];
        // trovo l'attività  a durata massima tra le attività che si intersecano
        while(attInters(val[i], val[i+1])) {
            maxLoc = max(val[i], val[i + 1]);
            i++;
        }
        sol[j] = maxLoc;
        maxLen += sol[j].durata;
    }
    // flag di fine del vettore soluzione
    sol[j].durata = -1;
    return maxLen;
}


int attInters(att a1, att a2){
    if(a1.inizio < a2.fine)
        if(a1.fine > a2.inizio)
            return 1;
    return 0;
}


att max(att a1, att a2){
    if(a1.durata >= a2.durata)
        return a1;
    return a2;
}