#ifndef ES__3_PERSONAGGIO_H
#define ES__3_PERSONAGGIO_H



#include "inventario.h"
typedef struct personaggio* linkPers;

typedef struct{
    int inUso;
    int* indiciOgg;
}equip;

typedef struct personaggio{
    char* codice;
    char* nome;
    char* classe;
    equip equipPers;
    stats statPers;
    linkPers next;
}personaggio;

typedef struct{
    linkPers head;
    linkPers tail;
    int nPersonaggi;
}DBpg;

void aggiungiPersonaggio(DBpg *dati, linkPers newPg);
void leggiFilePg(DBpg *dati, char *filename);
int eliminaPersonaggio(DBpg *dati, char *codice);
int aggiungiOggAPg(linkPers personaggio, int indexOgg, int maxOgg);
int rimuoviOggaPg(linkPers personaggio, int indexOgg, int maxOgg);
linkPers daCodiceAP(char *codice, linkPers head);
stats calcolaStats(DBogg listaOgg, linkPers personaggio);
stats bonusCumulativi(DBogg listaOgg, int* oggettiDelPg);
void stampaPersonaggio(char *codice, DBpg *datiPg, DBogg *datiOgg);

#endif
