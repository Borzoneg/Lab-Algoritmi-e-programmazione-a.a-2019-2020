#include "grafo.h"

typedef struct node * link;

typedef struct node{
    char id;
    int peso;
    link adj;
}node;

typedef struct tab_s{
    char * list;
    int n;
}tab_s;

typedef struct grafo_s{
    int V;
    int E;
    int **matrice;
    node *lista;
    tab_s simboli;
}grafo_s;


grafo grafo_init(){
    grafo graph = malloc(sizeof(grafo_s));
    graph->simboli.list = malloc(sizeof(char**));
    graph->simboli.n = 0;
    graph->V = 0;
    graph->E = 0;
    graph->matrice = NULL;
    graph->lista = NULL;
    return graph;
}


int **matrix_init(int v){
    int i, j, **matrix = malloc(sizeof(int)*v);
    for(i=0; i<v; i++){
        matrix[i] = malloc(sizeof(int)*v);
        for(j=0; j<v; j++)
            matrix[i][j] = 0;
            }
    return matrix;
}


void grafo_leggiFile(char *filename, grafo graph){
    int i, nrig = 0, peso, u, v;
    char id1, id2;
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d\n", &graph->V);
    graph->matrice = matrix_init(graph->V);

    for(i=0; i<graph->V; i++) {
        fscanf(fp, "%c\n", &id1);
        tab_inserisciNew(id1, graph);
    }
    while((fscanf(fp, "%c %c %d\n", &id1, &id2, &peso)) == 3){
        nrig++;
        u = tab_toIndex(id1, graph);
        v = tab_toIndex(id2, graph);
        graph->matrice[u][v] = peso;
    }
    graph->E = nrig;
}


int tab_toIndex(char nome, grafo graph){
    int i;
    for(i=0; i<graph->simboli.n; i++){
        if(nome == graph->simboli.list[i])
            return i;
    }
    return -1;
}


char tab_toId(int index, grafo graph){
    return graph->simboli.list[index];
}


void tab_inserisciNew(char nome, grafo graph){
    int i = 0, j, a;
    while((a = (nome - graph->simboli.list[i])) != 0 && i <graph->simboli.n)
        i++;
    if(i==graph->simboli.n){
        graph->simboli.n++;
        graph->simboli.list[i] = nome;
    }

}


void grafo_stampaGrafo(char *filename, grafo graph){
    int i, j;
    if(!strcmp("stdout", filename)) {
        for(i=0; i< graph->V; i++)
            printf("%d: %c\n", i, graph->simboli.list[i]);
        for(i = 0; i < graph->V; i++){
            printf("%c: ", tab_toId(i, graph));
            for(j = 0; j < graph->V; j++) {
                if(graph->matrice[i][j] != 0)
                    printf("%c %d, ", tab_toId(j, graph), graph->matrice[i][j]);
            }
            printf("\n");
        }
        return;
    }

    FILE *fp = fopen(filename, "w");
    for(i=0; i< graph->V; i++)
        fprintf(fp, "%d: %c\n", i, graph->simboli.list[i]);
    for(i = 0; i < graph->V; i++){
        fprintf(fp,"%c: ", tab_toId(i, graph));
        for(j = 0; j < graph->V; j++) {
            if(graph->matrice[i][j] != 0)
                fprintf(fp, "%c %d, ", tab_toId(j, graph), graph->matrice[i][j]);
        }
        fprintf(fp,"\n");
    }
}


void grafo_generaLista(grafo graph){
    int i, j;
    link tmp = NULL;
    graph->lista = malloc(sizeof(node)*graph->V);
    for(i=0; i<graph->V; i++){
        graph->lista[i].id = tab_toId(i, graph);
        graph->lista->peso = 0;
        graph->lista[i].adj = NULL;
        for(j=0; j<graph->V; j++){
            if(graph->matrice[i][j] != 0){
                if(graph->lista[i].adj == NULL) {
                    graph->lista[i].adj = malloc(sizeof(node));
                    tmp = graph->lista[i].adj;
                }
                else {
                    tmp->adj = malloc(sizeof(node));
                    tmp = tmp->adj;
                }
                tmp->id = tab_toId(j, graph);
                tmp->peso = graph->matrice[i][j];
                tmp->adj = NULL;
            }

        }
    }
}


int grafo_adjCoppie(char id1, char id2, char id3, grafo graph, char strategy){
    int index1 = tab_toIndex(id1, graph);
    int index2 = tab_toIndex(id2, graph);
    int index3 = tab_toIndex(id3, graph);
    int a, adj12 = 0, adj13 = 0, adj23 = 0;
    link i;
    // tramite matrice
    if(strategy == 'm'){
        a = graph->matrice[index1][index2] * graph->matrice[index1][index3] * graph->matrice[index2][index3];
        return a;
    }

    if(strategy == 'l') {
        for(i = graph->lista[index1].adj; i != NULL; i = i->adj) {
            if(i->id == id2)
                adj12 = 1;
            if(i->id == id3)
                adj13 = 1;
        }
        for(i = graph->lista[index2].adj; i != NULL; i = i->adj) {
            if(i->id == id3)
                adj23 = 1;
        }
        a = adj12 * adj13 * adj23;
        return a;
    }
    return -1;
}