// TODO:    posso scrivere i prototipi e le funzioni come
//          void funzione(int nr, rigaLog dati[nr]);
//          per risparmiare memoria invece di come sono ora?

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
void stampaLog(rigaLog dati[R], int nr);
void ordinaPerDate(rigaLog dati[R], int nr, rigaLog *ordinato[R]);
void ordinaPerPartenza(rigaLog dati[R], int nr, rigaLog *ordinato[R]);
void ordinaPerCapolinea(rigaLog dati[R], int nr, rigaLog *ordinato[R]);
void ordinaPertratta(rigaLog dati[R], int nr, rigaLog *ordinato[R]);
void ricercaPartenza(rigaLog dati[R], int nr, char partenza[N]);
int fromDatetoInt(data date, data riferimento);

int main() {
    rigaLog r[R];
    rigaLog *ordDate[R];
    rigaLog *ordPartenza[R];
    rigaLog *ordCapolinea[R];
    rigaLog *ordTratta[R];

    menu scelta;
    char comando[C], data1[C];
    int continua = 1, nr;

    nr = leggiFile("corse.txt", r);
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
                stampaLog(r, nr);
                break;
            case Odata:
                ordinaPerDate(r, nr, ordDate);
                break;
            case Otratta:
                ordinaPertratta(r, nr, ordTratta);
                break;
            case Opartenza:
                ordinaPerPartenza(r, nr, ordPartenza);
                break;
            case Ocapolinea:
                ordinaPerCapolinea(r, nr, ordCapolinea);
                break;
            case Rpartenza:
                scanf("%s", data1);
                ricercaPartenza(r, nr, data1);
                break;
            case fine:
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
    if(!(strcmp(comando, "odata")))
        return 1;
    if(!(strcmp(comando, "otratta")))
        return 2;
    if(!(strcmp(comando, "opartenza")))
        return 3;
    if(!(strcmp(comando, "ocapolinea")))
        return 4;
    if(!(strcmp(comando, "rpartenza")))
        return 5;
    if(!(strcmp(comando, "fine")))
        return 6;
}


data fromStringtoDate(char str[C]){
    data form;
    int i;
    // gestione di caratteri diversi da '-', ad esempio '/'
    for(i=0; i<strlen(str); i++){
        if(!isdigit(str[i]))
            str[i] = '-';
    }
    sscanf(str, "%d-%d-%d", &form.giorno, &form.mese, &form.anno);
    if(form.giorno < 1 || form.giorno > 31 || form.mese < 1 || form.mese > 12)
        form.giorno = -1;
    return form;
}


void stampaRigaLog(rigaLog dati) {
    printf("%s %s %s %d-%d-%d %d:%d %d:%d %d\n",
           dati.codiceTratta, dati.partenza, dati.destinazione,
           dati.data.giorno, dati.data.mese, dati.data.anno,
           dati.oraPart.ore, dati.oraPart.min, dati.oraArr.ore, dati.oraArr.min,
           dati.ritardo);
}


void stampaLog(rigaLog dati[R], int nr){
    int i;
    printf("\n");
    for(i=0; i<nr; i++){
        stampaRigaLog(dati[i]);
    }
    printf("\n");
}


void ordinaPerDate(rigaLog dati[R], int nr, rigaLog *ordinato[R]){
    int i, annoMin, tempo[R];
    annoMin = dati[0].data.anno;
    for(i=1; i<nr; i++){
        if(dati[i].data.anno < annoMin)
            annoMin = dati[i].data.anno;
    }

}


void ordinaPerPartenza(rigaLog dati[R], int nr, rigaLog *ordinato[R]){
    int i;
    for(i=0; i<nr; i++){

    }
}


void ordinaPerCapolinea(rigaLog dati[R], int nr, rigaLog *ordinato[R]){

}


void ordinaPertratta(rigaLog dati[R], int nr, rigaLog *ordinato[R]){

}


void ricercaPartenza(rigaLog dati[R], int nr, char partenza[N]){

}


int fromDatetoInt(data date, data riferimento){
    int a = 0;
    a += (date.anno - riferimento.anno - 1) * 365 * 24 * 60;
    a += (date.giorno - riferimento.giorno - 1)  * 24 * 60;
    return a;
}