#include <stdio.h>
#include "graph.h"

int main(void) {
    Graph G = GRAPHinit(5);

    GRAPHinsertE(G, 0, 1, 10);
    GRAPHinsertE(G, 0, 4, 7);
    GRAPHinsertE(G, 3, 4, 2);




    // Test rimozione arco
    printf("Prima della rimozione:\n");
    GRAPHstore(G, stdout);

    /* Rimozione arco
    GRAPHremoveE(G, 0, 4);
    printf("\nDopo la rimozione di 0--4:\n");
    GRAPHstore(G, stdout);
    */

    GRAPHfree(G);

    return 0;
}