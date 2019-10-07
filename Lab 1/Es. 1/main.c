#include <stdio.h>

const int N = 30;
const int n = 20;
const int m = 20;
void trovaDim(char filename[N], int *nc, int *nr);
void leggifile(char filename[N], int matrix[n][m], int nc, int nr);
int trovaCapolista(int matrix[n][m], int nc, int nr, int k);

int main() {
    int matrix [n][m];
    int nc, nr, i;
    FILE *fp = fopen("dizionario", "r");
    trovaDim("campionato" ,&nc, &nr);
    leggifile("campionato", matrix, nc, nr);
    for(i=0; i<nc; i++) {
        printf("%d\n", trovaCapolista(matrix, nc, nr, i));
    }
    return 0;
}


void trovaDim(char filename[N], int *nc, int *nr){
    *nc = 0;
    *nr = 0;
    FILE *fp = fopen(filename,"r");
    char ch;
    while((ch = getc(fp)) != EOF){
        if(ch == ' ' && *nr == 0)
            *nc = *nc + 1;
        if(ch== '\n')
            *nr = *nr + 1;
    }
    *nc = *nc + 1;
    *nr = *nr + 1;
}


void leggifile(char filename[N], int matrix[n][m], int nc, int nr){
    //char filename = "campionato";
    FILE *fp = fopen(filename, "r");
    int i, j;
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }
}


int trovaCapolista(int matrix[n][m], int nc, int nr, int k){
    int i, max=-1, indice, somma;
    if(k == 0){
        for(i=0; i<nr; i++){
            if(matrix[i][k] > max){
                indice = i;
                max = matrix[i][k];
            }
        }
    }
    else{
        for(i=0; i<nr; i++){
            matrix[i][k] += matrix[i][k-1];
            if(matrix[i][k] > max){
                indice = i;
                max = matrix[i][k];
            }
        }
    }
    return indice;
}