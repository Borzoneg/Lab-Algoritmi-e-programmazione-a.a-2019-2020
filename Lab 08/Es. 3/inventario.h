//
// Created by borzo on 05/12/2019.
//

#ifndef ES__3_INVENTARIO_H
#define ES__3_INVENTARIO_H
// massimo numero di oggetti per personaggio
#define M 8
// lungheza max stringhe nome, codice, ecc...
#define N 50
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

typedef struct {
    oggetto* listaOgg;
    int nOgg;
    int maxOgg;
}DBogg;

void leggiFileOggetti(DBogg *dati, char *filename);
int nome2IndOgg(char *nome, DBogg dati);
void stampaOgg(char *nome, DBogg dati);
void liberaDBogg(DBogg * dati);

#endif //ES__3_INVENTARIO_H
