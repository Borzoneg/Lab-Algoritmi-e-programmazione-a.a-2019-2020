
#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int valoreT1;
    char coloreT1;
    int valoreT2;
    char coloreT2;
}tubi;

typedef struct{
    int indice;
    int ruotata;
}casella;


typedef struct{
    casella *val;
    casella *sol;
    int *mark;
    int n, k, pos;
    int maxPoints;
}datiBase;

int trovaValMax(char *filename1, char *filename2);
int disposizioniSempl(datiBase base, tubi *dati, int nc, int nr, casella *bestSol, casella **board);
int contaVal(casella *sol, tubi *dati, int nc, int nr, int nTubi, casella **boardIniz, int k);
casella *generaListaCaselle(int nrig);

int main() {
    trovaValMax("tiles.txt", "board.txt");
    return 0;
}


int trovaValMax(char *filename1, char *filename2){

    int nrig, i, j, maxPoints, nr, nc, caselleFisse = 0, postiLiberi;
    FILE *fp = fopen(filename1, "r");
    FILE *fd = fopen(filename2, "r");
    // lettura del file delle caselle
    fscanf(fp, "%d", &nrig);
    fscanf(fp, "\n");
    casella* listaCaselle = generaListaCaselle(nrig);
    casella* bestSol = malloc(sizeof(casella)*nrig*2);
    tubi *dati = malloc(sizeof(tubi) * nrig * 2);
    for(i=0; i<nrig; i++){
        fscanf(fp,"%c %d %c %d\n", &dati[i].coloreT1, &dati[i].valoreT1, &dati[i].coloreT2, &dati[i].valoreT2);
        // per poter contare più semplicemente dopo, mi genero già anche i tubi girati e li metto nell struttura dati
        dati[i+nrig].coloreT1 = dati[i].coloreT2;
        dati[i+nrig].valoreT1 = dati[i].valoreT2;
        dati[i+nrig].coloreT2 = dati[i].coloreT1;
        dati[i+nrig].valoreT2 = dati[i].valoreT1;
    }
    // lettura del file della board
    fscanf(fd, "%d %d", &nr, &nc);
    casella** tabella = malloc(sizeof(casella) * nr);

    for(i=0; i<nr; i++){
        tabella[i] = malloc(sizeof(casella) * nc);
        for(j=0; j<nc; j++){
            fscanf(fd, "%d/%d", &tabella[i][j].indice, &tabella[i][j].ruotata);
            if(tabella[i][j].indice != -1)
                caselleFisse++;
        }
    }
    fclose(fd);
    fclose(fp);
    // determino le posizioni da riempire su cui devo lavoare con le disposizioni
    postiLiberi = (nr * nc) - caselleFisse;
    int *mark = malloc(sizeof(int)*nrig*2);
    for(i=0; i<nrig*2; i++)
        mark[i] = 0;

    casella *sol = malloc(sizeof(casella)*postiLiberi);
    datiBase base;
    base.pos = 0;
    base.sol = sol;
    base.val = listaCaselle;
    base.mark = mark;
    base.maxPoints = 0;
    base.n = nrig*2;
    base.k = postiLiberi;
    base.maxPoints = disposizioniSempl(base, dati, nc, nr, bestSol, tabella);
    printf("Massimo punti: %d", base.maxPoints);
    printf("\nCon la soluzione: \n");

    for(i=0; i<postiLiberi; i++){
        printf("%d %d\n", bestSol[i].indice, bestSol[i].ruotata);
    }
//    casella * asd = malloc(sizeof(casella)*5);
//    asd[0].indice = 8;
//    asd[1].indice = 7;
//    asd[2].indice = 6;
//    asd[3].indice = 5;
//    asd[4].indice = 4;
//    asd[0].ruotata = 1;
//    asd[1].ruotata = 1;
//    asd[2].ruotata = 1;
//    asd[3].ruotata = 1;
//    asd[4].ruotata = 1;
//    printf("%d", contaVal(asd, dati, nc, nr, nrig, tabella, base.k));
    return base.maxPoints;

}

int disposizioniSempl(datiBase base, tubi *dati, int nc, int nr, casella *bestSol, casella **board){
    int i, valLoc = 0, r, c;
    if(base.pos >= base.k){
        valLoc = contaVal(base.sol, dati, nc, nr, (base.n)/2, board, base.k);
        if(valLoc > base.maxPoints) {
            base.maxPoints = valLoc;
            for(i = 0; i < base.k; i++)
                bestSol[i] = base.sol[i];
        }
        return base.maxPoints;
    }
    for(i=0; i<base.n; i++){
        if(!base.mark[i]){
            base.mark[i] = 1;
            base.sol[base.pos] = base.val[i];
            base.pos++;
            base.maxPoints = disposizioniSempl(base, dati, nc, nr, bestSol, board);
            base.mark[i] = 0;
            base.pos--;
        }
    }
    return base.maxPoints;
}


casella *generaListaCaselle(int nrig){
    int i;
    casella *dati = malloc(sizeof(casella)*nrig*2);
    for(i=0; i<nrig; i++){
        dati[i].indice = i;
        dati[i+nrig].indice = i;
        dati[i].ruotata = 0;
        dati[i+nrig].ruotata = 1;
    }
    return dati;
}


int contaVal(casella *sol, tubi *dati, int nc, int nr, int nTubi, casella **boardIniz, int k){
    int i, j, l, n, lineaOk, indiceTubo, indiceTuboDopo, punti = 0, puntiLin;
    casella boardAtt[nc][nr];
    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            boardAtt[i][j] = boardIniz[i][j];
    // riempie la boardIniz attuale con le caselle della soluzione
    for(l=0, n =0; n<k && l<(nr*nc); n++){
        i = l/nr;
        j = l%nc;
        while(boardAtt[i][j].indice != -1){
            l++;
            i = l/nr;
            j = l%nc;
        }
        boardAtt[i][j] = sol[n];
    }

    // conteggio dei punti per righe
    for(i=0 ; i<nr; i++){
        for(j=0, lineaOk=1, puntiLin=0; lineaOk && j<nc-1; j++){
            indiceTubo = boardAtt[i][j].indice + nTubi * boardAtt[i][j].ruotata;
            indiceTuboDopo = boardAtt[i][j + 1].indice + nTubi * boardAtt[i][j + 1].ruotata;
            if(dati[indiceTubo].coloreT1 == dati[indiceTuboDopo].coloreT1) {
                puntiLin += dati[indiceTubo].valoreT1;
                if(j==nc-2)
                    puntiLin += dati[indiceTuboDopo].valoreT1;
            }
            else{
                lineaOk = 0;
                puntiLin = 0;
            }
        }
        punti += puntiLin;
    }
    // conteggio dei punti per colonne
    for(i=0; i<nc; i++){
        for(j=0, lineaOk=1, puntiLin=0; lineaOk && j<nr-1; j++){
            indiceTubo = boardAtt[j][i].indice + nTubi * boardAtt[j][i].ruotata;
            indiceTuboDopo = boardAtt[j + 1][i].indice + nTubi * boardAtt[j + 1][i].ruotata;
            if(dati[indiceTubo].coloreT2 == dati[indiceTuboDopo].coloreT2) {
                puntiLin += dati[indiceTubo].valoreT2;
                if(j==nr-2)
                    puntiLin += dati[indiceTuboDopo].valoreT2;
            }
            else{
                lineaOk = 0;
                puntiLin = 0;
            }

        }
        punti += puntiLin;
    }

    return punti;
}

