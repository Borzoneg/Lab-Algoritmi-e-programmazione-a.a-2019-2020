#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define N 30

typedef  struct {
    int giorno;
    int mese;
    int anno;
}data;

typedef  struct {
    int ore;
    int min;
}orario;

typedef struct {
    char codiceTratta[N];
    char partenza[N];
    char destinazione[N];
    data data;
    orario oraPart;
    orario oraArr;
    int ritardo;
} rigaLog;

typedef enum{
    stampa, Odata, Otratta, Opartenza, Ocapolinea, Rpartenza, Acquisizione,fine
}menu;

rigaLog* leggiFile(char *filename, int *nr);
int leggicomando(char *comando);
void stampaRigaLog(rigaLog dati);
void stampaLog(int nr, rigaLog **log);
void ordinaPerDate(int nr, rigaLog *dati, rigaLog **ordinato);
void ordinaPerPartenza(int nr, rigaLog *dati, rigaLog **ordinato);
void ordinaPerTratta(int nr, rigaLog *dati, rigaLog **ordinato);
void ordinaPerCapolinea(int nr, rigaLog *dati, rigaLog **ordinato);
void ricercaPartenza(int nr, rigaLog *dati, char *partenza);
int ricercaDicotomica(int l, int r, rigaLog **ordinato, char *partenza);
void bubbleSortStr(int nr, char **dati, rigaLog **ordinato);
rigaLog** inizializzaPuntatore(int nr, rigaLog dati[nr]);
void fromDatetoString(data daConvD, orario daConvH, char *converted);

int main() {

    rigaLog **ordAtt;
    rigaLog **ordPartenza;

    menu scelta;
    char *comando = malloc(sizeof(char)*N);
    char *partstr = malloc(sizeof(char)*N);

    int continua = 1, nr, ordinatoPart = 0;

    rigaLog *r = leggiFile("corse.txt", &nr);

    ordAtt = inizializzaPuntatore(nr, r);
    ordPartenza = inizializzaPuntatore(nr, r);

    while(continua){
        printf("Inserisci comando:\n"
               "Stampa: per stampare il log per intero\n"
               "Odata: per odinare per data il database\n"
               "Otratta: per odinare per tratta il database\n"
               "Opartenza: per odinare per partenza il database\n"
               "Odestinazione: per ordinare per destinazione il database\n"
               "Rpartenza: per ricercare una una tratta per stazione di partenza\n"
               "Acquisizione: per importare un nuovo file\n"
               "fine: per uscire\n");

        scanf("%s", comando);
        scelta = leggicomando(comando);

        switch (scelta) {
            case stampa:
                stampaLog(nr, ordAtt);
                break;
            case Odata:
                ordinaPerDate(nr, r, ordAtt);
                break;
            case Otratta:
                ordinaPerTratta(nr, r, ordAtt);
                break;
            case Opartenza:
                ordinatoPart = 1;
                ordinaPerPartenza(nr, r, ordPartenza);
                ordAtt = ordPartenza;
                break;
            case Ocapolinea:
                ordinaPerCapolinea(nr, r, ordAtt);
                break;
            case Rpartenza:
                scanf("%s", partstr);
                if(ordinatoPart)
                    ricercaDicotomica(0, nr, ordPartenza, partstr);
                else
                    ricercaPartenza(nr, r, partstr);
                break;
            case Acquisizione:
                free(r);
                scanf("%s", partstr);
                r = leggiFile(partstr, &nr);
                break;
            case fine:
                free(r);
                free(comando);
                free(partstr);
                free(ordAtt);
                free(ordPartenza);
                printf("Arrivederci!");
                continua = 0;
                break;
            default:
                printf("Comando inserito non riconosciuto, prego riprovare\n");
        }
    }
    return 0;
}


rigaLog* leggiFile(char filename[N], int *nr){
    int i;
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File non trovato\n");
        return 0;
    }
    fscanf(fp, "%d", nr);
    rigaLog *dati = (rigaLog*)malloc(sizeof(rigaLog)*(*nr));
    for(i=0; i<*nr; i++){
        fscanf(fp, "%s %s %s %d-%d-%d %d:%d %d:%d %d",
               dati[i].codiceTratta, dati[i].partenza, dati[i].destinazione,
               &dati[i].data.giorno, &dati[i].data.mese, &dati[i].data.anno,
               &dati[i].oraPart.ore, &dati[i].oraPart.min, &dati[i].oraArr.ore, &dati[i].oraArr.min,
               &dati[i].ritardo);
    }
    fclose(fp);
    return dati;
}


int leggicomando(char *comando){
    int i;
    for(i=0; i<strlen(comando); i++){
        comando[i] = tolower(comando[i]);
    }
    if(!(strcmp(comando, "stampa")))
        return 0;
    else if(!(strcmp(comando, "odata")))
        return 1;
    else if(!(strcmp(comando, "otratta")))
        return 2;
    else if(!(strcmp(comando, "opartenza")))
        return 3;
    else if(!(strcmp(comando, "ocapolinea")))
        return 4;
    else if(!(strcmp(comando, "rpartenza")))
        return 5;
    else if(!(strcmp(comando, "acquisizione")))
        return 6;
    else if(!(strcmp(comando, "fine")))
        return 7;

    return -1;
}


void stampaRigaLog(rigaLog dati) {
    printf("%10s\t%10s\t%10s\t%02d-%02d-%04d\t%02d:%02d\t%02d:%02d\t%3d\n",
           dati.codiceTratta, dati.partenza, dati.destinazione,
           dati.data.giorno, dati.data.mese, dati.data.anno,
           dati.oraPart.ore, dati.oraPart.min, dati.oraArr.ore, dati.oraArr.min,
           dati.ritardo);
}


void stampaLog(int nr, rigaLog **log){
    int i;
    printf("\n");
    for(i=0; i<nr; i++) {
        stampaRigaLog(*log[i]);
    }
    printf("\n");
}


void ordinaPerDate(int nr, rigaLog *dati, rigaLog **ordinato){
    int i;
    char **date = malloc(sizeof(char*) * nr);
    for(i=0; i<nr; i++) {
        date[i] = malloc(sizeof(char*));
        fromDatetoString(dati[i].data, dati[i].oraPart, date[i]);
    }
    for(i=0;i<nr;i++)
        printf("%s\n", date[i]);
    bubbleSortStr(nr, date, ordinato);
    for(i=0; i<nr; i++)
        free(date[i]);
    free(date);
}


void ordinaPerPartenza(int nr, rigaLog *dati, rigaLog **ordinato){
    int i;
    char **partenze = malloc(sizeof(char*)*nr);
    for(i=0; i<nr; i++) {
        partenze[i] = malloc(sizeof(char *));
        strcpy(partenze[i], dati[i].partenza);
    }
    bubbleSortStr(nr, partenze, ordinato);
    for(i=0; i<nr; i++)
        free(partenze[i]);
    free(partenze);
}


void ordinaPerCapolinea(int nr, rigaLog *dati, rigaLog **ordinato){
    int i;
    char **capolinea = malloc(sizeof(char*) * nr);
    for(i=0; i<nr; i++) {
        capolinea[i] = malloc(sizeof(char *));
        strcpy(capolinea[i], dati[i].destinazione);
    }
    bubbleSortStr(nr, capolinea, ordinato);
    for(i=0; i<nr; i++)
        free(capolinea[i]);
    free(capolinea);
}


void ordinaPerTratta(int nr, rigaLog *dati, rigaLog **ordinato){
    int i;
    char **tratta = malloc(sizeof(char*) * nr);
    for(i=0; i<nr; i++) {
        tratta[i] = malloc(sizeof(char *));
        strcpy(tratta[i], dati[i].codiceTratta);
    }
    bubbleSortStr(nr, tratta, ordinato);
    for(i=0; i<nr; i++)
        free(tratta[i]);
    free(tratta);
}


void ricercaPartenza(int nr, rigaLog *dati, char *partenza){
    int i, j;
    for(i=0, j=0; i<nr; i++){
        while((tolower(partenza[j]) - tolower(dati[i].partenza[j])) == 0) {
            j++;
            if(j==strlen(partenza))
                stampaRigaLog(dati[i]);
        }
        j=0;
    }
}


int ricercaDicotomica(int l, int r, rigaLog **ordinato, char *partenza){
    int nr = r-l;
    rigaLog **trovato;
    if(l==r)
        return -1;
    if(strncmp(partenza, ordinato[l+nr/2]->partenza, strlen(partenza)) > 0)
        ricercaDicotomica(nr/2 +1+ l, r, ordinato, partenza);
    else if(strncmp(partenza, ordinato[nr/2]->partenza, strlen(partenza)) < 0)
        ricercaDicotomica(l, nr/2, ordinato, partenza);
    else{
        trovato = &ordinato[l + nr/2];
        while(strncmp(partenza, (*trovato)->partenza, strlen(partenza)) == 0)
            trovato--;
        trovato++;
        while(strncmp(partenza, (*trovato)->partenza, strlen(partenza)) == 0) {
            stampaRigaLog(**trovato);
            trovato++;
        }
        return nr/2;
    }
}


void bubbleSortStr(int nr, char **dati, rigaLog **ordinato){
    int i, j;
    char temp[N];
    rigaLog *tempP;
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nr - i - 1; j++) {
            //Scambio valori
            if(strcmp(dati[j], dati[j+1]) > 0){
                strcpy(temp, dati[j]);
                strcpy(dati[j], dati[j+1]);
                strcpy(dati[j+1], temp);

                tempP = ordinato[j];
                ordinato[j] = ordinato[j + 1];
                ordinato[j + 1] = tempP;
            }
        }
    }
}


rigaLog** inizializzaPuntatore(int nr, rigaLog dati[nr]){
    int i;
    rigaLog **punt = malloc(sizeof(rigaLog*)*nr);
    for(i=0; i<nr; i++)
        punt[i] = &dati[i];
    return punt;
}


void fromDatetoString(data daConvD, orario daConvH, char *converted){
    sprintf(converted, "%4d%2d%2d%2d%2d", daConvD.anno, daConvD.mese, daConvD.giorno, daConvH.ore, daConvH.min);
}
