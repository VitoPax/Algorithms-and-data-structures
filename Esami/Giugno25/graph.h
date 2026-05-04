#ifndef GIUGNO25_GRAPH_H
#define GIUGNO25_GRAPH_H

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void GRAPHinsertE(Graph G, int v, int w);
void GRAPHshow(Graph G);
void GRAPHfree(Graph G);

/* Funzione dell'esame: vedi graph.c */
int GRAPHcheckSimmetry(Graph G);

#endif //GIUGNO25_GRAPH_H