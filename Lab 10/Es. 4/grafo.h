#ifndef ES__4_GRAFO_H
#define ES__4_GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30

typedef struct grafo_s *grafo;

grafo   grafo_init();
void    grafo_leggiFile(char *filename, grafo graph);
void    grafo_stampaGrafo(char *filename, grafo graph);
void    grafo_generaLista(grafo graph);
int     grafo_adjCoppie(char *id1, char *id2, char *id3, grafo graph, char strategy);
int     tab_toIndex(char *nome, grafo graph);
char*   tab_toId(int index, grafo graph);
void    tab_inserisciNew(char *nome, grafo graph);

#endif //ES__4_GRAFO_H
