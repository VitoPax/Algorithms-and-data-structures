/*
    È dato un tipo BST (ADT di prima classe). Si scriva una funzione che, dato un BST b, e due chiavi k1 e k2,
    conti i nodi compresi tra le due chiavi (escluse dal conteggio) verificando anche se le due chiavi siano presenti.
    La funzione, avente prototipo
    int BSTcountBetween(BST b, Key k1, Key k2);
    ritorni come risultato il conteggio, oppure -1 se una o entrambe le chiavi non sono presenti.
    Attenzione: è preferibile (se ne terrà conto in fase di valutazione) una soluzione in grado di evitare la visita di
    parti dell’albero sicuramente da non conteggiare.
*/

/*
    Altro esercizio
    È dato un BST b e una chiave k.
    Si scriva una funzione

    int BSTcountGreater(BST b, Key k);

    che conti quanti nodi del BST hanno chiave strettamente maggiore di k.
    Anche qui, è preferibile una soluzione che eviti la visita di parti dell’albero sicuramente inutili.
*/

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

static link NEW(Item item, link l, link r) {
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->item = item;
    x->l = l;
    x->r = r;
    return x;
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

    b->z->l = b->z;
    b->z->r = b->z;
    b->root = b->z;

    return b;
}

static link insertR(link h, link z, Item val) {
    int cmp;

    if (h == z)
        return NEW(val, z, z);

    cmp = KEYcmp(KEYget(&val), KEYget(&h->item));

    if (cmp < 0)
        h->l = insertR(h->l, z, val);
    else if (cmp > 0)
        h->r = insertR(h->r, z, val);

    return h;
}

void BSTinsert_leafR(BST b, Item val) {
    if (b == NULL)
        return;
    b->root = insertR(b->root, b->z, val);
}

static int countBetweenR(link h, link z, Key k1, Key k2, int *cP) {
    int cmp1, cmp2;

    if (h == z)
        return 0;

    cmp1 = KEYcmp(k1, KEYget(&h->item));
    cmp2 = KEYcmp(k2, KEYget(&h->item));

    if (cmp1 == 0)
        (*cP)++;
    if (cmp2 == 0)
        (*cP)++;

    if (cmp1 >= 0)
        return countBetweenR(h->r, z, k1, k2, cP);

    if (cmp2 <= 0)
        return countBetweenR(h->l, z, k1, k2, cP);

    return 1 + countBetweenR(h->l, z, k1, k2, cP)
             + countBetweenR(h->r, z, k1, k2, cP);
}

int BSTcountBetween(BST b, Key k1, Key k2) {
    int foundCnt = 0;
    int ret;

    if (b == NULL)
        return -1;

    if (KEYcmp(k1, k2) > 0) {
        Key t = k1;
        k1 = k2;
        k2 = t;
    }

    ret = countBetweenR(b->root, b->z, k1, k2, &foundCnt);

    if (foundCnt < 2)
        return -1;

    return ret;
}

static int countGreaterR(link h, link z, Key k) {
    int cmp;

    if (h == z)
        return 0;
    cmp = KEYcmp(k,KEYget(&h->item));

    if (cmp >= 0)
        return countGreaterR(h->r, z,k);

    return 1 + countGreaterR(h->r,z,k) + countGreaterR(h->l, z, k);
}

int BSTcountGreater(BST b, Key k) {
    int conteggio;

    if (b == NULL)
        return -1;

    conteggio = countGreaterR(b->root,b->z,k);

    return conteggio;
}

static void showR(link h, link z) {
    if (h == z)
        return;
    showR(h->l, z);
    printf("%s\n", KEYget(&h->item));
    showR(h->r, z);
}

void BSTshow(BST b) {
    if (b == NULL)
        return;
    showR(b->root, b->z);
}