/*
È dato un tipo struct node (e il puntatore link) adatti a rappresentare nodi e puntatori in lista concatenata.
Sono date due liste ordinate in modo crescente, prive di duplicati.
È possibile che due liste abbiano una parte in comune, nel senso che il puntatore next di un nodo in una lista può puntare a un nodo di un’altra lista.
Date le due liste, si vogliono contare, nel modo più efficiente possibile (un algoritmo lineare), i nodi comuni.
La funzione ritorna come risultato il numero di nodi comuni (0 indica quindi che non ci sono nodi comuni).
Completare il codice parziale utilizzando la numerazione riportata
*/

#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    char *val;
    struct node *next;
} *link;


int countCommonNodes(link h1, link h2) {
    link p1, p2;
    int cnt = 0;

    for (p1 = h1, p2 = h2; p1 != NULL; p1 = p1->next) {
        if (p1->val == p2->val) {
            cnt++; // Trovato nodo comune
        } else {
            p2 = p2->next;
        }
    }
    return cnt;
}
