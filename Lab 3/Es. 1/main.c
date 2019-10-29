#include <stdio.h>

#define N 20
#define MAXR 50

void leggiMatrice(char filename[N], int maxr, int m[maxr][maxr], int *nr, int *nc);
int riconosciRegione(int m[MAXR][MAXR], int nr, int nc, int r,int c,int *b,int *h, int risultati    [15]);
void ricercaMax(int risultati[15],int i, int j, int area, int base, int alte);

int main() {
    int nc, nr, i, j, base, altezza;
    int M[MAXR][MAXR];
    int r[15] = {0};

    leggiMatrice("sorgente", MAXR, M, &nr, &nc);

    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            if(riconosciRegione(M, nr, nc, i, j, &base, &altezza, r))
                printf("Trovato rettangolo in %d %d, di base: %d e altezza: %d\n", i, j, base, altezza);
            else
                printf("In %d %d non vi e' l'inizio di un rettangolo\n", i, j);
        }

        printf("Max Base: %d,%d, base = %d, altezza = %d, Area = %d\n"
               "Max Area: %d,%d, base = %d, altezza = %d, Area = %d\n"
               "Max Altezza: %d,%d, base = %d, altezza = %d, Area = %d\n",
               r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8], r[9], r[10], r[11], r[12], r[13], r[14]);

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
	fclose(fp);
}


int riconosciRegione( int m[MAXR][MAXR],int nr,int nc, int r,int c,int *b,int *h, int risultati[15]){
    int i, j, finito, area;
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
                    }
                    else
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
                // pongo  a 0 le celle comprese nel rettangolo per non ricontrollarle
                for(i=r+1; i<r+*b; i++){
                    for(j=c+1; j<c+*h; j++)
                        m[i][j] = 0;

                }
                area = (*b)*(*h);
                ricercaMax(risultati, r, c, area, *b, *h);
                return 1;
            }
    else
        return 0;
}


void ricercaMax(int risultati[15], int i, int j, int area, int base, int alte){
    if (base > risultati[2]) {
        risultati[0] = i;
        risultati[1] = j;
        risultati[2] = base;
        risultati[3] = alte;
        risultati[4] = area;

    }
    if (area > risultati[9]) {
        risultati[5] = i;
        risultati[6] = j;
        risultati[7] = base;
        risultati[8] = alte;
        risultati[9] = area;

    }
    if (alte > risultati[13]) {
        risultati[10] = i;
        risultati[11] = j;
        risultati[12] = base;
        risultati[13] = alte;
        risultati[14] = area;
    }
}