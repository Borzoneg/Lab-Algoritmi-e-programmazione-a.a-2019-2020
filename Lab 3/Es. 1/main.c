#include <stdio.h>
#define N 20
#define MAXR 50

void leggiMatrice(char filename[N], int maxr, int m[maxr][maxr], int *nr, int *nc);
int riconosciRegione(int m[MAXR][MAXR], int nr, int nc, int r,int c,int *b,int *h);

int main() {
    int nc, nr, i, j, base, altezza;
    int M[MAXR][MAXR];
    leggiMatrice("sorgente", MAXR, M, &nr, &nc);
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            if(riconosciRegione(M, nr, nc, i, j, &base, &altezza))
                printf("Trovato rettangolo in %d %d, di base: %d e altezza: %d\n", i, j, base, altezza);
            else
                printf("In %d %d non vi e' l'inizio di un rettangolo\n", i, j);
        }
    }
    return 0;
}


void leggiMatrice(char filename[N], int maxr, int m[maxr][maxr], int *nr, int *nc){
    FILE *fp = fopen(filename, "r");
    int i, j;
    fscanf(fp, "%d %d", nr, nc);
    for(i=0; i< *nr; i++){
        for(j=0;j< *nc; j++){
            fscanf(fp, "%d", &m[i][j]);
        }
    }
}


int riconosciRegione( int m[MAXR][MAXR],int nr,int nc, int r,int c,int *b,int *h){
    int i, j, finito;
    *b = 0;
    *h = 0;
    if (m[r][c] == 1) {
                *b = *b + 1;
                *h = *h + 1;
                // controllo orizzontalmente di quanto va avanti il rettangolo
                for (i = c + 1, finito = 0; !finito; i++) {
                    if (m[r][i] == 1) {
                        *b = *b + 1;
                        // pongo a 0 la cella di modo da non controllarla di nuovo prendendola come punto di partenza
                        m[r][i] = 0;
                    } else
                        // se c'è uno zero il rettangolo finisce orizzontalmente, esco dal ciclo
                        finito = 1;
                }
                // faccio la stessa cosa ma verticalmente
                for (finito = 0, i = r + 1; !finito; i++) {
                    if (m[i][c] == 1) {
                        *h = *h + 1;
                        m[i][c] = 0;
                    } else
                        finito = 1;
                }
                for(i=r+1; i<r+*b; i++){
                    for(j=c+1; j<c+*h; j++)
                        m[i][j] = 0;

                }
                return 1;
            }
    else
        return 0;
}