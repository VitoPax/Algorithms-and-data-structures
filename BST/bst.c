#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/*
 * link è un puntatore a un nodo del BST.
 */
typedef struct BSTnode *link;

/*
 * Nodo del BST.
 *
 * Ogni nodo contiene:
 * - item
 * - puntatore al figlio sinistro
 * - puntatore al figlio destro
 */
struct BSTnode {
    Item item;
    link l;
    link r;
};

/*
 * Struttura principale del BST.
 *
 * root = radice dell'albero
 * z    = nodo sentinella
 *
 * In questo progetto NON usiamo NULL per indicare sottoalberi vuoti.
 * Usiamo bst->z.
 */
struct bst {
    link root;
    link z;
};

/*
 * Crea un nuovo nodo.
 *
 * item = valore salvato nel nodo
 * l    = figlio sinistro
 * r    = figlio destro
 */
static link NEW(Item item, link l, link r) {
    link x;

    x = malloc(sizeof(*x));

    if (x == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }

    x->item = item;
    x->l = l;
    x->r = r;

    return x;
}

/*
 * Inizializza un BST vuoto.
 *
 * Il BST vuoto ha:
 * - una sentinella z
 * - root che punta a z
 *
 * Inoltre facciamo puntare z->l e z->r a z stesso.
 */
BST BSTinit(void) {
    BST bst;

    bst = malloc(sizeof(*bst));

    if (bst == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }

    bst->z = NEW(ITEMsetNull(), NULL, NULL);

    bst->z->l = bst->z;
    bst->z->r = bst->z;

    bst->root = bst->z;

    return bst;
}

/*
 * Dealloca ricorsivamente tutti i nodi del BST.
 *
 * Caso base:
 * se h == z, il sottoalbero è vuoto.
 */
static void treeFree(link h, link z) {
    if (h == z) {
        return;
    }

    treeFree(h->l, z);
    treeFree(h->r, z);

    free(h);
}

/*
 * Libera tutto il BST.
 *
 * Prima libera i nodi veri,
 * poi libera la sentinella,
 * poi libera la struct bst.
 */
void BSTfree(BST bst) {
    if (bst == NULL) {
        return;
    }

    treeFree(bst->root, bst->z);

    free(bst->z);
    free(bst);
}

/*
 * Conta i nodi del sottoalbero radicato in h.
 */
static int countR(link h, link z) {
    if (h == z) {
        return 0;
    }

    return countR(h->l, z) + countR(h->r, z) + 1;
}

/*
 * Conta tutti i nodi del BST.
 */
int BSTcount(BST bst) {
    if (bst == NULL) {
        return 0;
    }

    return countR(bst->root, bst->z);
}

/*
 * Ritorna 1 se il BST è vuoto, 0 altrimenti.
 */
int BSTempty(BST bst) {
    if (bst == NULL) {
        return 1;
    }

    return bst->root == bst->z;
}

/*
 * Ricerca ricorsiva.
 *
 * Se h == z:
 *   la chiave non è stata trovata.
 *
 * Se k == chiave del nodo:
 *   ricerca riuscita.
 *
 * Se k < chiave del nodo:
 *   cerco nel sottoalbero sinistro.
 *
 * Se k > chiave del nodo:
 *   cerco nel sottoalbero destro.
 */
static Item searchR(link h, Key k, link z) {
    int cmp;

    if (h == z) {
        return ITEMsetNull();
    }

    cmp = KEYcmp(k, KEYget(&h->item));

    if (cmp == 0) {
        return h->item;
    }

    if (cmp < 0) {
        return searchR(h->l, k, z);
    }

    return searchR(h->r, k, z);
}

/*
 * Wrapper pubblico della ricerca.
 */
Item BSTsearch(BST bst, Key k) {
    if (bst == NULL) {
        return ITEMsetNull();
    }

    return searchR(bst->root, k, bst->z);
}

/*
 * Inserimento ricorsivo in foglia.
 *
 * Funziona come una ricerca:
 * - se la posizione è vuota, creo il nodo
 * - se x < h->item, inserisco a sinistra
 * - se x > h->item, inserisco a destra
 *
 * Se la chiave è già presente, non inserisco duplicati.
 */
static link insertR(link h, Item x, link z) {
    int cmp;

    if (h == z) {
        return NEW(x, z, z);
    }

    cmp = KEYcmp(KEYget(&x), KEYget(&h->item));

    if (cmp < 0) {
        h->l = insertR(h->l, x, z);
    } else if (cmp > 0) {
        h->r = insertR(h->r, x, z);
    }

    return h;
}

/*
 * Wrapper pubblico dell'inserimento ricorsivo in foglia.
 */
void BSTinsert_leafR(BST bst, Item x) {
    if (bst == NULL) {
        return;
    }

    bst->root = insertR(bst->root, x, bst->z);
}

/*
 * Inserimento iterativo in foglia.
 *
 * Usiamo due puntatori:
 * - h scorre l'albero
 * - p resta indietro e rappresenta il padre di h
 *
 * Quando h arriva alla sentinella z,
 * abbiamo trovato il punto in cui attaccare il nuovo nodo.
 */
void BSTinsert_leafI(BST bst, Item x) {
    link h;
    link p;
    link n;
    int cmp;

    if (bst == NULL) {
        return;
    }

    /*
     * Caso albero vuoto.
     */
    if (bst->root == bst->z) {
        bst->root = NEW(x, bst->z, bst->z);
        return;
    }

    h = bst->root;
    p = bst->z;

    /*
     * Cerco la posizione di inserimento.
     */
    while (h != bst->z) {
        p = h;

        cmp = KEYcmp(KEYget(&x), KEYget(&h->item));

        if (cmp == 0) {
            return;
        }

        if (cmp < 0) {
            h = h->l;
        } else {
            h = h->r;
        }
    }

    /*
     * Creo il nuovo nodo.
     */
    n = NEW(x, bst->z, bst->z);

    /*
     * Lo collego come figlio sinistro o destro di p.
     */
    if (KEYcmp(KEYget(&x), KEYget(&p->item)) < 0) {
        p->l = n;
    } else {
        p->r = n;
    }
}

/*
 * Minimo del sottoalbero.
 *
 * In un BST il minimo si trova andando sempre a sinistra.
 */
static Item minR(link h, link z) {
    if (h == z) {
        return ITEMsetNull();
    }

    if (h->l == z) {
        return h->item;
    }

    return minR(h->l, z);
}

/*
 * Wrapper pubblico del minimo.
 */
Item BSTmin(BST bst) {
    if (bst == NULL) {
        return ITEMsetNull();
    }

    return minR(bst->root, bst->z);
}

/*
 * Massimo del sottoalbero.
 *
 * In un BST il massimo si trova andando sempre a destra.
 */
static Item maxR(link h, link z) {
    if (h == z) {
        return ITEMsetNull();
    }

    if (h->r == z) {
        return h->item;
    }

    return maxR(h->r, z);
}

/*
 * Wrapper pubblico del massimo.
 */
Item BSTmax(BST bst) {
    if (bst == NULL) {
        return ITEMsetNull();
    }

    return maxR(bst->root, bst->z);
}

/*
 * Visita ricorsiva dell'albero.
 *
 * PREORDER:
 *   stampa radice, sinistra, destra
 *
 * INORDER:
 *   stampa sinistra, radice, destra
 *   In un BST stampa le chiavi in ordine crescente.
 *
 * POSTORDER:
 *   stampa sinistra, destra, radice
 */
static void treePrintR(link h, link z, int strategy) {
    if (h == z) {
        return;
    }

    if (strategy == PREORDER) {
        ITEMstore(h->item);
        printf(" ");
    }

    treePrintR(h->l, z, strategy);

    if (strategy == INORDER) {
        ITEMstore(h->item);
        printf(" ");
    }

    treePrintR(h->r, z, strategy);

    if (strategy == POSTORDER) {
        ITEMstore(h->item);
        printf(" ");
    }
}

/*
 * Wrapper pubblico della visita.
 */
void BSTvisit(BST bst, int strategy) {
    if (bst == NULL || BSTempty(bst)) {
        return;
    }

    treePrintR(bst->root, bst->z, strategy);
}

/*
 * Rotazione a destra.
 *
 * Forma iniziale:
 *
 *        h
 *       /
 *      x
 *       \
 *        beta
 *
 * Dopo rotazione:
 *
 *        x
 *         \
 *          h
 *         /
 *      beta
 */
static link rotR(link h) {
    link x;

    x = h->l;

    h->l = x->r;
    x->r = h;

    return x;
}

/*
 * Rotazione a sinistra.
 *
 * Forma iniziale:
 *
 *      h
 *       \
 *        x
 *       /
 *    beta
 *
 * Dopo rotazione:
 *
 *        x
 *       /
 *      h
 *       \
 *      beta
 */
static link rotL(link h) {
    link x;

    x = h->r;

    h->r = x->l;
    x->l = h;

    return x;
}

/*
 * Inserimento in radice.
 *
 * L'idea è:
 * - inserisco ricorsivamente nel sottoalbero corretto
 * - quando risalgo, ruoto
 *
 * Se inserisco a sinistra:
 *   rotazione a destra
 *
 * Se inserisco a destra:
 *   rotazione a sinistra
 *
 * Così il nuovo nodo viene portato in radice.
 */
static link insertT(link h, Item x, link z) {
    int cmp;

    if (h == z) {
        return NEW(x, z, z);
    }

    cmp = KEYcmp(KEYget(&x), KEYget(&h->item));

    if (cmp < 0) {
        h->l = insertT(h->l, x, z);
        h = rotR(h);
    } else if (cmp > 0) {
        h->r = insertT(h->r, x, z);
        h = rotL(h);
    }

    return h;
}

/*
 * Wrapper pubblico dell'inserimento in radice.
 */
void BSTinsert_root(BST bst, Item x) {
    if (bst == NULL) {
        return;
    }

    bst->root = insertT(bst->root, x, bst->z);
}