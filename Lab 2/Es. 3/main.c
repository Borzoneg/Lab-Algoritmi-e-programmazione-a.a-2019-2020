#include <stdio.h>
#include <string.h>
#include <ctype.h>
const int N = 20;
const int L = 5;
const int P = 25;

int leggiSequenze(char filename[N], char sequenze[N][5]);
void trovaParola(char filename[N], char sequenza[5]);

int main() {
    int nSeq, i;
    char s[N][L];
    nSeq = leggiSequenze("sequenze", s);
    for(i=0; i<nSeq; i++){
        trovaParola("testo", s[i]);
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
    fclose(fp);
    // ciclo che mi permette di mettere tutte le sequenze in minuscolo
    for(i=0; i<n; i++){
        for(j=0; j<strlen(sequenze[i]); j++){
            sequenze[i][j] = tolower(sequenze[i][j]);
        }
    }
    return n;
}


void trovaParola(char filename[N], char sequenza[5]){
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
        if((strstr(parola, sequenza)) != NULL){
            printf("%s e' contenuta in %s (posizione %d)\n", sequenza, parola, i);
        }
        // gestisco l'eccezione dell'apostrofo
        if((strstr(parola, "\'") != NULL))
            i++;
        i++;
    }
    fclose(fp);
}
