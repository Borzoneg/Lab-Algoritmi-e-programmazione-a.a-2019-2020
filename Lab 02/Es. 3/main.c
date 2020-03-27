#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 20
#define L 5
#define P 25
#define O 10

typedef struct{
    char sequenza[L];
    int posizione[O];
    char parolatrov[O][P];
    int nOcc;
}occorrenza;

int leggiSequenze(char filename[N], char sequenze[N][5]);
void trovaParola(char filename[N], char sequenza0[5]);
void trovaParola2(char sequenze[N][L], char filename[N], occorrenza r[N], int nSeq);

int main() {
    int nSeq, i, j;
    char s[N][L];

    nSeq = leggiSequenze("sequenze", s);
    occorrenza r[nSeq];

    for(i=0; i<nSeq; i++){
        strcpy(r[i].sequenza, s[i]);
        r[i].nOcc = 0;
    }

    trovaParola2(s, "testo", r, nSeq);
    /*
   for(i=0; i<nSeq; i++){
       trovaParola("testo", s[i]);
   }*/
    for(i=0; i<nSeq; i++){
        printf("La sequenza %s e' contenuta in\n", r[i].sequenza);
        for(j=0; j<r[i].nOcc; j++){
            printf("'%s', in posizione: %d\n", r[i].parolatrov[j], r[i].posizione[j]);
        }
        printf("\n");
    }
    return 0;
}


int leggiSequenze(char filename[N], char sequenze[N][L]){
    int n, i, j;
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File non trovato");
        return -1;
    }
    fscanf(fp, "%d", &n);
    for(i=0; i<n; i++)
        fscanf(fp, "%s", sequenze[i]);
    // ciclo che mi permette di mettere tutte le sequenze in minuscolo
    for(i=0; i<n; i++){
        for(j=0; j<strlen(sequenze[i]); j++){
            sequenze[i][j] = tolower(sequenze[i][j]);
        }
    }
    fclose(fp);
    return n;
}


void trovaParola(char filename[N], char sequenza0[5]){
    char parola[P];
    int i = 1;
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File non trovato");
        return;
    }
    // finchè trovo una parola da controllare
    while((fscanf(fp, "%s", parola)) == 1){
        // pongo la prima lettera della parola minuscola perchè corrisponda alla sequenza (scritta in minuscolo)
        parola[0] = tolower(parola[0]);
        // se la sequenza è contenuta nella parola che sto esaminando stampo il messaggio
        if((strstr(parola, sequenza0)) != NULL){
            printf("%s e' contenuta in %s (posizione %d)\n", sequenza0, parola, i);
        }
        // gestisco l'eccezione dell'apostrofo
        if((strstr(parola, "\'") != NULL))
            i++;
        i++;
    }
    fclose(fp);
}


void trovaParola2(char sequenze[N][L], char filename[N], occorrenza r[N], int nSeq){
    FILE *fp = fopen(filename, "r");
    char parola[P];
    char *apo;
    int i, indiceParola = 0, apos = 0;
    if(fp == NULL) {
        printf("File non trovato");
        return;
    }
    // ciclo su ogni parola
    while((fscanf(fp, "%s", parola)) == 1){
        // aumento il'indice della parola a cui mi trovo e porto la prima lettera di ogni parola a minuscolo
        indiceParola++;
        parola[0] = tolower(parola[0]);
        // gestisco l'apostrofo
        if((apo = (strstr(parola, "'"))) != NULL){
            *apo = '\0';
            apos = 1;
        }
        // per ogni sequenza nella mia struttura dati
        for(i=0; i<nSeq; i++){
            // comparo la parola con la sequenza contenuta nel vettore di struct, se trovo una corrispondenza
            // e non ne ho trovate già dieci aggiungo i dati nella struct, aggiungo la posizione e la parola a
            // cui ho trovat la corrisponenza e aumento il numero di occorrenze trovate
            if(strstr(parola, r[i].sequenza) != NULL){
                if(r[i].nOcc < 10) {
                    r[i].posizione[r[i].nOcc] = indiceParola;
                    strcpy(r[i].parolatrov[r[i].nOcc], parola);
                    r[i].nOcc++;
                }
            }
        }
        if(apos == 1)
            indiceParola++;
        apos = 0;
    }

    fclose(fp);
}