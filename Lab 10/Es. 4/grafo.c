#include "grafo.h"

typedef struct node * link;

typedef struct node{
    char id [N];
    int peso;
    link adj;
}node;

typedef struct tab_s{
    char ** list;
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
    char id1[N], id2[N], net1[N], net2[N];
    FILE *fp = fopen(filename, "r");
    while(fscanf(fp, "%s %s %s %s %d", id1, net1, id2, net2, &peso) == 5){
        nrig++;
        tab_inserisciNew(id1, graph);
        tab_inserisciNew(id2, graph);
    }
    graph->E = nrig;
    graph->V = graph->simboli.n;
    graph->matrice = matrix_init(graph->V);
    rewind(fp);
    for(i=0; i<nrig; i++){
        fscanf(fp, "%s %s %s %s %d", id1, net1, id2, net2, &peso);
        u = tab_toIndex(id1, graph);
        v = tab_toIndex(id2, graph);
        graph->matrice[u][v] = peso;
        graph->matrice[v][u] = peso;
    }
}


int tab_toIndex(char *nome, grafo graph){
    int i;
    for(i=0; i<graph->simboli.n; i++){
        if(!strcmp(nome, graph->simboli.list[i]))
            return i;
    }
    return -1;
}


char* tab_toId(int index, grafo graph){
    return graph->simboli.list[index];
}


void tab_inserisciNew(char *nome, grafo graph){
    int i = 0, j, a;
    graph->simboli.list = realloc(graph->simboli.list, sizeof(char*)*(graph->simboli.n+1));
    while(i < graph->simboli.n &&(a = strcmp(graph->simboli.list[i], nome)) <= 0) {
        if(a == 0) {
            return;
        }
        i++;
    }
    graph->simboli.n++;
    graph->simboli.list[graph->simboli.n-1] = malloc(sizeof(char)*N);
    if(graph->simboli.n == 1){
        strcpy(graph->simboli.list[0], nome);
        return;
    }
    if(i==graph->simboli.n-1){
        strcpy(graph->simboli.list[i], nome);
        return;
    }
    for(j=graph->simboli.n-2; j != i && j>=0; j--){
        strcpy(graph->simboli.list[j+1], graph->simboli.list[j]);
    }
    strcpy(graph->simboli.list[i+1], graph->simboli.list[i]);
    strcpy(graph->simboli.list[i], nome);
}


void grafo_stampaGrafo(char *filename, grafo graph){
    int i, j;
    if(!strcmp("stdout", filename)) {
        for(i=0; i< graph->V; i++)
            printf("%d: %s\n", i, graph->simboli.list[i]);
        for(i = 0; i < graph->V; i++){
            printf("%s: ", tab_toId(i, graph));
            for(j = 0; j < graph->V; j++) {
                if(graph->matrice[i][j] != 0)
                    printf("%s %d, ", tab_toId(j, graph), graph->matrice[i][j]);
            }
            printf("\n");
        }
        return;
    }

    FILE *fp = fopen(filename, "w");
    for(i=0; i< graph->V; i++)
        fprintf(fp, "%d: %s\n", i, graph->simboli.list[i]);
    for(i = 0; i < graph->V; i++){
        fprintf(fp,"%s: ", tab_toId(i, graph));
        for(j = 0; j < graph->V; j++) {
            if(graph->matrice[i][j] != 0)
                fprintf(fp, "%s %d, ", tab_toId(j, graph), graph->matrice[i][j]);
        }
        fprintf(fp,"\n");
    }
}


void grafo_generaLista(grafo graph){
    int i, j;
    link tmp = NULL;
    graph->lista = malloc(sizeof(node)*graph->V);
    for(i=0; i<graph->V; i++){
        strcpy(graph->lista[i].id, tab_toId(i, graph));
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
                strcpy(tmp->id, tab_toId(j, graph));
                tmp->peso = graph->matrice[i][j];
                tmp->adj = NULL;
            }

        }
    }
}


int grafo_adjCoppie(char *id1, char *id2, char *id3, grafo graph, char strategy){
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
            if(!strcmp(i->id, id2))
                adj12 = 1;
            if(!strcmp(i->id, id3))
                adj13 = 1;
        }
        for(i = graph->lista[index2].adj; i != NULL; i = i->adj) {
            if(!strcmp(i->id, id3))
                adj23 = 1;
        }
        a = adj12 * adj13 * adj23;
        return a;
    }
    return -1;
}