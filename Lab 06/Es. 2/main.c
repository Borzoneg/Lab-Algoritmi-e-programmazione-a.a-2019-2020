#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 50

typedef struct anagrafica *link;

typedef struct anagrafica{
    char* codice;
    char* nome;
    char* cognome;
    char* dataNasc;
    char* via;
    char* citta;
    int cap;
    link next;
}anagrafica;

typedef enum{
    aggiungi, file, stampa, rcodice, rmcodice, rmdate, fine
}menu;

int leggicomdando(char*comando);
link leggiFile(char *filename, link head);
link aggiungiElemento(link head, link elemento);
char *giraData(char *data);
anagrafica riempiCampi(char* codice, char* nome, char* cognome, char* dataNasc, char* via, char* citta, int cap);
anagrafica ricercaPerCodice(link head, char* codice);
void stampaElemento(anagrafica elemento);
void stampaSuFile(link head, char *filename);
anagrafica rimuoviPerCodice(link *head, char* codice);
link rimuoviperDate(link *head, char *dataIniz, char *dataFin);
link trovaTroppoGiovane(link head, char *dataFin);
link trovaUltimo(link head, char *dataIniz);
void libera (link head);


int main() {
    int continua = 1, com;
    char *comando = malloc(sizeof(char)*10);
    char *dato, *dato2;
    link head = NULL, eliminati;
    anagrafica elemento;
    while (continua){
        printf("Inserisci un comando per continuare:\n"
               "Aggiungi: aggiungi un elemento campo per campo\n"
               "File: aggiungi tutti gli elementi all'interno di un file\n"
               "Stampa: stampa la lista su file\n"
               "Rcodice: ricerca di un elemento per codice\n"
               "rmCodice: rimozione di un elemento, ricercato per codice\n"
               "rmDate: rimozione di tutti gli elementi in un intervallo di date\n");
        scanf("%s", comando);
        com = leggicomdando(comando);
        switch (com){
            case aggiungi:
                printf("Inserire i campi separati da uno spazio\n"
                       "Codice nome cognome gg/mm/yyyy via citta cap\n");
                elemento.codice = malloc(sizeof(char)*N);
                elemento.nome = malloc(sizeof(char)*N);
                elemento.cognome = malloc(sizeof(char)*N);
                elemento.dataNasc = malloc(sizeof(char)*N);
                elemento.via = malloc(sizeof(char)*N);
                elemento.citta = malloc(sizeof(char)*N);
                elemento.next = NULL;
                scanf("%s %s %s %s %s %s %d", elemento.codice, elemento.nome, elemento.cognome,
                        elemento.dataNasc, elemento.via, elemento.citta, &elemento.cap);
                head = aggiungiElemento(head, &elemento);
                break;
            case file:
                dato = malloc(sizeof(char) * 15);
                printf("Inserire nome file:\n");
                scanf("%s", dato);
                head = leggiFile(dato, head);
                if(head == NULL)
                    printf("Lettura non riuscita, controllare nome del file\n");
                free(dato);
                break;
            case stampa:
                dato = malloc(sizeof(char) * 15);
                printf("Inserire nome file:\n");
                scanf("%s", dato);
                stampaSuFile(head, dato);
                free(dato);
                break;
            case rcodice:
                dato = malloc(sizeof(char) * 15);
                printf("Inserire codice:\n");
                scanf("%s", dato);
                elemento = ricercaPerCodice(head, dato);
                if(elemento.cap >0)
                    stampaElemento(elemento);
                else
                    printf("Elemento non trovato\n");
                free(dato);
                break;
            case rmcodice:
                dato = malloc(sizeof(char) * 15);
                printf("Inserire codice:\n");
                scanf("%s", dato);
                elemento = rimuoviPerCodice(&head, dato);
                if(elemento.cap>0){
                    stampaElemento(elemento);
                    printf("e' stato eliminato\n");
                    libera(&elemento);
                }
                else
                    printf("L'elemento non e' presente in lista\n");
                free(dato);
                break;
            case rmdate:
                dato = malloc(sizeof(char)* 12);
                dato2 = malloc(sizeof(char)* 12);
                printf("Inserire le due date separate da uno spazio nella forma: gg/mm/yyyy\n");
                scanf("%s %s", dato, dato2);
                eliminati = rimuoviperDate(&head, dato, dato2);
                if(eliminati == NULL)
                    printf("Nessun elemento nell'intervallo");
                else {
                    printf("Elementi eliminati:\n");
                    stampaSuFile(eliminati, "console");
                    libera(eliminati);
                }
                break;
            case fine:
                printf("Arrivederci!");
                free(comando);
                continua = 0;
                libera(head);
                break;
            default:
                printf("Comando inserito non riconosciuto, prego riprovare\n");
        }
    }
    return 0;
}


anagrafica riempiCampi(char* codice, char* nome, char* cognome, char* dataNasc, char* via, char* citta, int cap){
    anagrafica elemento;
    elemento.codice = malloc(sizeof(codice));
    elemento.nome = malloc(sizeof(nome));
    elemento.cognome = malloc(sizeof(cognome));
    elemento.dataNasc = malloc(sizeof(dataNasc));
    elemento.via = malloc(sizeof(via));
    elemento.citta = malloc(sizeof(citta));

    strcpy(elemento.codice, codice);
    strcpy(elemento.nome, nome);
    strcpy(elemento.cognome, cognome);
    strcpy(elemento.dataNasc, dataNasc);
    strcpy(elemento.via, via);
    strcpy(elemento.citta, citta);
    elemento.cap  = cap;
    elemento.next = NULL;
    return elemento;
}


link aggiungiElemento(link head, link elemento){
    link i, tmp;
    char *dataGirEl, *dataGir;

    // se la lista è nulla la testa della lista diverrà il nuovo elemento
    if(head == NULL)
        return elemento;

    dataGir = giraData(head->dataNasc);
    dataGirEl = giraData(elemento->dataNasc);

    // gestisco il caso in cui la head sia da mettere sotto l'elemento nuovo
    if(strcmp(dataGir, dataGirEl)< 0){
        tmp = head;
        head = elemento;
        elemento->next = tmp;
        return head;
    }
    // altrimenti itero per trovare la giusta posizione del nuovo elemento
    for(i=head; i->next != NULL; i = i->next){
        dataGir = giraData(i->next->dataNasc);
        if(strcmp(dataGir, dataGirEl) < 0){
            tmp = i->next;
            elemento->next = tmp;
            i->next = elemento;
            return head;
        }

    }
    // se sono arrivato fin qui senza uscire da uno delle terminazioni superiori allora l'elemento sarà da mettere
    // al fondo della lista
    i->next = elemento;
    return head;
}


link leggiFile(char *filename, link head){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Errore file\n");
        return NULL;
    }

    // alloco le stringhe e il link in modo che rimangano nell'heap e non si perdano nel return al main
    char *codice = malloc(sizeof(char)*N);
    char *nome = malloc(sizeof(char)*N);
    char *cognome = malloc(sizeof(char)*N);
    char *dataNasc = malloc(sizeof(char)*N);
    char *via = malloc(sizeof(char)*N);
    char *citta = malloc(sizeof(char)*N);
    int cap;
    // per ogni elemento nella lista utilizzo la funzione di aggiunta singola
    while(fscanf(fp, "%s %s %s %s %s %s %d", codice, nome, cognome, dataNasc, via, citta, &cap) == 7){
        link newElement = malloc(sizeof(char)*N*6 + sizeof(int) + sizeof(link));
        *newElement = riempiCampi(codice, nome, cognome, dataNasc, via, citta, cap);
        head = aggiungiElemento(head, newElement);
    }
    return head;
}


anagrafica ricercaPerCodice(link head, char* codice){
    link i;
    for(i=head; i != NULL; i = i->next){
        if(!(strcmp(codice, i->codice)))
            return *i;
    }
    return (riempiCampi("AXXXX", "NA", "NA", "gg/mm/yyyy", "NA", "NA", -1));
}


void stampaElemento(anagrafica elemento){
    printf("%s %s %s %s %s %s %d\n", elemento.codice, elemento.nome, elemento.cognome,
            elemento.dataNasc, elemento.via, elemento.citta, elemento.cap);

}


void stampaSuFile(link head, char *filename){
    link i;
    if(!strcmp(filename, "console")){
        for(i=head; i!=NULL; i=i->next)
            fprintf(stdout, "%s %s %s %s %s %s %d\n", i->codice, i->nome, i->cognome,
                    i->dataNasc, i->via, i->citta, i->cap);
    }
    else {
        FILE *fp = fopen(filename, "w");
        for (i = head; i != NULL; i = i->next)
            fprintf(fp, "%s %s %s %s %s %s %d\n", i->codice, i->nome, i->cognome,
                    i->dataNasc, i->via, i->citta, i->cap);
        fclose(fp);
    }

}


anagrafica rimuoviPerCodice(link *head, char* codice){
    link i, tmp;
    // gestisco il caso in cui la head sia l'elemento cercato
    if(!(strcmp((*head)->codice,codice))){
        tmp = *head;
        *head = (*head)->next;
        tmp->next = NULL;
        return *tmp;
    }
    // altrimenti vado avanti con un for per ogni elemento della lista fino a trovare l'elemento che mi serve e lo ritorno
    for(i=(*head); i->next != NULL; i= i->next){
        if(!strcmp(i->next->codice, codice)) {
            tmp = i->next;
            i->next = i->next->next;
            tmp->next =NULL;
            return *tmp;
        }
    }
    // altrimenti ritorno una struct nulla
    return (riempiCampi("AXXXX", "NA", "NA", "gg/mm/yyyy", "NA", "NA", -1));
}


link rimuoviperDate(link *head, char *dataIniz, char *dataFin){
    link tmp = NULL, troppoGiovane;
    // trovo l'ultimo compreso nell'intervallo
    link ultimo = trovaUltimo((*head), giraData(dataIniz));
    // se head è nell'intervallo inizializzo tmp
    // e cambio head perchè diventi il successivo all'ultimo elemento da eliminare
    if (strcmp(giraData(dataFin), giraData((*head)->dataNasc)) >= 0) {
        tmp = *head;
        *head = ultimo->next;
    }
        // altrimenti trovo l'elemento troppo giovane per stare nell'intervallo, che mi servirà per metter il suo
        // campo next al primo elmento troppo vecchio per stare in intervallo
    else {
        troppoGiovane = trovaTroppoGiovane((*head), giraData(dataFin));
    }
    // se siamo nel caso in cui head sia all'interno dell'intervallo allora salto altrimenti entro in questo caso
    if (tmp == NULL) {
        // salvo il valore del più giovane nell'intervallo che è quello dopo il "troppo giovane"
        tmp = troppoGiovane->next;
        // ora quello troppo giovane punta a quello troppo vecchio
        troppoGiovane->next = ultimo->next;
    }
    // nel caso in cui ultimo e troppogiovane siano uguali (lo vediamo dalla chiave univoca) non devo eliminare niente
    if(ultimo->codice != NULL && !strcmp(troppoGiovane->codice, ultimo->codice))
        return NULL;

    // infine il campo next dell'ultimo diventa nullo, per poter stampare correttamente gli elementi eliminati
    ultimo->next = NULL;
    // ritorno tmp che è l'elemento più giovane tra quelli eliminati
    return tmp;
}


link trovaTroppoGiovane(link head, char *dataFin){
    if(head==NULL)
        return NULL;
    if(strcmp(dataFin, giraData(head->next->dataNasc)) >= 0)
        return head;
    link troppoGiovane = trovaTroppoGiovane(head->next, dataFin);
    return troppoGiovane;
}


link trovaUltimo(link head, char *dataIniz){
    if(head->next==NULL)
        return NULL;
    if(strcmp(dataIniz, giraData(head->next->dataNasc)) >= 0)
        return head;
    link ultimo = trovaUltimo(head->next, dataIniz);
    if(ultimo==NULL){
        anagrafica p = riempiCampi("AXXXX", "NA", "NA", "gg/mm/yyyy", "NA", "NA", -1);
        ultimo = &p;
    }
    return ultimo;
}


void libera (link head){
    link i;
    for(i=head; i!=NULL; i=i->next){
        free(i->codice);
        free(i->nome);
        free(i->cognome);
        free(i->via);
        free(i->citta);
        free(i->dataNasc);
    }
}


int leggicomdando(char*comando){
    int i;
    for(i=0; i<strlen(comando); i++)
        comando[i] = tolower(comando[i]);
    if(!strcmp(comando, "aggiungi"))
        return 0;
    if(!strcmp(comando, "file"))
        return 1;
    if(!strcmp(comando, "stampa"))
        return 2;
    if(!strcmp(comando, "rcodice"))
        return 3;
    if(!strcmp(comando, "rmcodice"))
        return 4;
    if(!strcmp(comando, "rmdate"))
        return 5;
    if(!strcmp(comando, "fine"))
        return 6;
    return -1;
}


char *giraData(char *data){
    int giorno, mese, anno;
    char *dataGirata = malloc(sizeof(char)*10);
    sscanf(data, "%d/%d/%d", &giorno, &mese, &anno);
    sprintf(dataGirata, "%04d/%02d/%02d", anno, mese, giorno);
    return dataGirata;
}