/*  È dato un tipo BST (ADT di prima classe), avente nodi estesi in modo tale da contenere puntatore al padre e
    dimensione del sottoalbero. Il tipo Item (quasi ADT) e le struct BSTnode (con puntatore link) e
    binarysearchtree sono definiti come segue

    typedef struct {
        char name[MAXC];
    } Item;
    typedef struct BSTnode* link;
    struct BSTnode {Item item; link p; link l; link r; int N; };
    struct binarysearchtree { link root; link z; };
    typedef struct binarysearchtree *BST;

    Si scriva una funzione che, dato un BST b, generi un duplicato (un BST con la stessa topologia, contenente un
    duplicato dei dati).

    La funzione abbia prototipo
    BST BSTdup(BST b);

    Se utile per la soluzione, si possono richiamare funzioni spiegate a lezione.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E02.h"

typedef struct BSTnode *link;

struct BSTnode {
    Item item;
    link p;
    link l;
    link r;
    int N;
};

struct binarysearchtree {
    link root;
    link z;
};

static int ITEMcmp(Item a, Item b) {
    return strcmp(a.name, b.name);
}

static link NEW(Item item, link p, link l, link r, int N) {
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;

    x->item = item;
    x->p = p;
    x->l = l;
    x->r = r;
    x->N = N;

    return x;
}

static int countN(link h, link z) {
    if (h == z)
        return 0;
    return h->N;
}

static void freeR(link h, link z) {
    if (h == z)
        return;

    freeR(h->l, z);
    freeR(h->r, z);
    free(h);
}

static link dupR(link h, link zold, link znew, link parent) {
    link x;

    if (h == zold)
        return znew;

    x = NEW(h->item, parent, znew, znew, h->N);
    if (x == NULL)
        return znew;

    x->l = dupR(h->l, zold, znew, x);
    x->r = dupR(h->r, zold, znew, x);

    return x;
}

static link insertR(link h, link z, Item item, link parent) {
    if (h == z)
        return NEW(item, parent, z, z, 1);

    if (ITEMcmp(item, h->item) < 0)
        h->l = insertR(h->l, z, item, h);
    else
        h->r = insertR(h->r, z, item, h);

    h->N = 1 + countN(h->l, z) + countN(h->r, z);
    return h;
}

static void showR(link h, link z) {
    if (h == z)
        return;

    showR(h->l, z);
    printf("%s (N=%d)\n", h->item.name, h->N);
    showR(h->r, z);
}

BST BSTinit(void) {
    BST b = malloc(sizeof(*b));
    if (b == NULL)
        return NULL;

    b->z = malloc(sizeof(*(b->z)));
    if (b->z == NULL) {
        free(b);
        return NULL;
    }

    strcpy(b->z->item.name, "");
    b->z->p = b->z;
    b->z->l = b->z;
    b->z->r = b->z;
    b->z->N = 0;

    b->root = b->z;

    return b;
}

void BSTfree(BST b) {
    if (b == NULL)
        return;

    freeR(b->root, b->z);
    free(b->z);
    free(b);
}

BST BSTdup(BST b) {
    BST copy;

    if (b == NULL)
        return NULL;

    copy = BSTinit();
    if (copy == NULL)
        return NULL;

    copy->root = dupR(b->root, b->z, copy->z, copy->z);

    return copy;
}

void BSTinsertLeaf(BST b, Item item) {
    if (b == NULL)
        return;

    b->root = insertR(b->root, b->z, item, b->z);
}

void BSTshow(BST b) {
    if (b == NULL)
        return;

    showR(b->root, b->z);
}