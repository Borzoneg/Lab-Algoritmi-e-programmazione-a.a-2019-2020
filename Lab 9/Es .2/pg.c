#include "pg.h"

// lettura da file
int pg_read(FILE *fp, pg_t *pgp){
    stat_t tmp;
    int n;
    // n è un intero di controllo per vedere se ha trovato tutti i campi
    if(fp == stdout)
        n = scanf("%s %s %s %d %d %d %d %d %d", pgp->cod, pgp->nome, pgp->classe,
                  &tmp.hp, &tmp.mp, &tmp.atk, &tmp.def, &tmp.mag, &tmp.spr);
    else
        n = fscanf(fp, "%s %s %s %d %d %d %d %d %d", pgp->cod, pgp->nome, pgp->classe,
                   &tmp.hp, &tmp.mp, &tmp.atk, &tmp.def, &tmp.mag, &tmp.spr);
    pgp->eq_stat = tmp;
    pgp->b_stat = tmp;
    pgp->equip = equipArray_init();
    return n;
}


// scrittura su file
void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    stat_t tmp = pgp ->eq_stat;
    fprintf(fp, "%s %s %s %d %d %d %d %d %d\n", pgp->cod, pgp->nome, pgp->classe,
            tmp.hp, tmp.mp, tmp.atk, tmp.def, tmp.mag, tmp.spr);
    fprintf(fp, "Equip:\n");
    equipArray_print(fp, pgp->equip, invArray);
}


// non essendo struct dinamica, pulisce chiamando il distruttire di equipArray
void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}


// aggunta/rimozione oggetto da personaggio con la funzione di equipArray.h
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    int azione;
    stat_t agg = equipArray_update(pgp->equip, invArray, &azione);
    pg_updateStat(pgp, agg, azione);
}


// update delle stat in seguito a aggiunta/rimozione oggetto
void pg_updateStat(pg_t *pgp, stat_t stat, int rimozione){
    if(!rimozione){
        pgp->eq_stat.hp += stat.hp;
        pgp->eq_stat.mp += stat.mp;
        pgp->eq_stat.atk += stat.atk;
        pgp->eq_stat.def += stat.def;
        pgp->eq_stat.mag += stat.mag;
        pgp->eq_stat.spr += stat.spr;
    }
    else{
        pgp->eq_stat.hp -= stat.hp;
        pgp->eq_stat.mp -= stat.mp;
        pgp->eq_stat.atk -= stat.atk;
        pgp->eq_stat.def -= stat.def;
        pgp->eq_stat.mag -= stat.mag;
        pgp->eq_stat.spr -= stat.spr;
    }
}
