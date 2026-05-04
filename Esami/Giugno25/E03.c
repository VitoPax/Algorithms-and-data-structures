/*
È dato un Grafo orientato realizzato con liste adiacenza (tipo ADT Graph).
Si scriva una funzione GRAPHcheckSimmetry che, ricevuto come parametro un grafo, verifichi se il grafo è simmetrico e non contiene cappi (self-loop).
Si ricorda che un grafo si dice simmetrico quando per ogni arco v-w esiste anche l’arco inverso w-v.
*/


/* VEDI graph.c per la funzione richiesta all'esame */

/* Qui testiamo */

#include <stdio.h>
#include "graph.h"

int main(void) {
    Graph G1;
    Graph G2;
    Graph G3;

    /*
        Caso 1:
        Simmetrico e senza cappi

        0 <-> 1
        1 <-> 2
        2 <-> 3
    */
    G1 = GRAPHinit(4);

    GRAPHinsertE(G1, 0, 1);
    GRAPHinsertE(G1, 1, 0);

    GRAPHinsertE(G1, 1, 2);
    GRAPHinsertE(G1, 2, 1);

    GRAPHinsertE(G1, 2, 3);
    GRAPHinsertE(G1, 3, 2);

    printf("Test 1 - grafo simmetrico senza cappi:\n");
    GRAPHshow(G1);
    printf("Risultato: %d\n\n", GRAPHcheckSimmetry(G1));


    /*
        Caso 2:
        Non simmetrico

        esiste 0 -> 1
        ma non esiste 1 -> 0
    */
    G2 = GRAPHinit(3);

    GRAPHinsertE(G2, 0, 1);
    GRAPHinsertE(G2, 1, 2);
    GRAPHinsertE(G2, 2, 1);

    printf("Test 2 - grafo non simmetrico:\n");
    GRAPHshow(G2);
    printf("Risultato: %d\n\n", GRAPHcheckSimmetry(G2));


    /*
        Caso 3:
        Ha un cappio

        esiste 1 -> 1
    */
    G3 = GRAPHinit(3);

    GRAPHinsertE(G3, 0, 1);
    GRAPHinsertE(G3, 1, 0);

    GRAPHinsertE(G3, 1, 1);

    printf("Test 3 - grafo con cappio:\n");
    GRAPHshow(G3);
    printf("Risultato: %d\n\n", GRAPHcheckSimmetry(G3));

    GRAPHfree(G1);
    GRAPHfree(G2);
    GRAPHfree(G3);

    return 0;
}