#include <stdio.h>
// Individuazione di regioni
const int N = 20;
const int NC = 50;
const int NR = 50;

void leggiFile(char filename[N], int matrix[NC][NR], int *nc, int *nr);
void trovaMassimi(int matrix[NC][NR], int nc, int nr, int risultati[15]);

int main() {
    int matrix[NC][NR];
    char filename[N];
    int nc, nr, i;
    int r[15];

    printf("Inserisci nome file: ");
    scanf("%s", filename);

    leggiFile("sorgente", matrix, &nc, &nr);

    trovaMassimi(matrix, nc, nr, r);

    printf("Max Base: %d,%d, base = %d, altezza = %d, Area = %d\n"
           "Max Area: %d,%d, base = %d, altezza = %d, Area = %d\n"
           "Max Altezza: %d,%d, base = %d, altezza = %d, Area = %d\n",
           r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8], r[9], r[10], r[11], r[12], r[13], r[14]);

    return 0;
}

void trovaMassimi(int matrix[NC][NR], int nc, int nr, int risultati[15]) {
    int i, j, k, q, base = 0, area = 0, alte = 0, finito;

    for (i = 0; i < 15; i++)
        risultati[i] = 0;
    // i due cicli controllano cella per cella
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            // trovo un punto d'inizio
            if (matrix[i][j] == 1) {
                base++;
                alte++;
                // controllo orizzontalmente di quanto va avanti il rettangolo
                for (k = j+1, finito = 0; !finito; k++) {
                    if (matrix[i][k] == 1) {
                        base++;
                        // pongo a 0 la cella di modo da non controllarla di nuovo prendendola come punto di partenza
                        matrix[i][k] = 0;
                    } else
                        // se c'è uno zero il rettangoolo finisce orizzontalmente, esco dal ciclo
                        finito = 1;
                }
                // faccio la stessa cosa ma verticalmente
                for (finito = 0, k = i+1; !finito; k++) {
                    if (matrix[k][j] == 1) {
                        alte++;
                        matrix[k][j] = 0;
                    } else
                        finito = 1;
                }

                // pongo a zero anche le celle del rettangolo che non fanno parte di base e altezza
                for(k=i+1; k<i+alte; k++){
                    for(q=j+1; q<j+base; q++)
                        matrix[k][q] = 0;
                }
                area = base * alte;

                // tre ricerche del massimo
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
                area = 0;
                base = 0;
                alte = 0;
            }
        }
    }
}


void leggiFile(char filename[N], int matrix[NC][NR], int *nc, int *nr) {
    int i, j;
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d %d", nr, nc);
    for (i = 0; i < *nr; i++) {
        for (j = 0; j < *nc; j++) {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }
    fclose(fp);
}