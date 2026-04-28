#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "item.h"

typedef struct BSTnode *link;

struct BSTnode {
    Item item;
    link l;
    link r;
};

struct bst {
    link root;
    link z;
};

// Creazione del nodo
static link NEW(Item item, link l, link r) {
    link x = malloc(sizeof(*x));

    if (x == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }

    x->item = item;
    x->l = l;
    x->r = r;

    return x;
}


BST BSTinit(void) {
    BST bst = malloc(sizeof(*bst));

    if (bst == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }

    bst->z = NEW(ITEMsetNull(), NULL, NULL);
    bst->root = bst->z;

    return bst;
}


// Inserimento in foglia, versione RICORSIVA

