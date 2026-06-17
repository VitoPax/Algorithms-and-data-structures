#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void) {
    GRAPH G;
    Edge e;
    FILE *fp;
    vertexSeq V1;
    int i, id;
    int res;

    G = GRAPHinit(10);

    /* assegno i nomi */
    GRAPHsetName(G, 0, "Roma");
    GRAPHsetName(G, 1, "Milano");
    GRAPHsetName(G, 2, "Torino");
    GRAPHsetName(G, 3, "Napoli");
    GRAPHsetName(G, 4, "Genova");
    GRAPHsetName(G, 5, "Bologna");
    GRAPHsetName(G, 6, "Firenze");
    GRAPHsetName(G, 7, "Venezia");
    GRAPHsetName(G, 8, "Palermo");
    GRAPHsetName(G, 9, "Catania");

    /* archi */

    e.v = 0; e.w = 1; e.wt = 5;   /* Roma -> Milano */
    GRAPHinsertE(G, e);

    e.v = 2; e.w = 5; e.wt = 4;   /* Torino -> Bologna */
    GRAPHinsertE(G, e);

    e.v = 4; e.w = 6; e.wt = 1;   /* Genova -> Firenze */
    GRAPHinsertE(G, e);


    //--------------------------------------------------------------
    /*
       Se aggiungi questo arco rompe il bipartito,
       perché collega due vertici entrambi in V1
    */

    /*
    e.v = 0; e.w = 2; e.wt = 7;
    GRAPHinsertE(G, e);
    */


    //--------------------------------------------------------------

    /* leggo V1 dal file */
    fp = fopen("../vertices.txt", "r");

    if (fp == NULL) {
        printf("Errore apertura file\n");
        return 1;
    }

    V1 = readVertexSeq(G, fp);
    fclose(fp);

    printf("Vertici in V1:\n");

    for (i = 0; i < vertexSeqSize(V1); i++) {
        id = vertexSeqGet(V1, i);
        printf("%s\n", GRAPHgetName(G, id));
    }

    /* verifica bipartizione */
    res = checkBipart(G, V1);

    if (res)
        printf("\nIl grafo e' bipartito rispetto a V1 e V2\n");
    else
        printf("\nIl grafo NON e' bipartito rispetto a V1 e V2\n");

    vertexSeqFree(V1);
    GRAPHfree(G);

    return 0;
}