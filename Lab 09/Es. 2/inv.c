#include "inv.h"

// input delle statistiche
void stat_read(FILE *fp, stat_t *statp){
    if(fp == stdout)
        scanf( "%d %d %d %d %d %d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr);
    else
        fscanf(fp,"%d %d %d %d %d %d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr);
}


// output delle statistiche
void stat_print(FILE *fp, stat_t *statp, int soglia){
    int hp, mp, atk, def, mag, spr;
    // espressioni condizionali per cambio di variabili
    hp = (statp->hp < MIN_STAT? MIN_STAT : statp->hp);
    mp = (statp->mp < MIN_STAT? MIN_STAT : statp->mp);
    atk = (statp->atk < MIN_STAT? MIN_STAT : statp->atk);
    def = (statp->def < MIN_STAT? MIN_STAT : statp->def);
    mag = (statp->mag < MIN_STAT? MIN_STAT : statp->mag);
    spr = (statp->spr < MIN_STAT? MIN_STAT : statp->spr);
    fprintf(fp,"%d %d %d %d %d %d\n", hp, mp, atk, def, mag, spr);
}


// input di oggetto da file
void inv_read(FILE *fp, inv_t *invp){
    stat_t tmp;
    if(fp == stdout)
        scanf( "%s %s %d %d %d %d %d %d", invp->nome, invp->tipo,
              &tmp.hp, &tmp.mp, &tmp.atk, &tmp.def, &tmp.mag, &tmp.spr);
    else
        fscanf(fp, "%s %s %d %d %d %d %d %d", invp->nome, invp->tipo,
           &tmp.hp, &tmp.mp, &tmp.atk, &tmp.def, &tmp.mag, &tmp.spr);
    invp->stat = tmp;
}


// output di oggetto da file
void inv_print(FILE *fp, inv_t *invp){
    stat_t tmp;
    tmp = invp->stat;
    fprintf(fp, "%s %s %d %d %d %d %d %d\n", invp->nome, invp->tipo,
            tmp.hp, tmp.mp, tmp.atk, tmp.def, tmp.mag, tmp.spr);
}


// ritorna il campo stat di un oggetto dell'inventario
stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}
