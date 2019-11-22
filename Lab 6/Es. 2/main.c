// TODO:
//          -cancellazione (con estrazione del dato) di un elemento dalla lista, previa ricerca per codice
//          -cancellazione (con estrazione del dato) di tutti gli elementi con date comprese tra 2 date lette da tastiera.
//              Si consiglia, anziché di realizzare una funzione che cancelli dalla lista questi
//              elementi, restituendoli memorizzati in una lista o in un vettore dinamico, di implementare
//              una funzione che estragga e restituisca al programma chiamante il primo degli elementi
//              appartenenti all’intervallo. Il programma chiamante itererà la chiamata di questa funzione,
//              stampando il risultato, per tutti gli elementi dell’intervallo



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
anagrafica rimuoviperDate(link *head, char *dataIniz, char *dataFin, int inInt);
anagrafica trovaPreInizio(link head, char *dataIniz);
anagrafica trovaFine(link inizio,  char *dataFin);


int main() {
    int continua = 1, com;
    char *comando = malloc(sizeof(char)*10);
    char *dato, *dato2;
    link i, head = NULL;
    anagrafica elemento;

    // TEST
    anagrafica el, el2, el3, el4, el5, el6, el7;
    el = riempiCampi("A0000", "Alfredo", "Bici",
            "24/04/1999", "Pontedassio", "PontedassioRue", 0);
    el2 = riempiCampi("A0001", "Simone", "Clemenzi",
            "24/06/1999", "Pontedassio", "PontedassioRue", 1);
    el3 = riempiCampi("A0002", "Giuseppe", "Bruzzone",
            "05/04/1999", "Imperia", "Stradadefrancesi", 2);
    el4 = riempiCampi("A0003", "Valerio", "Carrivale",
            "20/08/1999", "cascione", "imperia", 3);

    head = aggiungiElemento(head, &el);
    head = aggiungiElemento(head, &el2);
    head = aggiungiElemento(head, &el3);
    head = aggiungiElemento(head, &el4);
    head = leggiFile("pazienti", head);
//
//    for(i=head; i!=NULL; i=i->next)
//        stampaElemento(*i);
//
//    printf("\n\n");
//
    for(i=head; i!=NULL; i=i->next)
        stampaElemento(*i);
    printf("%d\n", strcmp("1999/06/25","1999/07/02"));
    anagrafica p  = rimuoviperDate(&head, "23/04/1999", "25/06/1999", 0);

    for(i=&p; i!=NULL; i=i->next)
        stampaElemento(*i);


    continua = 0;
    //FINE TEST

    while (continua){
        printf("Benvenuto, inserisci un comando per continuare:\n"
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
                }
                else
                    printf("L'elemento non e' presente in lista\n");
                free(dato);
                break;
            case rmdate:
                dato = malloc(sizeof(char)* 12);
                dato2 = malloc(sizeof(char)* 12);
                printf("Inserire le due date separate da uno spazio nella forma: gg/mm/yyyy");
                scanf("%s %s", dato, dato2);
                printf("NON IMPLEMENTATA");
                break;
            case fine:
                printf("Arrivederci!");
                free(comando);
                continua = 0;
                break;
            default:
                printf("Comando inserito non riconosciuto, prego riprovare");
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

    if(head == NULL)
        return elemento;

    dataGir = giraData(head->dataNasc);
    dataGirEl = giraData(elemento->dataNasc);

    if(strcmp(dataGir, dataGirEl)< 0){
        tmp = head;
        head = elemento;
        elemento->next = tmp;
        return head;
    }
    for(i=head; i->next != NULL; i = i->next){
        dataGir = giraData(i->next->dataNasc);
        if(strcmp(dataGir, dataGirEl) < 0){
            tmp = i->next;
            elemento->next = tmp;
            i->next = elemento;
            return head;
        }

    }
    i->next = elemento;
    return head;
}


link leggiFile(char *filename, link head){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Errore file\n");
        return NULL;
    }

    char *codice = malloc(sizeof(char)*N);
    char *nome = malloc(sizeof(char)*N);
    char *cognome = malloc(sizeof(char)*N);
    char *dataNasc = malloc(sizeof(char)*N);
    char *via = malloc(sizeof(char)*N);
    char *citta = malloc(sizeof(char)*N);
    int cap;
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
    FILE *fp = fopen(filename, "w");
    for(i=head; i!=NULL; i=i->next)
        fprintf(fp, "%s %s %s %s %s %s %d\n", i->codice, i->nome, i->cognome,
                i->dataNasc, i->via, i->citta, i->cap);
}


anagrafica rimuoviPerCodice(link *head, char* codice){
    link i, tmp;
    if(!(strcmp((*head)->codice,codice))){
        tmp = *head;
        *head = (*head)->next;
        return *tmp;
    }
    for(i=(*head); i->next != NULL; i= i->next){
        if(!strcmp(i->next->codice, codice)) {
            tmp = i->next;
            i->next = i->next->next;
            return *tmp;
        }
    }
    return (riempiCampi("AXXXX", "NA", "NA", "gg/mm/yyyy", "NA", "NA", -1));
}


anagrafica rimuoviperDate(link *head, char *dataIniz, char *dataFin, int inInt){
    anagrafica preElementoIniziale;
    char* dataInizGir = giraData(dataIniz);
    char* dataFinGir = giraData(dataFin);
    // Prima trovo la fine perchè essendo la lista ordinata dal più giovanee al più vecchio sarà più in alto la
    // data finale che la data iniziale
    preElementoIniziale = trovaPreInizio(*head, dataInizGir);
    anagrafica elementoFinale = trovaFine(preElementoIniziale.next, dataFinGir);
    preElementoIniziale.next = elementoFinale.next;
    elementoFinale.next = NULL;
    return *(preElementoIniziale.next);
}


anagrafica trovaPreInizio(link head, char *dataIniz){
    if(strcmp(dataIniz,giraData(head->dataNasc)) <= 0)
        return (*head);
    anagrafica preElementoIniziale = trovaPreInizio(head->next, dataIniz);
    return (riempiCampi("AXXXX", "NA", "NA", "gg/mm/yyyy", "NA", "NA", -1));
}


anagrafica trovaFine(link inizio,  char *dataFin){
    printf("%s %s %d", dataFin, giraData(inizio->next->dataNasc), strcmp(dataFin,giraData(inizio->next->dataNasc)));
    if(strcmp(dataFin,giraData(inizio->next->dataNasc)) <= 0)
        return (*inizio);
    anagrafica elementoFin = trovaFine(inizio->next, dataFin);
    return (riempiCampi("AXXXX", "NA", "NA", "gg/mm/yyyy", "NA", "NA", -1));
}

int leggicomdando(char*comando){
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