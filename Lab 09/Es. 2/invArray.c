#include "invArray.h"

typedef struct invArray_s{
    int nmax;
    int n;
    inv_t *invArr;
}invArray_s;

// creatore
invArray_t invArray_init(){
    invArray_t newEl = malloc(sizeof(invArray_s));
    newEl->nmax = 0;
    newEl->n = 0;
    newEl->invArr = malloc(sizeof(inv_t));
    return newEl;

}


// distruttore
void invArray_free(invArray_t invArray){
    free(invArray->invArr);
}


// lettura da file
void invArray_read(FILE *fp, invArray_t invArray){
    int i, nrig;
    fscanf(fp, "%d", &nrig);
    invArray->n += nrig;
    invArray->nmax += nrig;
    realloc(invArray->invArr, invArray->nmax);
    for(i=0; i<nrig; i++){
        inv_read(fp, &invArray->invArr[i]);
    }
}


// stampa della lista su file
void invArray_print(FILE *fp, invArray_t invArray){
    int i;
    for(i=0; i<invArray->n; i++)
        inv_print(fp, &invArray->invArr[i]);
}


// stampa un unico oggetto selezionato da indice (nel vettore)
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, &invArray->invArr[index]);
}


// ritorna puntatore a oggetto selezionato da indice (nel vettore)
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &invArray->invArr[index];
}


// ritorna indice (nel vettore) a oggetto selezionato da nome
int invArray_searchByName(invArray_t invArray, char *name){
    int i;
    for(i=0; i<invArray->n; i++){
        if(!strcmp(invArray->invArr[i].nome, name))
            return i;
    }
    return -1;
}


// ritorna il numero di oggetti nel vettore
int invArray_getN(invArray_t invArray){
    return invArray->n;
}