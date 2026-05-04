#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef struct node *link;

struct node {
    int v;
    link next;
};

struct graph {
    int V;
    int E;
    link *ladj;
};

static link NEW(int v, link next);
static void listFree(link x);
static int GRAPHedgeExists(Graph G, int v, int w);

Graph GRAPHinit(int V) {
    Graph G;
    int v;

    G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;

    G->V = V;
    G->E = 0;

    G->ladj = malloc(V * sizeof(link));
    if (G->ladj == NULL) {
        free(G);
        return NULL;
    }

    for (v = 0; v < V; v++)
        G->ladj[v] = NULL;

    return G;
}

static link NEW(int v, link next) {
    link x;

    x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;

    x->v = v;
    x->next = next;

    return x;
}

void GRAPHinsertE(Graph G, int v, int w) {
    if (G == NULL)
        return;

    if (v < 0 || v >= G->V || w < 0 || w >= G->V)
        return;

    G->ladj[v] = NEW(w, G->ladj[v]);
    G->E++;
}

void GRAPHshow(Graph G) {
    int v;
    link x;

    if (G == NULL)
        return;

    printf("Grafo con %d vertici e %d archi\n", G->V, G->E);

    for (v = 0; v < G->V; v++) {
        printf("%d:", v);

        for (x = G->ladj[v]; x != NULL; x = x->next) {
            printf(" %d", x->v);
        }

        printf("\n");
    }
}

void GRAPHfree(Graph G) {
    int v;

    if (G == NULL)
        return;

    for (v = 0; v < G->V; v++)
        listFree(G->ladj[v]);

    free(G->ladj);
    free(G);
}

static void listFree(link x) {
    link t;

    while (x != NULL) {
        t = x->next;
        free(x);
        x = t;
    }
}

/*
    Funzione ausiliaria utile:
    ritorna 1 se esiste l'arco v -> w,
    ritorna 0 altrimenti.
*/
static int GRAPHedgeExists(Graph G, int v, int w) {
    link x;

    for (x = G->ladj[v]; x != NULL; x = x->next) {
        if (x->v == w)
            return 1;
    }

    return 0;
}

/*
    ESERCIZIO:
    Scrivi tu questa funzione.

    Deve ritornare:
    1 se il grafo è simmetrico e senza cappi
    0 altrimenti
*/
int GRAPHcheckSimmetry(Graph G) {
    /*
        Suggerimento:

        per ogni vertice v:
            scorri la lista G->ladj[v]
            per ogni arco v -> w:
                se v == w, ritorna 0
                se non esiste w -> v, ritorna 0

        alla fine ritorna 1
    */




    return -1;  /* valore provvisorio */
}