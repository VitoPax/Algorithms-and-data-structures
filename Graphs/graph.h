#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <stdio.h>

typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph G);

void GRAPHinsertE(Graph G, int id1, int id2, int wt);
void GRAPHremoveE(Graph G, int id1, int id2);

void GRAPHstore(Graph G, FILE *fout);


#endif //GRAPHS_GRAPH_H