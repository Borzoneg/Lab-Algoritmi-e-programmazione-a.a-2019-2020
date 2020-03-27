#include "personaggio.h"

void aggiungiPersonaggio(DBpg *dati, linkPers newPg){
    linkPers i;
    if(dati->head==NULL){
        newPg->next = NULL;
        dati->head = newPg;
        dati->tail = newPg;
        dati->nPersonaggi++;
        return;
    }
    for(i=dati->head; i->next!=NULL; i=i->next);
    i->next = newPg;
    dati->tail = newPg;
    dati->nPersonaggi++;
}


int eliminaPersonaggio(DBpg *dati, char *codice){
    linkPers i, tmp = NULL;
    if(!strcmp(dati->head->codice, codice)){
        if(dati->head == dati->tail)
            dati->tail = NULL;
        tmp = dati->head;
        dati->head = dati->head->next;
        dati->nPersonaggi--;
        tmp->next = NULL;
        free(tmp->codice);
        free(tmp->nome);
        free(tmp->classe);
        free(tmp);
        return 1;
    }

    for(i=dati->head; i->next!=NULL; i=i->next){
        if(!(strcmp(i->next->codice, codice))){
            if(dati->tail == i->next)
                dati->tail = i;
            tmp = i->next;
            i->next = i->next->next;
            tmp->next = NULL;
            dati->nPersonaggi--;
            free(tmp->codice);
            free(tmp->nome);
            free(tmp->classe);
            free(tmp);
            return 1;
        }
    }
    return 0;
}


void leggiFilePg(DBpg *dati, char *filename){
    FILE *fp  =fopen(filename, "r");
    if(fp == NULL){
        printf("File non trovato");
        exit(1);
    }
    char nome[N], classe[N], codice[N];
    int hp, mp, atk, def, mag, spr;
    while((fscanf(fp ,"%s %s %s %d %d %d %d %d %d", codice, nome, classe, &hp, &mp, &atk, &def, &mag, &spr)) ==9){
        linkPers newEl = malloc(sizeof(personaggio));
        newEl->codice = strdup(codice);
        newEl->nome = strdup(nome);
        newEl->classe =strdup(classe);
        newEl->statPers.hp = hp;
        newEl->statPers.mp = mp;
        newEl->statPers.atk = atk;
        newEl->statPers.def = def;
        newEl->statPers.mag = mag;
        newEl->statPers.spr = spr;
        newEl->equipPers.indiciOgg = NULL;
        newEl->equipPers.inUso = 0;
        newEl->next = NULL;
        aggiungiPersonaggio(dati, newEl);
    }
    fclose(fp);
}


int aggiungiOggAPg(linkPers personaggio, int indexOgg, int maxOgg){
    int i;
    if(personaggio == NULL || indexOgg < 0)
        return 0;
    if(personaggio->equipPers.indiciOgg==NULL){
        personaggio->equipPers.indiciOgg = malloc(sizeof(int)*maxOgg);
        for(i=0; i<maxOgg; i++)
            personaggio->equipPers.indiciOgg[i] = -1;
        personaggio->equipPers.inUso = 1;
    }
    for(i=0; personaggio->equipPers.indiciOgg[i] !=-1 && i<maxOgg; i++);
    if(i>=maxOgg)
        return 0;
    personaggio->equipPers.indiciOgg[i] = indexOgg;
    return 1;
}


int rimuoviOggaPg(linkPers personaggio, int indexOgg, int maxOgg){
    int i;
    if(personaggio==NULL || indexOgg < 0)
        return 0;
    if(personaggio->equipPers.indiciOgg==NULL)
        return 0;
    for(i=0;(indexOgg != personaggio->equipPers.indiciOgg[i]) && i<maxOgg; i++);
    if(i>=maxOgg)
        return 0;
    personaggio->equipPers.indiciOgg[i] = -1;
    return 1;
}


stats calcolaStats(DBogg listaOgg, linkPers personaggio){
    int i;
    stats finali;
    if(personaggio==NULL) {
        finali.hp=0;
        finali.mp=0;
        finali.atk=0;
        finali.def=0;
        finali.mag=0;
        finali.spr=0;
        return finali;
    }
    finali = bonusCumulativi(listaOgg, personaggio->equipPers.indiciOgg);
    finali.hp += personaggio->statPers.hp;
    finali.mp += personaggio->statPers.mp;
    finali.atk += personaggio->statPers.atk;
    finali.def += personaggio->statPers.def;
    finali.mag += personaggio->statPers.mag;
    finali.spr += personaggio->statPers.spr;
    return finali;
}


linkPers daCodiceAP(char *codice, linkPers head){
    linkPers i = NULL;
    for(i=head; i!=NULL; i=i->next) {
        if(!strcmp(codice, i->codice))
            return i;
    }
    return i;
}


stats bonusCumulativi(DBogg listaOgg, int* oggettiDelPg){
    int i;
    stats bonusC;
    bonusC.hp = 0;
    bonusC.mp = 0;
    bonusC.atk = 0;
    bonusC.def = 0;
    bonusC.mag = 0;
    bonusC.spr = 0;
    if(oggettiDelPg == NULL)
        return bonusC;
    for(i=0; oggettiDelPg[i]>=0 && i<listaOgg.maxOgg; i++) {
        bonusC.hp += listaOgg.listaOgg[oggettiDelPg[i]].bonusOgg.hp;
        bonusC.mp += listaOgg.listaOgg[oggettiDelPg[i]].bonusOgg.mp;
        bonusC.atk += listaOgg.listaOgg[oggettiDelPg[i]].bonusOgg.atk;
        bonusC.def += listaOgg.listaOgg[oggettiDelPg[i]].bonusOgg.def;
        bonusC.mag += listaOgg.listaOgg[oggettiDelPg[i]].bonusOgg.mag;
        bonusC.spr += listaOgg.listaOgg[oggettiDelPg[i]].bonusOgg.spr;
    }
    return bonusC;

}


void stampaPersonaggio(char *codice, DBpg *datiPg, DBogg *datiOgg){
    int i, hp, mp, atk, def, mag, spr;
    linkPers el = daCodiceAP(codice, datiPg->head);
    if(el==NULL){
        printf("Peronaggio non esistente\n");
        return;
    }
    stats sF = calcolaStats(*datiOgg, el);
    hp = sF.hp < 1 ? 1 : sF.hp;
    mp = sF.mp < 1 ? 1 : sF.mp;
    atk = sF.atk < 1 ? 1 : sF.atk;
    def = sF.def < 1 ? 1 : sF.def;
    mag = sF.mag < 1 ? 1 : sF.mag;
    spr = sF.spr < 1 ? 1 : sF.spr;

    printf("%s %s %s %d %d %d %d %d %d\n",
            el->codice, el->nome, el->classe, hp, mp, atk, def, mag, spr);
    printf("Equipaggiamento:");
    if(el->equipPers.inUso){
        for(i=0; i < datiOgg->maxOgg; i++){
            if(el->equipPers.indiciOgg[i] >= 0)
                stampaOgg(datiOgg->listaOgg[el->equipPers.indiciOgg[i]].nome, *datiOgg);
        }
    }
    printf("\n");
}


void liberaDBpg(DBpg *dati){
    linkPers i, tmp;
    for(i=dati->head; i!=NULL; i = i->next, free(tmp)){
        free(i->nome);
        free(i->classe);
        free(i->codice);
        free(i->equipPers.indiciOgg);
        tmp = i;
    }
    free(dati);
}