#include <stdio.h>

#include "list.h"

int main(void){
    LIST l;
    Item trovato;

    l = LISTinit();

    if (l == NULL) {
        printf("Errore nella creazione della lista\n");
        return 1;
    }

    printf("Lista iniziale:\n");
    LISTdisplay(l);

    if (LISTempty(l))
        printf("La lista e' vuota\n");

    /*
     * Inserimento in coda su lista vuota:
     * 20 -> NULL
     */
    LISTinsTail(l, 20);

    printf("\nDopo LISTinsTail(l, 20):\n");
    LISTdisplay(l);

    /*
     * Inserimento in testa:
     * 10 -> 20 -> NULL
     */
    LISTinsHead(l, 10);

    printf("\nDopo LISTinsHead(l, 10):\n");
    LISTdisplay(l);

    /*
     * Inserimento in coda su lista non vuota:
     * 10 -> 20 -> 30 -> NULL
     */
    LISTinsTail(l, 30);

    printf("\nDopo LISTinsTail(l, 30):\n");
    LISTdisplay(l);



    /* Test funzione di ricerca */
    printf("\n");
    trovato = LISTsearch(l, 20);
    if (KEYget(trovato) != -1)
        printf("Elemento trovato: %d\n", trovato);
    else
        printf("Elemento non trovato\n");


    trovato = LISTsearch(l, 50);
    if (KEYget(trovato) != -1)
        printf("Elemento trovato: %d\n", trovato);
    else
        printf("Elemento non trovato\n");

    /* Test cancellazione in testa */
    printf("Lista iniziale:\n");
    LISTdisplay(l);

    LISTdelHead(l);

    printf("Dopo la cancellazione dalla testa:\n");
    LISTdisplay(l);

    /* Test estrazione in testa */
    Item estratto;

    printf("Lista prima dell'estrazione:\n");
    LISTdisplay(l);

    estratto = LISTextractHead(l);

    if (estratto != ITEMsetvoid())
        printf("Elemento estratto: %d\n", estratto);
    else
        printf("Lista vuota\n");

    printf("Lista dopo l'estrazione:\n");
    LISTdisplay(l);

    /* Test estrazione chiave data */
    printf("Lista iniziale:\n");
    LISTdisplay(l);

    LISTdelKey(l, 20);

    printf("\nDopo la cancellazione di 20:\n");
    LISTdisplay(l);

    LISTdelKey(l, 10);

    printf("\nDopo la cancellazione della testa 10:\n");
    LISTdisplay(l);

    LISTdelKey(l, 50);

    printf("\nDopo il tentativo di cancellare 50:\n");
    LISTdisplay(l);

    /* TEST LISTA ORDINATA */
    LIST ordinata;

    ordinata = LISTinit();

    if (ordinata == NULL) {
        printf("Errore di allocazione\n");
        return 1;
    }

    printf("\nLista ordinata:\n");
    LISTsortIns(ordinata, 30);
    LISTsortIns(ordinata, 10);
    LISTsortIns(ordinata, 40);
    LISTsortIns(ordinata, 20);

    LISTdisplay(ordinata);

    return 0;
}