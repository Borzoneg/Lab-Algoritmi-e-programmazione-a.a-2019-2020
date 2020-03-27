#include "inventario.h"

void leggiFileOggetti(DBogg *dati, char *filename){
    char nome[N], tipo[N];
    int hp, mp, atk, def, mag, spr, i, a;
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File non trovato");
        exit(1);
    }
    fscanf(fp, "%d", &a);
    dati->nOgg += a;
    if(dati->listaOgg == NULL)
        dati->listaOgg = malloc(sizeof(oggetto) * dati->nOgg);
    else
        dati->listaOgg = realloc(dati->listaOgg, sizeof(oggetto) * dati->nOgg);
    for(i=dati->nOgg-a; i< dati->nOgg;i++) {
        fscanf(fp, "%s %s %d %d %d %d %d %d", nome, tipo, &hp, &mp, &atk, &def, &mag, &spr);
        dati->listaOgg[i].nome = strdup(nome);
        dati->listaOgg[i].tipo = strdup(tipo);
        dati->listaOgg[i].bonusOgg.hp = hp;
        dati->listaOgg[i].bonusOgg.mp = mp;
        dati->listaOgg[i].bonusOgg.atk = atk;
        dati->listaOgg[i].bonusOgg.def = def;
        dati->listaOgg[i].bonusOgg.mag = mag;
        dati->listaOgg[i].bonusOgg.spr = spr;
    }
}


int nome2IndOgg(char *nome, DBogg dati){
    int i;
    // Trovo l'oggetto dal nome giust, quando lo trovo ritorno l'indice a cui si trova
    for(i=0; i<dati.nOgg; i++){
        if(!strcmp(nome, dati.listaOgg[i].nome))
            return i;
    }
    // altrimenti ritorno -1 come segnale che l'oggetto non esiste
    return -1;
}


void stampaOgg(char *nome, DBogg dati){
    int index = nome2IndOgg(nome, dati);
    if(index<0){
        printf("Oggetto non presente\n");
        return;     
    }
    stats b = dati.listaOgg[index].bonusOgg;
    printf("%s %s %d %d %d %d %d %d\n",
            dati.listaOgg[index].nome, dati.listaOgg[index].tipo, b.hp, b.mp, b.atk, b.def, b.mag, b.spr);
}


void liberaDBogg(DBogg * dati){
    int i;
    for(i=0; i<dati->nOgg; i++){
        free(dati->listaOgg[i].nome);
        free(dati->listaOgg[i].tipo);
    }
    free(dati->listaOgg);
    free(dati);
}