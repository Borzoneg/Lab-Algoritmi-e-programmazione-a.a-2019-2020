// START:   16:30
// FINE:    17:30
// ho nrig*2 possibili caselle da piazzare in ordine diverso, quindi uso le disposizioni semplici poiché non si ripetono
// i valori.
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
int disposizioniSempl(datiBase base, tubi *dati, int nc, int nr, casella **bestSol);
int contaVal(casella **sol, tubi *dati, int nc, int nr, int nTubi);
casella *generaListaCaselle(int nrig);

int main() {
    int nrig, i, j, maxPoints, nr, nc, caselleFisse = 0, postiLiberi;
    FILE *fp = fopen("tiles.txt", "r");
    FILE *fd = fopen("board.txt", "r");
    // lettura del file delle caselle
    fscanf(fp, "%d", &nrig);
    fscanf(fp, "\n");
    casella* listaCaselle = generaListaCaselle(nrig);
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
    casella** bestSol = malloc(sizeof(casella)*nr);
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
    int *mark = malloc(sizeof(int)*postiLiberi);
    for(i=0; i<postiLiberi; i++)
        mark[i] = 0;

//    for(i=0; i<3; i++){
//        for(j=0; j<3; j++)
//            printf(" %d %d", tabella[i][j].indice, tabella[i][j].ruotata);
//        printf("\n");
//    }
    casella *sol = malloc(sizeof(casella)*postiLiberi);
    datiBase base;
    base.pos = 0;
    base.sol = sol;
    base.val = listaCaselle;
    base.mark = mark;
    base.maxPoints = 0;
    base.n = nrig*2;
    base.k = postiLiberi;
    base.maxPoints = disposizioniSempl(base, dati, nc, nr, bestSol);
    printf("Massimo punti: %d", base.maxPoints);
    return 0;
}


int trovaValMax(char *filename1, char *filename2);


int disposizioniSempl(datiBase base, tubi *dati, int nc, int nr, casella **bestSol){
    int i, valLoc, r, c;
    if(base.pos >= base.k){
        for(i=0; i<base.k;i++){
            setbuf(stdout, 0);
            printf("%d %d\t", base.sol[i].indice, base.sol[i].ruotata);
        }
        setbuf(stdout, 0);
        printf("\n");
        //valLoc = contaVal(sol, dati, nc, nr, n/2);
//        if(valLoc > maxPoints)
//            maxPoints = valLoc;
        return base.maxPoints+1;
    }
    for(i=0; i<base.n; i++){
        if(!base.mark[i]){
            base.mark[i] = 1;
            base.sol[i].indice = base.val[i].indice;
            base.sol[i].ruotata = base.val[i].ruotata;
            base.pos++;
            base.maxPoints = disposizioniSempl(base, dati, nc, nr, bestSol);
            base.mark[i] = 0;
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

int contaVal(casella **sol, tubi *dati, int nc, int nr, int nTubi){
    int i, j, lineaOk = 1, indiceTubo, indiceTuboDopo, punti = 0;
    // conteggio dei punti per righe
    for(i=0; i<nr; i++){
        for(j=0; lineaOk && j<nc-1; j++){
            indiceTubo = sol[i][j].indice + nTubi * sol[i][j].ruotata;
            indiceTuboDopo = sol[i][j+1].indice + nTubi * sol[i][j+1].ruotata;
            if(dati[indiceTubo].coloreT1 == dati[indiceTuboDopo].coloreT1) {
                punti += dati[indiceTubo].valoreT1;
                if(j==nc-2)
                    punti += dati[indiceTuboDopo].valoreT1;
            }
            else
                lineaOk = 0;
        }
    }
    // conteggio dei punti per colonne
    for(i=0; i<nc; i++){
        for(j=0; lineaOk && j<nr-1; j++){
            indiceTubo = sol[j][i].indice + nTubi * sol[j][i].ruotata;
            indiceTuboDopo = sol[j+1][i].indice + nTubi * sol[j+1][i].ruotata;
            if(dati[indiceTubo].coloreT2 == dati[indiceTuboDopo].coloreT2) {
                punti += dati[indiceTubo].valoreT2;
                if(j==nr-2)
                    punti += dati[indiceTuboDopo].valoreT2;
            }
            else
                lineaOk = 0;

        }
    }
    return punti;
}

