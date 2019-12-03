// TODO:
//            -La cancellazione è da fare con estrazione? Equivalente
//            -Controllo errori su aggiunta oggeti senza lista o rimoioni senza inizializzazione dei database

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50
#define S 15
#define M 8

typedef struct personaggio* linkPers;

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

typedef struct {
    oggetto* listaOgg;
    int nOgg;
    int maxOgg;
}DBogg;


typedef enum{aggiungi, rimuovi, importaPg, importaOgg, addOggApg, rimOggApg, calcola, fine}menu;

DBpg* aggiungiPersonaggio(DBpg *dati, linkPers newPg);
DBpg* leggiFilePg(DBpg *dati, char *filename);
linkPers eliminaPersonaggio(DBpg *dati, char *codice);
void leggiFileOggetti(DBogg *dati, char *filename);
int aggiungiOggAPg(linkPers personaggio, int indexOgg, int maxOgg);
int rimuoviOggaPg(linkPers personaggio, int indexOgg, int maxOgg);
linkPers daCodiceAP(char *codice, linkPers head);
int nome2IndOgg(char *nome, DBogg dati);
stats calcolaStats(DBogg listaOgg, linkPers personaggio);
stats bonusCumulativi(DBogg listaOgg, int* oggettiDelPg);
int leggiComando(char *comando);

int main() {
    int continua = 1, i;
    menu scelta;
    linkPers elemento, tmp;
    stats caratt;
    DBpg *datiPg = malloc(sizeof(DBpg));
    DBogg *datiOgg = malloc(sizeof(DBogg));
    char comando[S], dato[S], dato1[S], dato2[S];

    datiPg->head = NULL;
    datiPg->tail = NULL;
    datiPg->nPersonaggi = 0;
    datiOgg->nOgg = 0;
    datiOgg->listaOgg = NULL;
    datiOgg->maxOgg = M;

    /**************************** INIZIO TEST ****************************/
//    datiPg = leggiFilePg(datiPg, "pg.txt");
//    leggiFileOggetti("inventario.txt", datiOgg);
//    eliminaPersonaggio(datiPg, "PG01");
//    linkPers cane = daCodiceAP("PG02", datiPg->head);
//    int oggetto = nome2IndOgg("scudodiscudi", *datiOgg);
//    aggiungiOggAPg(cane, oggetto, datiOgg->maxOgg);
//    aggiungiOggAPg(cane, 0, datiOgg->maxOgg);
//    rimuoviOggaPg(cane->next, oggetto, datiOgg->maxOgg);
//    stats a = calcolaStats(*datiOgg, cane);
    /**************************** FINE TEST ****************************/

    while(continua){
        printf("Aggiungi: aggiungi personaggio\n"
               "Rimuovi: rimuovi personaggio\n"
               "importaPg: importa una lista di personaggi da file\n"
               "importaOgg: importa una lista di oggetti da file\n"
               "aggiungiOgg: aggiungi un oggetto a un personaggio\n"
               "rimuoviOgg: rimuovi un oggetto a un personaggio\n"
               "calcola: calcola le statistiche di un personaggio tenendo conto del suo equipaggiamento\n"
               "fine: per uscire\n");
        scanf("%s", comando);
        scelta = leggiComando(comando);
        switch(scelta){
            case aggiungi:
                elemento = malloc(sizeof(personaggio));
                elemento->next = NULL;
                elemento->equipPers.indiciOgg = NULL;
                elemento->equipPers.inUso = 0;
                printf("Inserire i campi del personaggio nel formato:\n"
                       "Codice Nome Classe hp mp atk def mag spr\n");
                scanf("%s %s %s %d %d %d %d %d %d", dato, dato1, dato2,
                        &elemento->statPers.hp, &elemento->statPers.mp, &elemento->statPers.atk,
                      &elemento->statPers.def, &elemento->statPers.mag, &elemento->statPers.spr);
                elemento->codice = strdup(dato);
                elemento->nome = strdup(dato1);
                elemento->classe = strdup(dato2);
                aggiungiPersonaggio(datiPg, elemento);
                break;
            case rimuovi:
                printf("Inserire il codice del pg che si vuole eliminare\n");
                scanf("%s", dato);
                elemento = eliminaPersonaggio(datiPg, dato);
                if(elemento!=NULL)
                    printf("%s e' stato eliminato", elemento->nome);
                else printf("L'elemento non e' presente in lista\n");
                break;
            case importaPg:
                printf("Inserire il nome del file che si vuole importare\n");
                scanf("%s", dato);
                leggiFilePg(datiPg, dato);
                if(datiPg->head==NULL)
                    printf("L'inizializzazione non e' riuscita\n");
                break;
            case importaOgg:
                printf("Inserire il nome del file che si vuole importare\n");
                scanf("%s", dato);
                leggiFileOggetti(datiOgg, dato);
                if(datiOgg->listaOgg==NULL)
                    printf("L'inizializzazione non e' riuscita\n");
                break;
            case addOggApg:
                printf("Inserire il nome dell'oggetto e il codice del personaggio\n");
                scanf("%s %s", dato, dato1);
                if(!aggiungiOggAPg(daCodiceAP(dato1, datiPg->head), nome2IndOgg(dato, *datiOgg), datiOgg->maxOgg))
                    printf("Oggetto non presente nell'inventario, equipaggiamento del pg pieno o pg inesistente\n");
                break;
            case rimOggApg:
                printf("Inserire il nome dell'oggetto e il codice del personaggio\n");
                scanf("%s %s", dato, dato1);
                if(!rimuoviOggaPg(daCodiceAP(dato1, datiPg->head), nome2IndOgg(dato, *datiOgg), datiOgg->maxOgg))
                    printf("Oggetto non presente nell'equipaggiamento o pg inesistente\n");
                break;
            case calcola:
                printf("Inserire il codice del personaggio\n");
                scanf("%s", dato);
                caratt = calcolaStats(*datiOgg, daCodiceAP(dato, datiPg->head));
                if(caratt.hp){
                    printf("Le statistiche del personaggio sono\n"
                           "Hp: %d Mp: %d Atk: %d Def: %d Mag: %d Spr: %d\n",
                           caratt.hp, caratt.mp, caratt.atk, caratt.def, caratt.mag, caratt.spr);
                }
                else
                    printf("Pg non presente in lista\n");
                break;
            case fine:
                // free dei dati interni degli oggetti del vettore di struct
                for(i=0; i<datiOgg->nOgg; i++) {
                    free(datiOgg->listaOgg[i].nome);
                    free(datiOgg->listaOgg[i].tipo);
                }
                // free di ogni elemento della lista di personaggi
                for(elemento=datiPg->head; elemento!=NULL;){
                    free(elemento->nome);
                    free(elemento->codice);
                    free(elemento->classe);
                    free(elemento->equipPers.indiciOgg);
                    // per poter liberare anche elemento mi salvo prima il suo valore in tmp
                    tmp = elemento;
                    // elemento diventa il successivo
                    elemento = elemento->next;
                    // libero tmp che rappresenta il vecchio elemento a cui ho già liberato i campi interni
                    free(tmp);
                }
                free(datiOgg);
                free(datiPg);
                continua = 0;
                break;
            default:
                printf("Comando non riconosciuto, riprovare\n");
        }
    }
    return 0;
}


DBpg *aggiungiPersonaggio(DBpg *dati, linkPers newPg){
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


linkPers eliminaPersonaggio(DBpg *dati, char *codice){
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
        return tmp;
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
            return tmp;
        }
    }
    return tmp;
}


DBpg *leggiFilePg(DBpg *dati, char *filename){
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
        dati = aggiungiPersonaggio(dati, newEl);
    }
    fclose(fp);
    return dati;
}


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


stats bonusCumulativi(DBogg listaOgg, int* oggettiDelPg){
    int i;
    stats bonusC;
    bonusC.hp = 0;
    bonusC.mp = 0;
    bonusC.atk = 0;
    bonusC.def = 0;
    bonusC.mag = 0;
    bonusC.spr = 0;
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


int leggiComando(char *comando){
    if(!strcmp(comando, "aggiungi"))
        return 0;
    if(!strcmp(comando, "rimuovi"))
        return 1;
    if(!strcmp(comando, "importapg"))
        return 2;
    if(!strcmp(comando, "importaogg"))
        return 3;
    if(!strcmp(comando, "aggiungiogg"))
        return 4;
    if(!strcmp(comando, "rimuoviogg"))
        return 5;
    if(!strcmp(comando, "calcola"))
        return 6;
    if(!strcmp(comando, "fine"))
        return 7;
    return -1;
}