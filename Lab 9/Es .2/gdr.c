#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pgList.h"
#include "invArray.h"
#include "pg.h"
#define N_SCELTE 7
#define DBG 0

enum { falso, vero };
typedef int bool;

void stampaMenu(char *scelte[], int *selezione){
  int i=0;
  printf("\nMENU'\n");
  for(i=0;i<N_SCELTE;i++)
    printf("%2d > %s\n",i,scelte[i]);
  scanf(" %d",selezione);
}

int main(int argc, char **argv) {
    char *scelte[] = {
            "Uscita",
            "Stampa personaggi",
            "Stampa inventario",
            "Cerca personaggio",
            "Aggiungi personaggio",
            "Elimina personaggio",
            "Modifica equip"
    };

    char codiceRicerca[LEN];
    int selezione;
    FILE *fin;
    bool fineProgramma;

    FILE *inventario = fopen("inventario.txt", "r");
    FILE *personaggi = fopen("pg.txt", "r");
    invArray_t inv = invArray_init();
    invArray_read(inventario, inv);
    pgList_t lista = pgList_init();
    pgList_read(personaggi, lista);
    //pgList_print(stdout, lista, inv);

    pg_t *pgp, pg;

#if DBG
    pgList_print(stdout, pgList);
#endif /* DBG */

#if DBG
    invArray_print(stdout, invArray);
#endif /* DBG */

    fineProgramma = falso;

    do {
        stampaMenu(scelte, &selezione);
        switch(selezione){

            case 0: {
                fineProgramma = vero;
            } break;

            case 1: {
                pgList_print(stdout, lista, inv);
            } break;

            case 2: {
                invArray_print(stdout, inv);
            } break;

            case 3: {
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                pgp = pgList_searchByCode(lista, codiceRicerca);
                if (pgp!=NULL) {
                    pg_print(stdout, pgp, inv);
                }
            } break;

            case 4: {
                printf("Cod Nome Classe HP MP ATK DEF MAG SPR: ");
                if (pg_read(stdin, &pg) != 0) {
                    pgList_insert(lista, pg);
                }
            } break;

            case 5: {
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                pgList_remove(lista, codiceRicerca);
            } break;

            case 6: {
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                pgp = pgList_searchByCode(lista, codiceRicerca);
                if (pgp!=NULL) {
                    pg_updateEquip(pgp, inv);
                }
            } break;

            default:{
                printf("Scelta non valida\n");
            } break;
        }
    } while(!fineProgramma);

    pgList_free(lista);
    invArray_free(inv);

    return 0;
}