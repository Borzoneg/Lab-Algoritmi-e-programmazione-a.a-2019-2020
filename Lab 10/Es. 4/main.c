#include "grafo.h"


int main() {
    grafo G = grafo_init();
    grafo_leggiFile("grafo.txt", G);
    grafo_stampaGrafo("stdout", G);
    grafo_generaLista(G);
    printf("%d", grafo_adjCoppie("Ifrit", "Tatooine", "Alderaan", G, 'l'));
    return 0;
}