#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"

/*
    graph.c fedele all'impostazione delle slide:
    - grafo come ADT di prima classe;
    - rappresentazione con liste di adiacenza;
    - sentinella z;
    - tabella di simboli interna al grafo;
    - archi orientati e pesati, come richiesto dalla traccia.
*/

/* =========================
   Tabella di simboli interna
   Implementazione semplice:
   vettore non ordinato di stringhe.
   L'indice nel vettore coincide con l'indice del vertice.
   ========================= */

typedef struct symbtab *ST;

struct symbtab {
    char **a;
    int maxN;
    int n;
};

static ST STinit(int maxN) {
    int i;
    ST st = malloc(sizeof(*st));
    if (st == NULL) exit(EXIT_FAILURE);

    st->a = malloc(maxN * sizeof(char *));
    if (st->a == NULL) exit(EXIT_FAILURE);

    st->maxN = maxN;
    st->n = 0;

    for (i = 0; i < maxN; i++)
        st->a[i] = NULL;

    return st;
}

static void STfree(ST st) {
    int i;

    if (st == NULL) return;

    for (i = 0; i < st->maxN; i++)
        free(st->a[i]);

    free(st->a);
    free(st);
}

static void STinsert(ST st, char *label, int id) {
    if (st == NULL) return;
    if (id < 0 || id >= st->maxN) return;

    if (st->a[id] != NULL)
        free(st->a[id]);

    st->a[id] = malloc((strlen(label) + 1) * sizeof(char));
    if (st->a[id] == NULL) exit(EXIT_FAILURE);

    strcpy(st->a[id], label);

    if (id >= st->n)
        st->n = id + 1;
}

static int STsearch(ST st, char *label) {
    int i;

    if (st == NULL || label == NULL) return -1;

    for (i = 0; i < st->n; i++) {
        if (st->a[i] != NULL && strcmp(st->a[i], label) == 0)
            return i;
    }

    return -1;
}

static char *STsearchByIndex(ST st, int id) {
    if (st == NULL) return NULL;
    if (id < 0 || id >= st->maxN) return NULL;

    return st->a[id];
}

/* =========================
   GRAPH con lista di adiacenza
   ========================= */

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
    ST tab;
    link z;
};

/* =========================
   vertexSeq
   ========================= */

struct vertexSeq_s {
    int *v;
    int n;
    int maxN;
};

/* =========================
   Funzioni statiche di utilità
   ========================= */

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof(*x));
    if (x == NULL) exit(EXIT_FAILURE);

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

static void insertE(GRAPH G, Edge e) {
    int v = e.v;
    int w = e.w;
    int wt = e.wt;

    if (G == NULL) return;
    if (v < 0 || v >= G->V || w < 0 || w >= G->V) return;

    /*
        Grafo orientato pesato:
        inserisco solo v -> w.
        Per un grafo non orientato avrei inserito anche w -> v.
    */
    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->E++;
}

/* =========================
   Funzioni GRAPH pubbliche
   ========================= */

GRAPH GRAPHinit(int V) {
    int v;
    GRAPH G = malloc(sizeof(*G));
    if (G == NULL) exit(EXIT_FAILURE);

    G->V = V;
    G->E = 0;

    G->z = NEW(-1, -1, NULL);

    G->ladj = malloc(V * sizeof(link));
    if (G->ladj == NULL) exit(EXIT_FAILURE);

    for (v = 0; v < V; v++)
        G->ladj[v] = G->z;

    G->tab = STinit(V);

    return G;
}

void GRAPHfree(GRAPH G) {
    int v;
    link t, next;

    if (G == NULL) return;

    for (v = 0; v < G->V; v++) {
        for (t = G->ladj[v]; t != G->z; t = next) {
            next = t->next;
            free(t);
        }
    }

    STfree(G->tab);
    free(G->ladj);
    free(G->z);
    free(G);
}

void GRAPHsetName(GRAPH G, int id, char *name) {
    if (G == NULL) return;
    if (id < 0 || id >= G->V) return;

    STinsert(G->tab, name, id);
}

int GRAPHgetIndex(GRAPH G, char *label) {
    if (G == NULL) return -1;

    return STsearch(G->tab, label);
}

char *GRAPHgetName(GRAPH G, int id) {
    if (G == NULL) return NULL;

    return STsearchByIndex(G->tab, id);
}

void GRAPHinsertE(GRAPH G, Edge e) {
    insertE(G, e);
}

/*
    Se nel tuo graph.h hai il prototipo:
        void GRAPHinsertE(GRAPH g, int id1, int id2, int wt);
    allora sostituisci la funzione sopra con questa:

    void GRAPHinsertE(GRAPH G, int id1, int id2, int wt) {
        insertE(G, EDGEcreate(id1, id2, wt));
    }
*/

int GRAPHnumV(GRAPH G) {
    if (G == NULL) return 0;

    return G->V;
}

int GRAPHnumE(GRAPH G) {
    if (G == NULL) return 0;

    return G->E;
}

/* =========================
   vertexSeq: ADT di prima classe
   ========================= */

vertexSeq vertexSeqInit(int maxN) {
    vertexSeq s;

    if (maxN <= 0)
        maxN = 1;

    s = malloc(sizeof(*s));
    if (s == NULL) exit(EXIT_FAILURE);

    s->v = malloc(maxN * sizeof(int));
    if (s->v == NULL) exit(EXIT_FAILURE);

    s->n = 0;
    s->maxN = maxN;

    return s;
}

void vertexSeqInsert(vertexSeq s, int v) {
    int *tmp;

    if (s == NULL) return;

    if (s->n == s->maxN) {
        s->maxN *= 2;

        tmp = realloc(s->v, s->maxN * sizeof(int));
        if (tmp == NULL) exit(EXIT_FAILURE);

        s->v = tmp;
    }

    s->v[s->n++] = v;
}

int vertexSeqSize(vertexSeq s) {
    if (s == NULL) return 0;

    return s->n;
}

int vertexSeqGet(vertexSeq s, int i) {
    if (s == NULL) return -1;
    if (i < 0 || i >= s->n) return -1;

    return s->v[i];
}

void vertexSeqFree(vertexSeq s) {
    if (s == NULL) return;

    free(s->v);
    free(s);
}

/* =========================
   Funzione richiesta dalla traccia
   ========================= */

vertexSeq readVertexSeq(GRAPH G, FILE *fp) {
    char label[MAXC];
    int id;
    vertexSeq s;

    if (G == NULL || fp == NULL) return NULL;

    s = vertexSeqInit(10);

    /*
        Il file contiene un elenco di nomi di vertici, uno per riga.
        MAXC = 20, quindi leggo al massimo 19 caratteri più '\0'.
    */
    while (fscanf(fp, "%19s", label) == 1) {
        id = GRAPHgetIndex(G, label);

        if (id != -1)
            vertexSeqInsert(s, id);
    }

    return s;
}


int checkBipart(GRAPH g, vertexSeq V1) {
    int *inV1;
    int i, u, w;
    link t;

    /* Tutti i vertici sono inizialmente considerati in V2 */
    inV1 = calloc(g->V, sizeof(int));

    /* Marco con 1 i vertici appartenenti a V1 */
    for (i = 0; i < vertexSeqSize(V1); i++) {
        u = vertexSeqGet(V1, i);
        inV1[u] = 1;
    }

    /* Scansione di tutti gli archi u -> w */
    for (u = 0; u < g->V; u++) {
        for (t = g->ladj[u]; t != g->z; t = t->next) {

            /* t->v contiene la destinazione dell'arco */
            w = t->v;

            /*
             * Se u e w appartengono allo stesso insieme,
             * la partizione non è bipartita.
             */
            if (inV1[u] == inV1[w]) {
                free(inV1);
                return 0;
            }
        }
    }

    free(inV1);
    return 1;
}

static void bestPathR(
    GRAPH g,
    int u,
    int *inS,
    int *visited,
    int *path,
    int pathLen,
    int countS,
    int weight,
    int *best,
    int *bestLen,
    int *bestWeight
) {
    link t;
    int w;
    int tripleCount;
    int i;

    /*
     * Il cammino corrente è una soluzione valida se:
     * - ha un numero pari di vertici;
     * - metà dei vertici appartiene a S.
     *
     * Il vincolo sulle terne è già stato controllato
     * durante la costruzione.
     */
    if (pathLen % 2 == 0 && countS * 2 == pathLen) {
        if (weight > *bestWeight) {
            *bestWeight = weight;
            *bestLen = pathLen;

            for (i = 0; i < pathLen; i++)
                best[i] = path[i];
        }
    }

    /*
     * Provo a estendere il cammino corrente u -> w
     * con ogni arco uscente da u.
     */
    for (t = g->ladj[u]; t != g->z; t = t->next) {
        w = t->v;

        /* Il cammino deve essere semplice. */
        if (visited[w])
            continue;

        /*
         * Se aggiungendo w si forma una terna,
         * verifico il vincolo:
         *
         * almeno uno deve appartenere a S,
         * ma non possono appartenere tutti a S.
         */
        if (pathLen >= 2) {
            tripleCount =
                inS[path[pathLen - 2]] +
                inS[path[pathLen - 1]] +
                inS[w];

            if (tripleCount == 0 || tripleCount == 3)
                continue;
        }

        /* Scelta: aggiungo w al cammino. */
        visited[w] = 1;
        path[pathLen] = w;

        bestPathR(
            g,
            w,
            inS,
            visited,
            path,
            pathLen + 1,
            countS + inS[w],
            weight + t->wt,
            best,
            bestLen,
            bestWeight
        );

        /* Backtrack: rimuovo w dal cammino corrente. */
        visited[w] = 0;
    }
}

int bestPath(GRAPH g, vertexSeq S) {
    int *inS;
    int *visited;
    int *path;
    int *best;

    int i;
    int start;
    int bestLen = 0;
    int bestWeight = INT_MIN;

    inS = calloc(g->V, sizeof(int));
    visited = calloc(g->V, sizeof(int));
    path = malloc(g->V * sizeof(int));
    best = malloc(g->V * sizeof(int));

    if (inS == NULL || visited == NULL ||
        path == NULL || best == NULL) {
        exit(EXIT_FAILURE);
        }

    /*
     * Costruisco il vettore di appartenenza:
     *
     * inS[v] = 1 se v appartiene a S
     * inS[v] = 0 altrimenti
     */
    for (i = 0; i < vertexSeqSize(S); i++) {
        int v = vertexSeqGet(S, i);

        if (v >= 0 && v < g->V)
            inS[v] = 1;
    }

    /*
     * Ogni vertice può essere il primo
     * vertice del cammino.
     */
    for (start = 0; start < g->V; start++) {
        visited[start] = 1;
        path[0] = start;

        bestPathR(
            g,
            start,
            inS,
            visited,
            path,
            1,              /* un vertice nel cammino */
            inS[start],     /* quanti appartengono a S */
            0,              /* nessun arco: peso zero */
            best,
            &bestLen,
            &bestWeight
        );

        visited[start] = 0;
    }

    if (bestLen == 0) {
        printf("Nessun cammino valido trovato.\n");

        free(inS);
        free(visited);
        free(path);
        free(best);

        return INT_MIN;
    }

    printf("Cammino ottimo: ");

    for (i = 0; i < bestLen; i++) {
        printf("%s", GRAPHgetName(g, best[i]));

        if (i < bestLen - 1)
            printf(" -> ");
    }

    printf("\nPeso ottimo: %d\n", bestWeight);

    free(inS);
    free(visited);
    free(path);
    free(best);

    return bestWeight;
}