#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(char *filename, int *nr, int *nc);
void separa(int **mat, int nr, int nc, int *bianchi, int *neri);

int main() {
    int nc, nr, nBianchi, nNeri;
    int **m = malloc2dR("mat.txt", &nr, &nc);

    if((nc*nr)%2 != 0)
        nBianchi = (nc*nr)/2+1;
    else
        nBianchi = (nc*nr)/2;
    nNeri = (nc*nr)/2;

    int *bianchi = (int*)malloc(sizeof(int) * nBianchi);
    int *neri = (int*)malloc(sizeof(int) * nNeri);

    separa(m, nr, nc, bianchi, neri);

//    for(int i =0; i<nBianchi; i++){
//        printf("%d\t", bianchi[i]);
//    }
//    printf("\n");
//    for(int i =0; i<nNeri; i++){
//        printf("%d\t", neri[i]);
//    }
    return 0;
}


int **malloc2dR(char *filename, int *nr, int *nc){
    FILE *fp = fopen(filename, "r");

    int  i, j, k, a;
    fscanf(fp, "%d %d", nr, nc);


    int ** matrix = malloc(*nr * (sizeof(int*)));
    for(i=0; i<*nr; i++){
        matrix[i] = (int*)malloc(*nc * (sizeof(int)));
        for(j=0; j<*nc; j++) {
            fscanf(fp, "%d", &matrix[i][j]);
        }

    }
    return matrix;
}


void separa(int **mat, int nr, int nc, int *bianchi, int *neri){
    int i, j, b =0, n = 0;
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            if((i%2 != 0) && (j%2 !=0)){
                bianchi[b] = mat[i][j];
            b++;
            }
            else if((i%2 == 0) && (j%2 ==0)){
                bianchi[b] = mat[i][j];
                b++;
            }
            else {
                neri[n] = mat[i][j];
                n++;
            }
        }
    }
}