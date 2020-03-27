#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int inizio;
    int fine;
}att;

int combSempl(int pos, att *val, att *sol, int start, int n, int durataMax);
void attSel(int N, att*v);
int checkSol(att*sol, int pos);

int main() {
    att* v;
    int i, nrig;
    FILE *fp = fopen("att.txt", "r");
    fscanf(fp, "%d", &nrig);
    v = malloc(sizeof(att)*nrig);
    for(i=0; i<nrig; i++)
        fscanf(fp, "%d %d", &v[i].inizio, &v[i].fine);
    attSel(nrig, v);
    return 0;
}


void attSel(int N, att*v){
    int i, maxDur = 0;
    printf("Durata massima: %d\n", maxDur);
    att* sol = malloc(sizeof(att)*N);
    maxDur = combSempl(0, v, sol, 0, N, 0);
    printf("Durata massima: %d", maxDur);
}


int combSempl(int pos, att *val, att *sol, int start, int n, int durataMax){
    int i, durataLoc, pruning;
    if(pos > 0 && (pruning = checkSol(sol, pos))){
        for(i=0, durataLoc=0; i<pos; i++){
            //printf("Attivita che inizia alle %d e finisce alle %d\n", sol[i].inizio, sol[i].fine);
            durataLoc += (sol[i].fine - sol[i].inizio);
        }
        //printf("Durata locale: %d\n\n", durataLoc);
        if(durataLoc>durataMax){
            durataMax = durataLoc;
        }
    }
    if(pos>=n)
        return durataMax;
    for(i=start; i<n; i++){
            sol[pos] = val[i];
            durataMax = combSempl(pos + 1, val, sol, i + 1, n, durataMax);
        }
    return durataMax;
}


int checkSol(att*sol, int pos){
    int i, j;
    for(i=0; i<pos; i++){
        for(j=0; j<pos; j++){
            if(i!=j)
                if(sol[i].inizio < sol[j].fine)
                    if(sol[i].fine > sol[j].inizio)
                        return 0;
        }
    }
    return 1;
}