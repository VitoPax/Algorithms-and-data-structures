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
};

/* Gestione nodi ( cioe' ciascun singolo vertice) */
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

/* Funzione ausiliaria per la creazione di un arco */
static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;

    e.v = v;
    e.w = w;
    e.wt = wt;

    return e;
}

/* Funzione privata: inizializza un grafo con V vertici e 0 archi */
Graph GRAPHinit(int V) {

    Graph g = malloc(sizeof(*g));

     if (g == NULL) {
         printf("Errore malloc\n");
         exit(1);
     }

    g->V = V;
    g->E = 0;

    g->ladj = malloc(V*sizeof(link));

    if (g->ladj == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }

    for (int v = 0; v < V; v++) {
        g->ladj[v] = NULL;
    }

    return g;
}

/* Funzione privata: inserisce un arco non orientato */
static void insertE(Graph G, Edge e) {
    int v = e.v;
    int w = e.w;
    int wt = e.wt;

    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->ladj[w] = NEW(v, wt, G->ladj[w]);

    G->E++;
}

/* Funzione pubblica: wrapper di inserimento */
void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

/* Funzione privata: rimuove w dalla lista di adiacenza di v */
static int removeFromList(Graph G, int v, int w) {
    link x;
    link p;

    for (x = G->ladj[v], p = NULL; x != NULL; p = x, x = x->next) {
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

/* Funzione privata: rimuove un arco non orientato */
static void removeE(Graph G, Edge e) {
    int v = e.v;
    int w = e.w;

    int removed1 = removeFromList(G, v, w);
    int removed2 = removeFromList(G, w, v);

    if (removed1 && removed2) {
        G->E--;
    }
}

/* Funzione pubblica: wrapper di rimozione */
void GRAPHremoveE(Graph G, int id1, int id2) {
    removeE(G, EDGEcreate(id1, id2, 0));
}

/* Stampa il grafo */
void GRAPHstore(Graph G, FILE *fout) {
    int v;
    link t;

    if (G == NULL || fout == NULL) {
        return;
    }

    fprintf(fout, "V = %d, E = %d\n", G->V, G->E);

    for (v = 0; v < G->V; v++) {
        fprintf(fout, "%d: ", v);

        for (t = G->ladj[v]; t != NULL; t = t->next) {
            fprintf(fout, "%d(%d) ", t->v, t->wt);
        }

        fprintf(fout, "\n");
    }
}

/* DFS semplice ricorsiva */
static void simpleDfsR(Graph G, Edge e, int *cnt, int *pre) {
    link t;
    int w = e.w;

    pre[w] = (*cnt)++;

    printf("Visito vertice %d\n", w);

    for (t = G->ladj[w]; t != NULL; t = t->next) {
        if (pre[t->v] == -1) {
            simpleDfsR(G, EDGEcreate(w, t->v, t->wt), cnt, pre);
        }
    }
}

/* DFS semplice pubblica */
void GRAPHsimpleDfs(Graph G, int id) {
    int v;
    int cnt = 0;
    int *pre;

    if (G == NULL) {
        return;
    }

    pre = malloc(G->V * sizeof(int));

    if (pre == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }

    for (v = 0; v < G->V; v++) {
        pre[v] = -1;
    }

    simpleDfsR(G, EDGEcreate(id, id, 0), &cnt, pre);

    for (v = 0; v < G->V; v++) {
        if (pre[v] == -1) {
            simpleDfsR(G, EDGEcreate(v, v, 0), &cnt, pre);
        }
    }

    printf("\nDiscovery time labels:\n");

    for (v = 0; v < G->V; v++) {
        printf("vertex %d : %d\n", v, pre[v]);
    }

    free(pre);
}

/* Libera tutta la memoria del grafo */
void GRAPHfree(Graph G) {
    int v;
    link t;
    link next;

    if (G == NULL) {
        return;
    }

    for (v = 0; v < G->V; v++) {
        for (t = G->ladj[v]; t != NULL; t = next) {
            next = t->next;
            free(t);
        }
    }

    free(G->ladj);
    free(G);
}