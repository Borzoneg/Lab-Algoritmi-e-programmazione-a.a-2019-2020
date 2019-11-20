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


link leggiFile(char *filename, link head);
link aggiungiElemento(link head, link elemento);
char *giraData(char *data);
anagrafica riempiCampi(char* codice, char* nome, char* cognome, char* dataNasc, char* via, char* citta, int cap);

int main() {
    link i, head = NULL;
    anagrafica el, el2, el3, el4;
    el = riempiCampi("A0000", "Alfredo", "Bici",
            "24/04/1999", "Pontedassio", "PontedassioRue", 18100);
    el2 = riempiCampi("A0001", "Simone", "Clemenzi",
            "24/06/1999", "Pontedassio", "PontedassioRue", 18101);
    el3 = riempiCampi("A0002", "Giuseppe", "Bruzzone",
            "05/04/1999", "Imperia", "Stradadefrancesi", 18102);
    el4 = riempiCampi("A0003", "Valerio", "Carrivale",
            "20/08/1999", "cascione", "imperia", 18123);

    head = aggiungiElemento(head, &el);
    head = aggiungiElemento(head, &el2);
    head = aggiungiElemento(head, &el3);
    head = aggiungiElemento(head, &el4);
    leggiFile("pazienti", head);
    for(i=head; i!=NULL; i = i->next)
        printf("%d\n", i->cap);
    return 0;
}


anagrafica riempiCampi(char* codice, char* nome, char* cognome, char* dataNasc, char* via, char* citta, int cap){
    anagrafica elemento;
    elemento.codice = codice;
    elemento.nome = nome;
    elemento.cognome = cognome;
    elemento.dataNasc = dataNasc;
    elemento.via = via;
    elemento.citta = citta;
    elemento.cap  = cap;
    elemento.next = NULL;
    return elemento;
}

link aggiungiElemento(link head, link elemento){
    link i, tmp;
    char* dataGirEl, *dataGir;

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

    char codice[N],nome[N], cognome[N],dataNasc[N], via[N], citta [N];
    int cap;
    while(fscanf(fp, "%s %s %s %s %s %s %d", codice, nome, cognome, dataNasc, via, citta, &cap) == 7){
        link newElement = malloc(sizeof(char)*N*6 + sizeof(int) + sizeof(link));
        *newElement = riempiCampi(codice, nome, cognome, dataNasc, via, citta, cap);
        head = aggiungiElemento(head, newElement);
    }
    return head;
}


char *giraData(char *data){
    int giorno, mese, anno;
    char *dataGirata = malloc(sizeof(char)*10);
    sscanf(data, "%d/%d/%d", &giorno, &mese, &anno);
    sprintf(dataGirata, "%04d/%02d/%02d", anno, mese, giorno);
    return dataGirata;
}