#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "bst.h"

int main(void) {
    BST b;
    Item x;
    int cnt;

    b = BSTinit();

    strcpy(x.name, "Milano");
    BSTinsert_leafR(b, x);

    strcpy(x.name, "Roma");
    BSTinsert_leafR(b, x);

    strcpy(x.name, "Torino");
    BSTinsert_leafR(b, x);

    strcpy(x.name, "Bologna");
    BSTinsert_leafR(b, x);

    strcpy(x.name, "Napoli");
    BSTinsert_leafR(b, x);

    strcpy(x.name, "Firenze");
    BSTinsert_leafR(b, x);

    strcpy(x.name, "Genova");
    BSTinsert_leafR(b, x);

    /* chiavi presenti */
    cnt = BSTcountBetween(b, "Bologna", "Roma");
    printf("Nodi tra Bologna e Roma: %d\n", cnt);

    /* chiavi presenti ma invertite */
    cnt = BSTcountBetween(b, "Roma", "Bologna");
    printf("Nodi tra Roma e Bologna: %d\n", cnt);

    /* una chiave assente */
    cnt = BSTcountBetween(b, "Bologna", "Venezia");
    printf("Nodi tra Bologna e Venezia: %d\n", cnt);

    /* entrambe presenti ma magari nessun nodo in mezzo */
    cnt = BSTcountBetween(b, "Potenza", "Milano");
    printf("Nodi tra Potenza e Milano: %d\n", cnt);

    /* test per l'esercizio BSTcountGreater */

    printf("\n--- Test BSTcountGreater ---\n");

    cnt = BSTcountGreater(b, "Roma");
    printf("Nodi con chiave maggiore di Roma: %d\n", cnt);

    cnt = BSTcountGreater(b, "Milano");
    printf("Nodi con chiave maggiore di Milano: %d\n", cnt);

    cnt = BSTcountGreater(b, "Torino");
    printf("Nodi con chiave maggiore di Torino: %d\n", cnt);

    cnt = BSTcountGreater(b, "Aosta");
    printf("Nodi con chiave maggiore di Aosta: %d\n", cnt);

    cnt = BSTcountGreater(b, "Catania");
    printf("Nodi con chiave maggiore di Catania: %d\n", cnt);

    return 0;
}