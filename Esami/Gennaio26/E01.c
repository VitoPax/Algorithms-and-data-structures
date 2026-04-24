/*
    È dato un tipo struct node (e il relativo puntatore link) adatti a rappresentare nodi e puntatori in lista concatenata.

    typedef struct node {
    char *val;
    struct node *next;
    } *link;

    Il campo val punta a una stringa di proprietà del nodo. È data una lista (realizzata con questo tipo di dato) di stringhe,
    non ordinata e contenete eventuali dati ripetuti (anche più volte e non necessariamente contigui). Si consideri quale
    esempio, la lista seguente
    ->”Roma”->”Milano”->”Palermo”->”Roma”->”Torino”->”Genova”->”Roma”->”Palermo”
    Si realizzi la funzione avente prototipo
    link removeDupl(link h);
    in grado di rimuovere dalla lista gli elementi duplicati. Di ogni stringa replicata più di una volta va mantenuta la
    prima istanza. I dati rimasti debbono conservare l’ordina originale. La lista precedentemente esemplificata,
    diventerebbe
    ->”Roma”->”Milano”->”Palermo”->”Torino”->”Genova”
    Attenzione: non va generata una nuova lista ma occorre ritornare il puntatore alla lista modificata.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct node {
    char *val;
    struct node *next;
}*link;

struct list{
    link head;
    int N, maxN;           // N numero di Item e maxN numero Massimo di Item

};

link NEWnode(char *val, link next) {
    link x = malloc(sizeof(*x));


    if (x == NULL) {
        printf("Errore malloc\n");
        exit(1);
    }

    x->val = strdup(val);
    x->next = next;

    return x;
}

/*
void LISTinshead(LIST l, char *val) {
    l->head = NEWnode(val, l->head);
    l->N++;
}
*/


link removeDupl(link h) {
    link x0, x, p;

    for (x0 = h; x0 != NULL; x0 = x0->next) {
        for (p = x0, x = x0->next; x != NULL; x = p->next) {
            if (strcmp(x->val, x0->val) == 0) {
                p->next = x->next;
                free(x->val);
                free(x);
            } else {
                p = x;
            }
        }
    }

    return h;
}

void printList(link h) {
    for (; h != NULL; h = h->next) {
        printf("%s -> ", h->val);
    }
    printf("NULL\n");
}

void freeList(link h) {
    link tmp;

    while (h != NULL) {
        tmp = h;
        h = h->next;

        free(tmp->val);
        free(tmp);
    }
}


int main(void) {

    link h = NULL;

    h = NEWnode("tigre", h);
    h = NEWnode("topo", h);
    h = NEWnode("rinoceronte", h);
    h = NEWnode("gatto", h);
    h = NEWnode("lupo", h);
    h = NEWnode("cane", h);

    printf("Lista iniziale:\n");
    printList(h);

    h = removeDupl(h);

    printf("\nLista dopo removeDupl:\n");
    printList(h);

    freeList(h);


    return 0;
}