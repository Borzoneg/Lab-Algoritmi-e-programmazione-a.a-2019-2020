#include "personaggio.h"

#define S 15
typedef enum{aggiungi, rimuovi, importaPg, importaOgg, addOggApg, rimOggApg, stampapg, stampaogg,fine}menu;

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
    leggiFilePg(datiPg, "pg.txt");
    leggiFileOggetti(datiOgg, "inventario.txt");
    /**************************** FINE TEST ****************************/

    while(continua){
        printf("aggiungi: aggiungi personaggio\n"
               "rimuovi: rimuovi personaggio\n"
               "importapg: importa una lista di personaggi da file\n"
               "importaogg: importa una lista di oggetti da file\n"
               "aggiungiogg: aggiungi un oggetto a un personaggio\n"
               "rimuoviogg: rimuovi un oggetto a un personaggio\n"
               "stampapg: stampa i dati di un personaggio\n"
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
                if(eliminaPersonaggio(datiPg, dato))
                    printf("%s e' stato eliminato", dato);
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
            case stampapg:
                printf("Inserire il codice del personaggio\n");
                scanf("%s", dato);
                stampaPersonaggio(dato, datiPg, datiOgg);
                break;
            case stampaogg:
                printf("Inserire nome dell'oggetto\n");
                scanf("%s", dato);
                stampaOgg(dato, *datiOgg);
                break;
            case fine:
                // TODO: free di tutti i dati allocati dinamicamene attraverso funzioni
                continua = 0;
                break;
            default:
                printf("Comando non riconosciuto, riprovare\n");
        }
    }
    return 0;
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
    if(!strcmp(comando, "stampapg"))
        return 6;
    if(!strcmp(comando, "stampaogg"))
        return 7;
    if(!strcmp(comando, "fine"))
        return 8;
    return -1;
}