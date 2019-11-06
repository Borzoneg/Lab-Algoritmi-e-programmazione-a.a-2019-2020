#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 30
#define R 1000
#define C 20

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
    stampa, Odata, Otratta, Opartenza, Ocapolinea, Rpartenza, fine
}menu;


int leggiFile(char filename[N], rigaLog dati[R]);
int leggicomando(char comando[C]);
void stampaRigaLog(rigaLog dati);
void stampaLog(int nr, rigaLog *log[nr]);
void ordinaPerDate(int nr, rigaLog dati[nr], rigaLog *ordinato[nr]);
void ordinaPerPartenza(int nr, rigaLog dati[nr], rigaLog *ordinato[nr]);
void ordinaPerCapolinea(int nr, rigaLog dati[nr], rigaLog *ordinato[nr]);
void ordinaPertratta(int nr, rigaLog dati[nr], rigaLog *ordinato[nr]);
void ricercaPartenza(int nr, rigaLog dati[nr], char partenza[N]);
int ricercaDicotomica(int l, int r, rigaLog *ordinato[R], char partenza[N]);
void bubbleSortStr(int nr, char dati[nr][N], rigaLog *ordinato[nr]);
void inizializzaPuntatore(int nr, rigaLog dati[nr], rigaLog *punt[nr]);
void fromDatetoString(data daConvD, orario daConvH, char converted[12]);
void copiaOrd(int nr, rigaLog *src[nr], rigaLog *dest[nr]);


int main() {
    rigaLog r[R];

    rigaLog *ordAtt[R];
    rigaLog *ordDate[R];
    rigaLog *ordPartenza[R];
    rigaLog *ordCapolinea[R];
    rigaLog *ordTratta[R];

    menu scelta;
    char comando[C], partstr[C];
    int continua = 1, nr;

    nr = leggiFile("corse.txt", r);

    inizializzaPuntatore(nr, r, ordAtt);
    inizializzaPuntatore(nr, r, ordDate);
    inizializzaPuntatore(nr, r, ordTratta);
    inizializzaPuntatore(nr, r, ordPartenza);
    inizializzaPuntatore(nr, r, ordCapolinea);

    while(continua){
        printf("Inserisci comando:\n"
               "Stampa: per stampare il log per intero\n"
               "Odata: per odinare per data il database\n"
               "Otratta: per odinare per tratta il database\n"
               "Opartenza: per odinare per partenza il database\n"
               "Odestinazione: per ordinare per destinazione il database\n"
               "Rpartenza: per ricercare una una tratta per stazione di partenza\n"
               "fine: per uscire\n");

        scanf("%s", comando);
        scelta = leggicomando(comando);

        switch (scelta) {
            case stampa:
                stampaLog(nr, ordAtt);
                break;
            case Odata:
                ordinaPerDate(nr, r, ordDate);
                copiaOrd(nr, ordDate, ordAtt);
                break;
            case Otratta:
                ordinaPertratta(nr, r, ordTratta);
                copiaOrd(nr, ordTratta, ordAtt);
                break;
            case Opartenza:
                ordinaPerPartenza(nr, r, ordPartenza);
                copiaOrd(nr, ordPartenza, ordAtt);
                break;
            case Ocapolinea:
                ordinaPerCapolinea(nr, r, ordCapolinea);
                copiaOrd(nr, ordCapolinea, ordAtt);
                break;
            case Rpartenza:
                scanf("%s", partstr);
                ricercaPartenza(nr, r, partstr);
                break;
            case fine:
                printf("Arrivederci!");
                continua = 0;
                break;
            default:
                printf("Comando inserito non riconosciuto, prego riprovare");
        }
    }
    return 0;
}


int leggiFile(char filename[N], rigaLog dati[R]){
    int i, nRig;
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File non trovato");
        return 0;
    }
    fscanf(fp, "%d", &nRig);
    fscanf(fp,"");
    for(i=0; i<nRig; i++){
        fscanf(fp, "%s %s %s %d-%d-%d %d:%d %d:%d %d",
               dati[i].codiceTratta, dati[i].partenza, dati[i].destinazione,
               &dati[i].data.giorno, &dati[i].data.mese, &dati[i].data.anno,
               &dati[i].oraPart.ore, &dati[i].oraPart.min, &dati[i].oraArr.ore, &dati[i].oraArr.min,
               &dati[i].ritardo);
    }
    fclose(fp);
    return nRig;
}


int leggicomando(char comando[C]){
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
    else if(!(strcmp(comando, "fine")))
        return 6;

    return -1;
}


void stampaRigaLog(rigaLog dati) {
    printf("%10s\t%10s\t%10s\t%02d-%02d-%04d\t%02d:%02d\t%02d:%02d\t%3d\n",
           dati.codiceTratta, dati.partenza, dati.destinazione,
           dati.data.giorno, dati.data.mese, dati.data.anno,
           dati.oraPart.ore, dati.oraPart.min, dati.oraArr.ore, dati.oraArr.min,
           dati.ritardo);
}


void stampaLog(int nr, rigaLog *log[nr]){
    int i;
    printf("\n");
    for(i=0; i<nr; i++) {
        stampaRigaLog(*log[i]);
    }
    printf("\n");
}


void ordinaPerDate(int nr, rigaLog dati[R], rigaLog *ordinato[R]){
    int i;
    char date[nr][N];

    for(i=0; i<nr; i++)
        fromDatetoString(dati[i].data, dati[i].oraPart, date[i]);
    bubbleSortStr(nr, date, ordinato);
}


void ordinaPerPartenza(int nr, rigaLog dati[R], rigaLog *ordinato[R]){
    int i;
    char partenze[nr][N];
    for(i=0; i<nr; i++)
        strcpy(partenze[i], dati[i].partenza);

    bubbleSortStr(nr, partenze, ordinato);
}


void ordinaPerCapolinea(int nr, rigaLog dati[R], rigaLog *ordinato[R]){
    int i;
    char destinazioni[nr][N];
    for(i=0; i<nr; i++)
        strcpy(destinazioni[i], dati[i].destinazione);

    bubbleSortStr(nr, destinazioni, ordinato);
}


void ordinaPertratta(int nr, rigaLog dati[R], rigaLog *ordinato[R]){
    int i;
    char tratta[nr][N];
    for(i=0; i<nr; i++)
        strcpy(tratta[i], dati[i].codiceTratta);

    bubbleSortStr(nr, tratta, ordinato);
}


void ricercaPartenza(int nr, rigaLog dati[R], char partenza[N]){
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


int ricercaDicotomica(int l, int r, rigaLog *ordinato[R], char partenza[N]){
    int i = 0, nr = r-l;
    printf("%s\t%s\n", ordinato[nr/2]->partenza, partenza);
    if(strncmp(partenza, ordinato[nr/2]->partenza, strlen(partenza)) > 0)
        ricercaDicotomica(nr/2 +1, r, ordinato, partenza);
    else if(strncmp(partenza, ordinato[nr/2]->partenza, strlen(partenza)) < 0)
        ricercaDicotomica(l, nr/2, ordinato, partenza);
    else{
        i = nr/2;
        while(strncmp(partenza, ordinato[i]->partenza, strlen(partenza)) == 0)
            i--;

        while(strncmp(partenza, ordinato[++i]->partenza, strlen(partenza)) == 0)
            stampaRigaLog(*ordinato[i]);
        return nr/2;
    }


}


void bubbleSortStr(int nr, char dati[nr][N], rigaLog *ordinato[nr]){
    int i, j;
    char temp[N];
    rigaLog *tempP;
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nr - i - 1; j++) {
            //Scambio valori}
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


void inizializzaPuntatore(int nr, rigaLog dati[nr], rigaLog *punt[nr]){
    int i;
    for(i=0; i<nr; i++)
        punt[i] = &dati[i];
}


void fromDatetoString(data daConvD, orario daConvH, char converted[12]){
    sprintf(converted, "%2d%2d%4d%2d%2d", daConvD.anno, daConvD.mese, daConvD.giorno, daConvH.ore, daConvH.min);
}


void copiaOrd(int nr, rigaLog *src[nr], rigaLog *dest[nr]){
    int i;
    for(i=0; i<nr; i++)
        dest[i] = src[i];
}