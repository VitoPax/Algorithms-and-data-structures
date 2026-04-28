#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "item.h"

typedef struct BSTnode *link;

struct BSTnode {
    int key;
    link l;
    link r;
};

struct bst {
    link root;
    link z;
};

// Creazione del nodo
static link NEW(int key, link l, link r) {
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->key = key;
    x->l = l;
    x->r = r;
    return x;
}


// Inserimento in foglia, versione RICORSIVA