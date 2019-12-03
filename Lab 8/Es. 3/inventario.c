#include "inventario.h"

void leggiFileOggetti(DBogg *dati, char *filename){
    char nome[N], tipo[N];
    int hp, mp, atk, def, mag, spr, i;
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File non trovato");
        exit(1);
    }
    fscanf(fp, "%d", &dati->nOgg);
    oggetto *oggetti = malloc(sizeof(oggetto) * dati->nOgg);
    for(i=0; i< dati->nOgg;i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", nome, tipo, &hp, &mp, &atk, &def, &mag, &spr);
        oggetti[i].nome = strdup(nome);
        oggetti[i].tipo = strdup(tipo);
        oggetti[i].bonusOgg.hp = hp;
        oggetti[i].bonusOgg.mp = mp;
        oggetti[i].bonusOgg.atk = atk;
        oggetti[i].bonusOgg.def = def;
        oggetti[i].bonusOgg.mag = mag;
        oggetti[i].bonusOgg.spr = spr;
    }
    dati->listaOgg = oggetti;
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