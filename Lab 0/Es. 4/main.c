#include <stdio.h>
#include <stdlib.h>

const int N = 20;
void leggiFile(FILE *fp, int matrix[N][N], int nc, int nr);
int dimOk(int dim, int nc, int nr);
void stampaSubMatrici(int matrix[N][N], int nc, int nr, int dim);
int main() {
    //char a = '4';
    //int b = atoi(&a);
    char filename[N];
    int matrix[N][N];
    FILE *fp;
    int dim = -1, nc =0, nr = 0;;
    //printf("Inserire nome file: ");
    //scanf("%s", filename);

    fp = fopen("matrice.txt", "r");

    if(nc == 0 && nr == 0){
        fscanf(fp, "%d %d", &nc, &nr);
    }

    //leggiFile(fp, matrix, nc, nr);

    while(dim < 0){
        printf("Quale dev'essere la dimsensione delle sottomatrici?");
        scanf("%d", dim);
    }
    if(dimOk(3, 4, 4)){
        printf("OK");
        stampaSubMatrici(matrix, nc, nr, dim);
    }

    return 0;
}

void leggiFile(FILE *fp, int matrix[N][N], int nc, int nr){
    for(int i=0; i<nr; i++){
        for(int j=0; j<nc; j++){
            fscanf(fp,"%d", &matrix[i][j]);
        }
    }
}

int dimOK(int dim, int nc, int nr){
    if(dim > 0 && dim < (nc +1) && dim < (nr+1))
        return 1;
    else
        return 0;
}

void stampaSubMatrici(int matrix[N][N], int nc, int nr, int dim){
}