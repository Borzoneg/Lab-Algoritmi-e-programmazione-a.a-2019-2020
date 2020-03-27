#include "pgList.h"

typedef struct node *link;
typedef struct node{
    pg_t item;
    link next;
}node;
typedef struct  pgList_s{
    link head;
    int nPg;
    link tail;
}pgList_s;

//creatore
pgList_t pgList_init(){
    pgList_t pgList = malloc(sizeof(pgList_s));
    pgList->head = malloc(sizeof(node));
    pgList->tail = malloc(sizeof(node));
    pgList->nPg = 0;
    return pgList;
}


// distruttore
void pgList_free(pgList_t pgList){
    link i;
    for(i=pgList->head; i!=NULL; i=i->next){
        pg_clean(&i->item);
    }
    free(pgList);
}


// lettura da file
void pgList_read(FILE *fp, pgList_t pgList){
    link i;
    link newEl;
    if(pgList->nPg == 0){
        pg_read(fp, &pgList->head->item);
        pgList->head->next = NULL;
        pgList->nPg = 1;
        pgList->tail = pgList->head;
    }
    // mi porto al fondo della lista
    newEl = malloc(sizeof(node));
    for(i=pgList->tail; pg_read(fp, &newEl->item) == 9; i=i->next, newEl = malloc(sizeof(node))){
        newEl->next = NULL;
        pgList->nPg++;
        i->next = newEl;
        pgList->tail = newEl;
    }

}


// scrittura su file
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link i;
    for(i=pgList->head; i!=NULL; i=i->next)
        pg_print(stdout, &i->item, invArray);
}


// inserimento di un nuovo personaggio
void pgList_insert(pgList_t pgList, pg_t pg){
    link newNode = malloc(sizeof(node));
    newNode->next = NULL;
    newNode->item = pg;
    pgList->tail->next = newNode;
    pgList->tail = newNode;
    pgList->nPg++;
}


// cancellazione con rimozione
void pgList_remove(pgList_t pgList, char* cod){
    link i, tmp;
    if(!strcmp(pgList->head->item.cod, cod)){
        tmp = pgList->head;
        pg_clean(&pgList->head->item);
        free(pgList->head);
        pgList->head = tmp->next;
        return;
    }
    for(i=pgList->head; i->next!=NULL; i=i->next){
        if(!strcmp(cod, i->next->item.cod)){
            tmp = i->next;
            i->next = tmp->next;
            pg_clean(&tmp->item);
            free(tmp);
            return;
        }
    }
}


// ricerca per codice, ritornando il puntatore
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link i, tmp;
    if(!strcmp(pgList->head->item.cod, cod)){
        return &pgList->head->item;
    }
    for(i=pgList->head; i!=NULL; i=i->next){
        if(!strcmp(cod, i->item.cod)){
            return &i->item;
        }
    }
    return NULL;
}