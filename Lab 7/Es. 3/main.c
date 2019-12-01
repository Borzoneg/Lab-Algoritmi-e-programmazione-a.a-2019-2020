#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50

typedef struct personaggio* linkPers;
typedef struct oggetto* linkOgg;

typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stats;

typedef struct{
    char* nome;
    char* tipo;
    stats bonusOgg;
}oggetto;

typedef struct personaggio{
    char* codice;
    char* nome;
    char* classe;
    linkOgg* equipPers;
    stats statPers;
    linkPers next;
}personaggio;

typedef struct{
    linkPers head;
    linkPers tail;
    int nPersonaggi;
}DB;

DB* aggiungiPersonaggio(DB *dati, linkPers newPg);
DB* leggiFilePg(DB *dati, char *filename);
oggetto* leggiFileOggetti(char *filename);

int main() {
    DB *dati = malloc(sizeof(DB));
    dati->head = NULL;
    dati->tail = NULL;
    dati = leggiFilePg(dati, "pg.txt");
    oggetto *listaOgg = leggiFileOggetti("inventario.txt");
    return 0;
}


DB *aggiungiPersonaggio(DB *dati,  linkPers newPg){
    linkPers i;
    if(dati->head==NULL){
        dati->head = newPg;
        dati->tail = newPg;
        dati->nPersonaggi++;
        return dati;
    }
    for(i=dati->head; i->next!=NULL; i=i->next);
    i->next = newPg;
    dati->tail = newPg;
    dati->nPersonaggi++;
    return dati;
}


DB *leggiFilePg(DB *dati, char *filename){
    FILE *fp  =fopen(filename, "r");
    if(fp == NULL){
        printf("File non trovato");
        exit(1);
    }
    char nome[N], classe[N], codice[N];
    int hp, mp, atk, def, mag, spr;
    while((fscanf(fp ,"%s %s %s %d %d %d %d %d %d", codice, nome, classe, &hp, &mp, &atk, &def, &mag, &spr)) ==9){
        linkPers asd = malloc(sizeof(personaggio));
        asd->codice = strdup(codice);
        asd->nome = strdup(nome);
        asd->classe =strdup(classe);
        asd->statPers.hp = hp;
        asd->statPers.mp = mp;
        asd->statPers.atk = atk;
        asd->statPers.def = def;
        asd->statPers.mag = mag;
        asd->statPers.spr = spr;
        asd->equipPers = NULL;
        asd->next = NULL;
        dati = aggiungiPersonaggio(dati, asd);
    }
    fclose(fp);
    return dati;
}


oggetto* leggiFileOggetti(char *filename){
    char nome[N], tipo[N];
    int hp, mp, atk, def, mag, spr, nOgg, i;
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File non trovato");
        exit(1);
    }
    fscanf(fp, "%d", &nOgg);
    oggetto *listOgg = malloc(sizeof(oggetto)* nOgg);
    for(i=0; i<nOgg;i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", nome, tipo, &hp, &mp, &atk, &def, &mag, &spr);
        listOgg[i].nome = strdup(nome);
        listOgg[i].tipo = strdup(tipo);
        listOgg[i].bonusOgg.hp = hp;
        listOgg[i].bonusOgg.mp = mp;
        listOgg[i].bonusOgg.atk = atk;
        listOgg[i].bonusOgg.def = def;
        listOgg[i].bonusOgg.mag = mag;
        listOgg[i].bonusOgg.spr = spr;
    }
    return listOgg;
}
