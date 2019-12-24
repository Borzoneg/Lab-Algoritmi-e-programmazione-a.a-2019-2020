#include "equipArray.h"

typedef struct equipArray_s{
    int inUso;
    int *oggetti;
}equipArray_s;


// creatore
equipArray_t equipArray_init(){
    equipArray_t newEl = malloc(sizeof(equipArray_s));
    newEl->inUso = 0;
    newEl->oggetti = malloc(sizeof(int));
    return newEl;
}


//disruttore
void equipArray_free(equipArray_t equipArray){
    free(equipArray->oggetti);
    free(equipArray);
}


// quanti equipaggiamenti sono in us
int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}


// stampa tutti gli oggetti in equip
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i, j;
    for(i=0, j=0; j<equipArray->inUso; i++){
        printf("SLOT %d: ", i);
        invArray_printByIndex(fp, invArray,equipArray->oggetti[i]);
        j++;
    }
}


// aggiungi/rimuovi oggetto
stat_t equipArray_update(equipArray_t equipArray, invArray_t invArray, int *azione){
    int i, index, index2;
    stat_t statOgg;
    statOgg.hp = -1;
    printf("Si vuole aggiungere o rimuovere l'oggetto?\n0: aggiungi\t1:rimuovi\n");
    scanf("%d", azione);

    // rimozione
    if(*azione == 1){
        // caso in cui nessun oggetto sia presente nell'equip del pg
        if(equipArray->inUso == 0){
            printf("Nessun oggetto nell'equipaggiamento\n");
            return statOgg;
        }
        equipArray_print(stdout, equipArray, invArray);
        printf("Inserire indice dell'oggetto che si vuole rimuovere dal personaggio\n");
        scanf("%d", &index);
        // controllo sull'indice
        if(index>=equipArray->inUso){
            printf("Indice non valido\n");
            return statOgg;
        }
        // mi salvo l'oggetto che viene eliminato
        index2 = equipArray->oggetti[index];
        // scalo tutti gli oggetti successivi
        for(i=index; i<equipArray->inUso; i++)
            equipArray->oggetti[i] = equipArray->oggetti[i+1];
        equipArray->inUso--;
        // ritorno le stat dell'oggetto eliminato per aggiornare le stat del pg
        statOgg = inv_getStat(invArray_getByIndex(invArray, index2));
        return statOgg;
    }

    // caso in cui l'equip sia pieno
    if(equipArray->inUso >= EQUIP_SLOT){
        printf("Equipaggiamento pieno\n");
        return statOgg;
    }

    // stampo scelte, aggiorno numero di oggetti e aggiungo l'oggetto al fondo
    for(i=0; i < invArray_getN(invArray); i++) {
        printf("%d: ", i);
        invArray_printByIndex(stdout, invArray, i);
    }
    printf("Inserire indice dell'oggetto che si vuole aggiungere al personaggio\n");
    scanf("%d", &index);
    equipArray->inUso++;
    realloc(equipArray->oggetti, sizeof(int)*equipArray->inUso);
    equipArray->oggetti[equipArray->inUso-1] = index;
    statOgg = inv_getStat(invArray_getByIndex(invArray, index));
    // ritorno le stat dell'oggetto aggiunto per aggiornare le stat del pg
    return statOgg;
}


// torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray
int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->oggetti[index];
}