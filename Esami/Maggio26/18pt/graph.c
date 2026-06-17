#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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