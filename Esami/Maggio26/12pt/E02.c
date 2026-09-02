/*
È dato un tipo LIST (ADT di prima classe per liste concatenate semplici). Si riportano le definizioni dei tipi.

Si scriva una funzione che, data una lista LIST l, generi un duplicato (una seconda lista con contenente un
duplicato dei dati, nello stesso ordine). La funzione abbia prototipo

LIST LISTdup(LIST l);
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAXC 11

typedef struct {
    char name[MAXC];
    int age;
} Item;

typedef struct node *link;

struct node {
    Item item;
    link next;
};

struct list {
    link root;
};


static link NODEdup(Item val, link next) {
    link nuovo;

    nuovo = malloc(sizeof(*nuovo));

    if (nuovo == NULL) return NULL;
    nuovo->item = val; /* Posso fare cosi' perche' e' tutto statico, altrimenti avrei dovuto fare strdup. In questo caso statico
                          avrei potuto fare anche strcpy(x->item.name, val.name); e poi fare anche x->item.age = age. */
    nuovo->next = next;

    return nuovo;
}

LIST LISTdup(LIST l) {
    LIST ldup;
    link x, nuovo, tail = NULL;

    if (l == NULL) return NULL;

    ldup = malloc(sizeof(struct list));

    if (ldup == NULL) return NULL;
    ldup->root = NULL;

    for (x = l->root; x != NULL; x = x->next) {
        nuovo = NODEdup(x->item, NULL);
        if (tail == NULL)
            ldup->root = nuovo;      /* primo nodo: aggancio all'handle */
        else
            tail->next = nuovo;      /* nodi successivi: aggancio all'ultimo */
        tail = nuovo;
    }

    return ldup;
}