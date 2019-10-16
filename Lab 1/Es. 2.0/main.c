#include <stdio.h>
#include <string.h>

const int N = 200;
void replace(char parola[], char originale[], char ricodifica[], char sostituita[], int pos);
int fileOk(FILE *fp);
void codifica(char filename1[N], filename2[N]);

int main() {
    codifica("dizionario", "sorgente");
    return 0;
}


int fileOk(FILE *fp){
    if(fp == NULL)
        return 0;
    return 1;
}


void replace(char parola[], char originale[], char ricodifica[], char sostituita[], int pos){
    char c;
    int i, j = 0, k, sostituito = 0;
    // ciclo lungo la parola carattere per carattere
    for(i=0, k=0; i<strlen(parola); i++, k++){
        c = parola[i];
        // quando arrivo alla posizione dove iniia la sottostringa da sostituire entro
        if(i == pos && !sostituito){
            // ciclo per la lunghezza della stringa da mettere es: $33$
            for(; j<(strlen(ricodifica)); j++){
                sostituita[k+j] = ricodifica[j];
            }
            sostituito = 1;
            // aggiorno i e k in modo che i salti le lettere che sono stata sostituite e k salti le lettere che sono
            // stata aggiunte, k e i saranno quidi sfasate
            i = i+(strlen(originale)-1);
            k = k+(strlen(ricodifica)-1);
        }
        else
            sostituita[k] = c;

    }
    // la nuova parola potrebbe essere più corta della vecchia perciò "tronco" la stringa aggiungendo il terminatore
    // di stringhe come ultimo carattere
    sostituita[strlen(parola)- strlen(originale) + strlen(ricodifica)] = '\0';
}


void codifica(char filenamed[N], filenames[N]){
    FILE *fs, *fd;
    char parola[N], ricodifica[N], originale[N], sostituita[N];
    char *n, c;
    int nsos = 0, trovato=0, i, pos;
    fs = fopen(filenames, "r");
    fd = fopen(filenamed, "r");

    if(!fileOk(fs) || !fileOk(fd)){
        printf("File non trovati");
        return;
    }

    fscanf(fd, "%d", &nsos);
    // ciclo per ogni parola del sorgente.txt, prendo anche un char vicino in modo che quando c'è il '\n'
    // lo possa aggiungere dopo la parola per mantenere la formattazione
    while((fscanf(fs, "%s%c", parola, &c)) != -1){
        // il ciclo passa per ogni riga del file dizionario fino a passarle tutte o alla prima corrispondenza
        for(i=0;!trovato && i<nsos; i++){
            fscanf(fd, "%s %s", ricodifica, originale);
            if ((n = (strstr(parola, originale))) != NULL) {
                trovato = 1;
                // utilizzando strstr ottengo un puntatore al carattere della stringa che è il primo della
                // sottostringa che sto cercando, per evitare una sostituzione errata ho bisogno di avere l'indice
                // di tale carattere per poter sostituire la sottostringa nel punto giusto
                pos = n - parola;
                replace(parola, originale, ricodifica, sostituita, pos);
                // riazzero il buffer del file dizionario in modo che la prossima parola venga confrontata con tutte
                // le sottostringhe
                rewind(fd);
                fscanf(fd, "%d", &nsos);
            }
        }
        // nel caso in cui sono arrivato al fondo del file dizionario senza trovare corrispondenza riazzero il buffer
        // per riconfrontare tutte le sottostringhe alla prossima parola
        rewind(fd);
        fscanf(fd, "%d", &nsos);
        // se trovo una corrispondenza nel file scriverò la nuova parola con il carattere che sarà niente se no ha
        // trovato niente oppure il carattere '\n'
        if(trovato)
            fprintf(stdout, "%s %c", sostituita, c);
            // se non ho trovato corrispondenza ristampo la parola lasciata com'era
        else
            fprintf(stdout, "%s %c", parola, c);
        trovato = 0;
    }
    fclose(fd);
    fclose(fs);
}