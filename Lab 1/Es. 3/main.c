#include <stdio.h>

const int NC = 30;
const int NR = 30;
const int N = 20;

void ruota(int m[NC][NR], int nc, int nr, int index, int P, int dir, int vers);
void leggiFile(char filename[N], int m[NC][NR], int *nc, int *nr);

int main() {
    char filename[N];
    int matrix[NC][NR];
    int nc, nr, passi, verso, dir, indice;
    printf("Scrivi il nome del file: ");
    scanf("%s", filename);
    leggiFile(filename, matrix, &nc, &nr);
    printf("Scrivere che tipo di rotazione si vuole effettuare:\n"
           "Scrivere in ordine indice, passi, direzione(0:orizzontale, 1: verticale) e "
           "verso(0: dx, su, 1: sx, giù");
    scanf("%d %d %d %d", &indice, &passi, & dir, &verso);
    ruota(matrix, nc, nr, 0, 1, 1, 1);
    return 0;
}

void ruota(int m[NC][NR], int nc, int nr, int index, int P, int dir, int vers){
    int temp1, temp2, i;
    // dir: {0: orizzontale; 1: verticale}
    // vers: {0: dx, su; 1: sx, giù}
    // orizzontale
    if(dir == 0) {
        while (P != 0) {
            temp1 = m[index][0];
            for (i = 0; i < nc; i++) {
                if (i == nc - 1)
                    // gestisco lo sforamento oltre il limite del vettore dello spostamento verso dx
                    if(vers == 1)
                        m[index][0] = temp1;
                    // gestisco lo sforamento pre 0 dello spostamento verso sx
                    else
                        m[index][i] = temp1;
                // spostamento verso dx
                else if(vers == 1) {
                    temp2 = m[index][i + 1];
                    m[index][i + 1] = temp1;
                    temp1 = temp2;
                }
                // spostamento verso sx
                else {
                    m[index][i] = m[index][i + 1];
                }
            }
            P--;
        }
    }

    else if(dir == 1){
        while(P != 0){
            temp1 = m[index][0];
            for (i = 0; i < nr; i++) {
                if (i == nr - 1)
                    // gestisco lo sforamento oltre il limite del vettore dello spostamento verso dx
                    if(vers == 1)
                        m[0][index] = temp1;
                        // gestisco lo sforamento pre 0 dello spostamento verso sx
                    else
                        m[i][index] = temp1;
                    // spostamento verso dx
                else if(vers == 1) {
                    temp2 = m[i+1][index];
                    m[i+1][index] = temp1;
                    temp1 = temp2;
                }
                    // spostamento verso sx
                else {
                    m[i][index] = m[i+1][index];
                }
            }
            P--;
            }
        }
    }


void leggiFile(char filename[N], int m[NC][NR], int *nc, int *nr){
    int i, j;
    FILE *fp = fopen(filename, "r");
    fscanf(fp,"%d %d", nc, nr);
    for(i=0; i<*nr; i++){
        for(j=0; j<*nc; j++){
            fscanf(fp, "%d", &m[i][j]);
        }
    }
}