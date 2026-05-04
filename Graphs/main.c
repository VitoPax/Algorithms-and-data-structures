#include <stdio.h>
#include "graph.h"

int main(void) {
    Graph G = GRAPHinit(7);

    /*
        Grafo di test:

        1
        |
        2
       / \
      0   4
     / \ / \
    6  5---3

    Archi:
    0--2
    0--5
    0--6
    1--2
    2--4
    3--4
    3--5
    4--5
    */

    GRAPHinsertE(G, 0, 2, 1);
    GRAPHinsertE(G, 0, 5, 1);
    GRAPHinsertE(G, 0, 6, 1);
    GRAPHinsertE(G, 1, 2, 1);
    GRAPHinsertE(G, 2, 4, 1);
    GRAPHinsertE(G, 3, 4, 1);
    GRAPHinsertE(G, 3, 5, 1);
    GRAPHinsertE(G, 4, 5, 1);

    printf("Grafo:\n");
    GRAPHstore(G, stdout);

    printf("\nDFS su tutto il grafo:\n");
    GRAPHdfs(G);

    printf("\nDFS partendo da 0:\n");
    GRAPHdfsFrom(G, 0);

    /*
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









