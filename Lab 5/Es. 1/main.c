#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 255

// struct definita per ogni amico, in cui metto un intero che è il numero di canzoni dell'amico e un vettore di stringhe
// per le canzoni
typedef struct{
    int nBrani;
    char **canzoni;
}amico;

amico *leggiFile(char *filename, int *nA);
int creaPLaylist(int pos, amico* lista, char **sol, int nAmici, int count);

int main() {
    int nAmici, i, j, count = 0;
    amico *lista;

    lista = leggiFile("brani.txt", &nAmici);

    char** sol= malloc(sizeof(char*)*nAmici);
    for(i=0; i<nAmici; i++){
        sol[i] = malloc(sizeof(char)*N);
    }

    count = creaPLaylist(0, lista, sol, nAmici, count);
    printf("\nEsistono %d playlist per il file inserito\n", count);

    for(i=0; i<nAmici; i++){
        for(j=0; j < lista[i].nBrani; j++)
            free(lista[i].canzoni[j]);
    }
    free(lista);
    return 0;
}


amico *leggiFile(char *filename, int *nA){
    int nBrani, i, j;
    FILE *fp = fopen(filename, "r");
    if(fp==NULL){
        printf("File non trovato");
        exit(1);
    }
    fscanf(fp, "%d", nA);
    // alloco spazio per creare un vettore di struct amico che sarà lungo tanto quanto il numero di amici
    amico *dati = malloc(sizeof(amico) * (*nA));
    for(i=0; i < *nA; i++){
        fscanf(fp, "%d", &nBrani);
        dati[i].nBrani = nBrani;
        // per ogni amico, alloco tanti puntatori a char per il numero di brani
        dati[i].canzoni = malloc(sizeof(char*) * nBrani);
        for(j=0; j<nBrani; j++) {
            // per ogni rano alloco un numero di char per il numero massimo di caratteri
            dati[i].canzoni[j] = malloc(sizeof(char)*N);
            fscanf(fp, "%s", dati[i].canzoni[j]);
        }
    }
	fclose(fp);
    return dati;
}

// utilizzo il codice del principio di moltiplicazione per visitare ogni soluzione adattando il codice al caso dei brani
int creaPLaylist(int pos, amico *lista, char **sol, int nAmici, int count){
    int i;
    if(pos >= nAmici){
        printf("\nInizio playlist %d\n\n", count+1);
        for(i=0; i<nAmici; i++)
            printf("%s\n",sol[i]);
        return count+1;
    }
    for(i=0; i<lista[pos].nBrani; i++){
        sol[pos] = lista[pos].canzoni[i];
        count = creaPLaylist(pos+1, lista, sol, nAmici, count);
        }
    return count;
}
