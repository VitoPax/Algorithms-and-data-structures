#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef struct node *link;

struct node {
    int v;
    int wt;
    link next;
};

struct graph {
    int V;
    int E;
    link *ladj;
    link z;
};

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof(*x));
    if (x == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }

    x->v = v;
    x->wt = wt;
    x->next = next;

    return x;
}

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;

    e.v = v;
    e.w = w;
    e.wt = wt;

    return e;
}

Graph GRAPHinit(int V) {
    int v;

    Graph G = malloc(sizeof(*G));
    if (G == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }

    G->V = V;
    G->E = 0;

    G->z = NEW(-1, -1, NULL);

    G->ladj = malloc(V * sizeof(link));
    if (G->ladj == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }

    for (v = 0; v < V; v++) {
        G->ladj[v] = G->z;
    }

    return G;
}

static void insertE(Graph G, Edge e) {
    int v = e.v;
    int w = e.w;
    int wt = e.wt;

    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->ladj[w] = NEW(v, wt, G->ladj[w]);

    G->E++;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

void GRAPHstore(Graph G, FILE *fout) {
    int v;
    link t;

    if (G == NULL || fout == NULL) {
        return;
    }

    fprintf(fout, "V = %d, E = %d\n", G->V, G->E);

    for (v = 0; v < G->V; v++) {
        fprintf(fout, "%d: ", v);

        for (t = G->ladj[v]; t != G->z; t = t->next) {
            fprintf(fout, "%d(%d) ", t->v, t->wt);
        }

        fprintf(fout, "\n");
    }
}

void GRAPHfree(Graph G) {
    int v;
    link t, next;

    if (G == NULL) {
        return;
    }

    for (v = 0; v < G->V; v++) {
        for (t = G->ladj[v]; t != G->z; t = next) {
            next = t->next;
            free(t);
        }
    }

    free(G->z);
    free(G->ladj);
    free(G);
}

// Rimozione di un arco

// Toglie w dalla lista di v
static int removeFromList(Graph G, int v, int w) {
    link x, p;

    for (x = G->ladj[v], p = NULL; x != G->z; p = x, x = x->next) {
        if (x->v == w) {
            if (p == NULL) {
                G->ladj[v] = x->next;
            } else {
                p->next = x->next;
            }

            free(x);
            return 1;
        }
    }

    return 0;
}

// Togliamo in entrambe le direzioni
static void removeE(Graph G, Edge e) {
    int v = e.v;
    int w = e.w;

    int removed1 = removeFromList(G, v, w);
    int removed2 = removeFromList(G, w, v);

    if (removed1 && removed2) {
        G->E--;
    }
}

// Wrapper
void GRAPHremoveE(Graph G, int id1, int id2) {
    removeE(G, EDGEcreate(id1, id2, 0));
}