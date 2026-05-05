/*
È dato un BST (o albero binario, il problema è equivalente). Si scriva una funzione che verifichi se l’albero è
bilanciato: si utilizzi come criterio di bilanciamento quello basato sulle dimensioni dei sotto-alberi. La funzione
abbia prototipo:
int BSTisBalanced(BST b);
Si richiede, oltre alla funzione, la definizione del tipo BST e del tipo usato per il nodo. Si assuma che il nodo
dell’albero NON sia stato esteso in modo da contenere la dimensione del relativo sotto-albero.
*/
#include <stdlib.h>
#include "bst.h"

/* Definizione del nodo */

typedef struct BSTnode *link;

struct BSTnode {
    int val;
    link l;
    link r;
};

struct bst {
    link root;
};

static link NODEnew(int val) {
    link x = malloc(sizeof(*x));

    x->val = val;
    x->l = NULL;
    x->r = NULL;

    return x;
}

BST BSTnew(void) {
    BST b = malloc(sizeof(*b));

    b->root = NULL;

    return b;
}

static void NODEfree(link root) {
    if (root == NULL)
        return;

    NODEfree(root->l);
    NODEfree(root->r);

    free(root);
}

void BSTfree(BST b) {
    if (b == NULL)
        return;

    NODEfree(b->root);
    free(b);
}

void BSTsetRoot(BST b, int val) {
    if (b == NULL)
        return;

    if (b->root != NULL)
        NODEfree(b->root);

    b->root = NODEnew(val);
}

static link NODEsearch(link root, int val) {
    if (root == NULL)
        return NULL;

    if (root->val == val)
        return root;

    link found = NODEsearch(root->l, val);

    if (found != NULL)
        return found;

    return NODEsearch(root->r, val);
}

void BSTinsertLeft(BST b, int parent_val, int val) {
    if (b == NULL)
        return;

    link parent = NODEsearch(b->root, parent_val);

    if (parent == NULL)
        return;

    if (parent->l != NULL)
        NODEfree(parent->l);

    parent->l = NODEnew(val);
}

void BSTinsertRight(BST b, int parent_val, int val) {
    if (b == NULL)
        return;

    link parent = NODEsearch(b->root, parent_val);

    if (parent == NULL)
        return;

    if (parent->r != NULL)
        NODEfree(parent->r);

    parent->r = NODEnew(val);
}

/* =========================
   FUNZIONE DELL'ESERCIZIO
   ========================= */

static int NODEcheckSize_r(link root) {
    if (root == NULL)
        return 0;

    int sL = NODEcheckSize_r(root->l);
    if (sL == -1)
        return -1;

    int sR = NODEcheckSize_r(root->r);
    if (sR == -1)
        return -1;

    if (abs(sL - sR) > 1)
        return -1;

    return 1 + sL + sR;
}

int BSTisBalanced(BST b) {
    if (b == NULL)
        return 1;

    return NODEcheckSize_r(b->root) != -1;
}

/* VERSIONE ESTESA
static int NODEsize_r(link root) {
    if (root == NULL)
        return 0;

    return 1 + NODEsize_r(root->l) + NODEsize_r(root->r);
}

static int NODEisBalanced_r(link root) {
    if (root == NULL)
        return 1;

    int sL = NODEsize_r(root->l);
    int sR = NODEsize_r(root->r);

    if (abs(sL - sR) > 1)
        return 0;

    return NODEisBalanced_r(root->l) && NODEisBalanced_r(root->r);
}

int BSTisBalanced(BST b) {
    return NODEisBalanced_r(b->root);
}

*/