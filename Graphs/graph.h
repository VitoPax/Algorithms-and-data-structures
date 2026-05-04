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

void GRAPHdfs(Graph G);
void GRAPHdfsFrom(Graph G, int start);


#endif //GRAPHS_GRAPH_H