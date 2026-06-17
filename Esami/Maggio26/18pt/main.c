#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void) {
    GRAPH G;
    Edge e;
    FILE *fp;
    vertexSeq s;
    int i, id;

    G = GRAPHinit(10);

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

    /* archi orientati pesati */
    e.v = 0; e.w = 1; e.wt = 5;
    GRAPHinsertE(G, e);

    e.v = 1; e.w = 2; e.wt = 3;
    GRAPHinsertE(G, e);

    e.v = 2; e.w = 4; e.wt = 7;
    GRAPHinsertE(G, e);

    e.v = 4; e.w = 0; e.wt = 2;
    GRAPHinsertE(G, e);

    fp = fopen("../vertices.txt", "r");
    if (fp == NULL) {
        printf("Errore apertura file vertices.txt\n");
        GRAPHfree(G);
        return 1;
    }

    s = readVertexSeq(G, fp);
    fclose(fp);

    printf("Vertici letti: %d\n", vertexSeqSize(s));

    for (i = 0; i < vertexSeqSize(s); i++) {
        id = vertexSeqGet(s, i);
        printf("s[%d] = %d, nome = %s\n", i, id, GRAPHgetName(G, id));
    }

    vertexSeqFree(s);
    GRAPHfree(G);

    return 0;
}