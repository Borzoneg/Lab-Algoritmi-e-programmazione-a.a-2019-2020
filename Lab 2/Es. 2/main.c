// TODO: controllo su date
//       input delle date più flessibile

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
    date, partenza, capolinea, ritardo, ritardo_tot, fine
}menu;

int leggiFile(char filename[N], rigaLog dati[R]);
int leggicomando(char comando[C]);
void dateFunz(rigaLog dati[R], int nr, data inizio, data fine);
void partenzeFunz(rigaLog dati[R], int nr, char partenza[N]);
void capolineaFunz(rigaLog dati[R], int nr, char capolinea[N]);
void ritardoFunz(rigaLog dati[R], int nr, data inizio, data fine);
int ritardoTotFunz(rigaLog dati[R], int nr, char codice[N]);
data fromStringtoDate(char str[C]);
void stampaRigaLog(rigaLog dati);
void isInInterval(rigaLog dati[R], int nr, data inizio, data fine, int risultati[R]);

int main() {
    rigaLog r[R];
    menu scelta;
    char comando[C], data1[C], data2[C], dato[C];
    int continua = 1, nr;
    data datainiz, datafin;

    nr = leggiFile("corse.txt", r);

//    ritardoTotFunz(r, nr, "123456");
    ritardoTotFunz(r, nr, "123456");

    while(continua) {
        printf("Inserisci comando:\n"
               "date: per vedere le corse partite in un intervallo di date\n"
               "partenza: per elencare tutti le corse partite da una certa fermata\n"
               "capolinea: per elencare tutti le corse che fanno capolinea in una certa fermata\n"
               "ritardo: per elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di"
               "date\n"
               "ritardo_tot: per elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di "
               "tratta\n"
               "fine: per uscire\n");
        scanf("%s", comando);
        scelta = leggicomando(comando);
        switch (scelta) {
            case date:
                printf("Comando inserito: %s\n"
                       "Inserire data di inizio e di fine nel formato: dd-mm-yyyy\n", comando);

                scanf("%s %s", data1, data2);
                datainiz = fromStringtoDate(data1);
                datafin = fromStringtoDate(data2);
                dateFunz(r, nr, datainiz, datafin);
                break;
            case partenza:
                printf("Comando inserito: %s\nInserire la stazione di partenze\n", comando);
                scanf("%s", dato);
                partenzeFunz(r, nr, dato);
                break;
            case capolinea:
                printf("Comando inserito: %s\nInserire la stazione capolinea\n", comando);
                scanf("%s", dato);
                capolineaFunz(r, nr, dato);
                break;
            case ritardo:
                printf("Comando inserito: %s\n"
                       "Inserire data di inizio e di fine nel formato: dd-mm-yyyy\n", comando);
                scanf("%s %s", data1, data2);
                datainiz = fromStringtoDate(data1);
                datafin = fromStringtoDate(data1);
                ritardoFunz(r, nr, datainiz, datafin);
                break;
            case ritardo_tot:
                printf("Comando inserito: %s\nInserire codice tratta:\n", comando);
                scanf("%s", dato);
                ritardoTotFunz(r, nr, dato);
                break;
            case fine:
                printf("Comando inserito: %s\nArrivederci!", comando);
                continua = 0;
                break;
            default:
                printf("Comando non corretto, riprovare\n");
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
    if(!(strcmp(comando, "date")))
        return 0;
    if(!(strcmp(comando, "partenza")))
        return 1;
    if(!(strcmp(comando, "capolinea")))
        return 2;
    if(!(strcmp(comando, "ritardo")))
        return 3;
    if(!(strcmp(comando, "ritardo_tot")))
        return 4;
    if(!(strcmp(comando, "fine")))
        return 5;
}


data fromStringtoDate(char str[C]){
    data form;
    sscanf(str, "%d-%d-%d", &form.giorno, &form.mese, &form.anno);
    return form;
}


void dateFunz(rigaLog dati[R], int nr, data inizio, data fine){
    int i, v[R];
    isInInterval(dati, nr, inizio, fine, v);
    for(i=0; i<nr; i++){
        if(v[i])
            stampaRigaLog(dati[i]);
    }
}


void partenzeFunz(rigaLog dati[R], int nr, char partenza[N]){
    int i;
    for(i=0; i<nr; i++){
        if(!strcmp(dati[i].partenza, partenza))
            stampaRigaLog(dati[i]);
    }
}


void capolineaFunz(rigaLog dati[R], int nr, char capolinea[N]){
    int i;
    for(i=0; i<nr; i++){
        if(!strcmp(dati[i].destinazione, capolinea))
            stampaRigaLog(dati[i]);
    }
}


void ritardoFunz(rigaLog dati[R], int nr, data inizio, data fine){
    int i, v[R];
    isInInterval(dati, nr, inizio, fine, v);
    for(i=0; i<nr; i++){
        if(v[i] && dati[i].ritardo > 0)
            stampaRigaLog(dati[i]);
    }
}


int ritardoTotFunz(rigaLog dati[R], int nr, char codice[N]){
    int i, ritardo = 0;
    printf("%s", dati[0].codiceTratta);
    for(i=0; i<nr; i++){
        if(!strcmp(dati[i].codiceTratta, codice))
            ritardo += dati[i].ritardo;
    }
    printf("Ritardo complessivo: %d min\n", ritardo);
    return ritardo;
}


void stampaRigaLog(rigaLog dati) {
    // 345678 savona trieste 27-07-2019 18:15 22:15 23
    printf("%s %s %s %d-%d-%d %d:%d %d:%d %d\n",
           dati.codiceTratta, dati.partenza, dati.destinazione,
           dati.data.giorno, dati.data.mese, dati.data.anno,
           dati.oraPart.ore, dati.oraPart.min, dati.oraArr.ore, dati.oraArr.min,
           dati.ritardo);
}


void isInInterval(rigaLog dati[R], int nr, data inizio, data fine, int risultati[R]){
    int i;

    for(i=0;i<nr; i++){
        risultati[i] = 0;
    }

    for(i=0; i<nr; i++){
        if(dati[i].data.anno > inizio.anno && dati[i].data.anno < fine.anno) {
            risultati[i] = 1;
            continue;
        }
        else {
            if(dati[i].data.mese > inizio.mese && dati[i].data.mese < fine.mese){
                risultati[i] = 1;
                continue;
            }
            else{
                if(dati[i].data.giorno > inizio.giorno && dati[i].data.giorno < fine.giorno){
                    risultati[i] = 1;
                    continue;
                }
                if(dati[i].data.mese == inizio.mese && dati[i].data.giorno >= inizio.giorno){
                    risultati[i] = 1;
                    continue;
                }
                if(dati[i].data.mese == fine.mese && dati[i].data.giorno <= fine.giorno){
                    risultati[i] = 1;
                    continue;
                }
            }
        }
    }
}
#pragma clang diagnostic pop