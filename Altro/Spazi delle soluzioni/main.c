#include <stdio.h>
#include <stdlib.h>
#define N 6

int principioDiMoltiplicazione(int pos, int *val, int n, int *sol, int count);
int disposizioniSemplici(int pos, int n, int k, int *mark, int *sol, int *val, int count);
int permutazioniSemplici(int pos, int n, int *mark, int *sol, int *val, int count);
int combinazioniSemplici(int pos, int n, int k, int start, int *sol, int *val, int count);
int disposizioniRipetute(int pos, int n, int k, int * sol, int *val, int count);
int permutazioniRipetute(int pos, int n, int *mark, int n_dist, int *sol, int *dist_val, int count);
int combinazioniRipetute(int pos, int n, int k, int start, int *sol, int *val, int count);
int powerSet(int pos, int n, int start, int *sol, int *val, int count);

int main() {
    int v[] = {0, 1 ,2, 3, 4, 5};
    int *sol = malloc(sizeof(int)* N);
    int *mark = malloc(sizeof(int)* N);
    for(int i=0; i<N; mark[i++]=0);
    int count;
//    count = principioDiMoltiplicazione(0, v, N, sol, 0);
//    printf("per un totale di %d scelte\n", count);
    count = disposizioniSemplici(0, 4, 2, mark, sol, v, 0);
    printf("per un totale di %d disposizioni\n", count);
    count = permutazioniSemplici(0, 3, mark, sol, v, 0);
    printf("per un totale di %d permutazioni\n", count);
    count = combinazioniSemplici(0, 4, 2, 0, sol, v, 0);
    printf("per un totale di %d combinazioni\n", count);
    count = disposizioniRipetute(0, 2, 4, sol, v, 0);
    printf("per un totale di %d disposizioni ripetute\n", count);
    mark[0] = 1;
    mark[1] = 2;
    int *dist_val = malloc(sizeof(int)*2);
    dist_val[0] = 0;
    dist_val[1] = 1;
    count = permutazioniRipetute(0, 3, mark, 2, sol, dist_val, 0);
    printf("per un totale di %d permutazioni ripetute\n", count);
    count = combinazioniRipetute(0, 6, 2, 0, sol, v, 0);
    printf("per un totale di %d combinazioni ripetute\n", count);
    printf("Powerset:\n");
    count = powerSet(0, 6, 0, sol, v, 0);
    printf("per un totale di %d insiemi\n", count);
    return 0;
}


int principioDiMoltiplicazione(int pos, int *val, int n, int *sol, int count){
    int i;
    if(pos >= n){
        for(i=0; i<n; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count+1;
    }
    for(i=0; i<n; i++){
        sol[pos] = val[i];
        count = principioDiMoltiplicazione(pos+1, val, n, sol, count);
    }
}


int disposizioniSemplici(int pos, int n, int k, int *mark, int *sol, int *val, int count){
    int i;
    if(pos >= k) {
        for(i = 0; i < pos; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count + 1;
    }
    for(i=0; i<n; i++){
        if(!mark[i]){
            sol[pos] = val[i];
            mark[i] = 1;
            count = disposizioniSemplici(pos+1, n, k, mark, sol, val, count);
            mark[i] = 0;
        }
    }
    return count;
}


int permutazioniSemplici(int pos, int n, int *mark, int *sol, int *val, int count){
    int i;
    if(pos >= n) {
        for(i = 0; i < pos; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count + 1;
    }
    for(i=0; i<n; i++){
        if(! mark[i]){
            sol[pos] = val[i];
            mark[i] = 1;
            count = permutazioniSemplici(pos+1, n, mark, sol, val, count);
            mark[i] = 0;
        }
    }
    return count;
}


int combinazioniSemplici(int pos, int n, int k, int start, int *sol, int *val, int count){
    int i;
    if(pos>=k){
        for(i=0; i<k; i++)
            printf("%d", sol[i]);
        printf("\n");
        return count+1;
    }
    for(i=start; i<n; i++){
        sol[pos] = val[i];
        count = combinazioniSemplici(pos+1, n, k, i+1, sol, val, count);
    }
    return count;
}


int disposizioniRipetute(int pos, int n, int k, int * sol, int *val, int count){
    int i;
    for(i=0; i<pos; i++)
        printf("%d ", sol[i]);
    printf("\n");
    if(pos >= k)
        return count +1;
    for(i=0; i<n; i++){
        sol[pos] = val[i];
        count = disposizioniRipetute(pos+1, n, k, sol, val, count);
    }
    return count;
}


int permutazioniRipetute(int pos, int n, int *mark, int n_dist, int *sol, int *dist_val, int count){
    int i;
    if(pos >= n) {
        for(i=0; i<n; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count + 1;
    }
    for(i=0; i<n_dist; i++){
        if(mark[i] > 0){
            mark[i]--;
            sol[pos] = dist_val[i];
            count = permutazioniRipetute(pos+1, n, mark, n_dist, sol, dist_val, count);
            mark[i]++;
        }
    }
    return count;
}


int combinazioniRipetute(int pos, int n, int k, int start, int *sol, int *val, int count){
    int i;
    if(pos >= k) {
        for(i=0; i<k; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return count + 1;
    }
    for(i=start; i<n; i++){
        sol[pos] = val[i];
        count = combinazioniRipetute(pos+1, n, k, start, sol, val, count);
        start++;
    }
    return count;
}


int powerSet(int pos, int n, int start, int *sol, int *val, int count){
    int i;
    if(start>=n) {
        for(i=0; i<pos; i++)
            printf("%d", sol[i]);
        printf("\n");
        return count + 1;
    }
    for(i=start; i<n; i++){
        sol[pos] = val[i];
        count = powerSet(pos+1, n, i+1, sol, val, count);
    }
    count = powerSet(pos, n, n, sol, val, count);
    return count;
}