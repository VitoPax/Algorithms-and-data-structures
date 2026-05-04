/*
    È dato un ADT List, in grado di rappresentare una lista (non ordinata) di stringhe (allocate dinamicamente).
    Si completi la funzione listDeleteLonger che, data la lista e una lunghezza (un valore intero lmax),
    elimini dalla lista le stringhe (e i relativi nodi) di lunghezza superiore a lmax.
    La funzione ritorna un risultato intero, che rappresenta il numero di cancellazioni effettuate.
    Completare il codice parziale utilizzando la numerazione riportata.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


int listDeleteLonger(List l, int lmax) {
    link x, p;
    int cnt = 0;

    for (x = l->head, p = NULL; x != NULL;) {
        if (strlen(x->val) > lmax) {
            link t;

            t = x->next;

            if (x == l->head) {
                l->head = x->next;
            } else {
                p->next = x->next;
            }

            free(x->val);
            free(x);

            x = t;
            // l->N--;  Solo se in List ho il numero di nodi
            cnt++;
        } else {
            p = x;
            x = x->next;
        }
    }

    return cnt;
}

int main(void) {
    List l = malloc(sizeof(*l));
    l->head = LINKnew("a", LINKnew("hello", LINKnew("world", LINKnew("test", LINKnew("programming", LINKnew("C", NULL))))));
    printf("initial LIST: \n");
    LINKprint(l->head);

    int deleted = listDeleteLonger(l, 4);
    printf("final LIST: \n");
    LINKprint(l->head);
    printf("Removed %d nodes\n", deleted);
    LINKfree(l->head);
    free(l);

    return 0;
}