#ifndef INC_18PT_GRAPH_H
#define INC_18PT_GRAPH_H

#include <stdio.h>

#define MAXC 20

typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;

typedef struct graph *GRAPH;
typedef struct vertexSeq_s *vertexSeq;

/* GRAPH */
GRAPH GRAPHinit(int V);
void GRAPHfree(GRAPH G);

void GRAPHsetName(GRAPH G, int id, char *name);
int GRAPHgetIndex(GRAPH G, char *label);
char *GRAPHgetName(GRAPH G, int id);

void GRAPHinsertE(GRAPH G, Edge e);

int GRAPHnumV(GRAPH G);
int GRAPHnumE(GRAPH G);

/* vertexSeq */
vertexSeq vertexSeqInit(int maxN);
void vertexSeqInsert(vertexSeq s, int v);
int vertexSeqSize(vertexSeq s);
int vertexSeqGet(vertexSeq s, int i);
void vertexSeqFree(vertexSeq s);

/* funzione richiesta dalla traccia */
vertexSeq readVertexSeq(GRAPH G, FILE *fp);

int checkBipart(GRAPH g, vertexSeq V1);

#endif //INC_18PT_GRAPH_H
