#include <stdio.h>
#include "grafo.h"
// TODO:
//          -individuazione di tutti gli insiemi di archi di cardinalità minima la cui rimozione renda il grafo originale un DAG
//          -costruzione  di  un  DAG  rimuovendo,  tra tutti  gli  insiemi di  archi generati al  passo  precedente,
//           quelli dell’insieme a peso massimo. Il peso di un insieme di archi è definito come la somma dei pesi
//           degli archi in esso contenuti
//          -calcolo delle distanze massime da ogni nodo sorgente verso ogni nododel DAG costruito al passo precedente
//          (1) provare a fare visita in profondità, un dag non ha archi back in una visita in profondità
int main() {
    grafo G = grafo_init();
    grafo_leggiFile("grafo1.txt", G);

    return 0;
}
