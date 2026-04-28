#include <stdio.h>
#include "bst.h"

int main(void) {
    BST bst;
    Item x;
    Item found;

    /*
     * Creo un BST vuoto.
     */
    bst = BSTinit();

    /*
     * Inserimento in foglia ricorsivo.
     */
    x = (Item){"mario"};
    BSTinsert_leafR(bst, x);

    x = (Item){"anna"};
    BSTinsert_leafR(bst, x);

    x = (Item){"zorro"};
    BSTinsert_leafR(bst, x);

    /*
     * Inserimento in radice.
     * "luca" verrà inserito e portato in radice tramite rotazioni.
     */
    x = (Item){"luca"};
    BSTinsert_root(bst, x);

    /*
     * Visita inorder:
     * in un BST stampa gli elementi in ordine crescente.
     */
    printf("Visita inorder: ");
    BSTvisit(bst, INORDER);
    printf("\n");

    /*
     * Ricerca.
     */
    found = BSTsearch(bst, "anna");

    if (!ITEMcheckNull(found)) {
        printf("Trovato: ");
        ITEMstore(found);
        printf("\n");
    } else {
        printf("Non trovato\n");
    }

    /*
     * Minimo.
     */
    printf("Min: ");
    ITEMstore(BSTmin(bst));
    printf("\n");

    /*
     * Massimo.
     */
    printf("Max: ");
    ITEMstore(BSTmax(bst));
    printf("\n");

    /*
     * Numero di nodi.
     */
    printf("Numero nodi: %d\n", BSTcount(bst));

    /*
     * Deallocazione finale.
     */
    BSTfree(bst);

    return 0;
}