/*
Scrivi la funzione:
int listDeleteYoung(List l, int minAge);
che deve eliminare dalla lista tutti i nodi contenenti persone con età strettamente minore di minAge.

La funzione deve:
    liberare correttamente tutta la memoria associata al nodo eliminato, compresa val.name;
    gestire correttamente anche la cancellazione della testa;
    gestire più cancellazioni consecutive;
    restituire il numero di nodi eliminati.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int age;
} Item;

typedef struct node *link;

struct node {
    Item val;
    link next;
};

typedef struct list *List;

struct list {
    link head;
};

link newNode(Item val, link next) {
    link x = malloc(sizeof(*x));

    x->val.name = strdup(val.name);
    x->val.age = val.age;
    x->next = next;

    return x;
}

void listInsertHead(List l, Item val) {
    l->head = newNode(val, l->head);
}

int listDeleteYoung(List l, int minAge) {
    link x, p, t;
    int cnt = 0;

    for (x = l->head, p = NULL; x != NULL;) {

        t = x->next;

        if (x->val.age < minAge) {

            if (p == NULL)
                l->head = t;
            else
                p->next = t;

            free(x->val.name);
            free(x);

            x = t;
            cnt++;
        }
        else {
            p = x;
            x = x->next;
        }
    }

    return cnt;
}

void listPrint(List l) {
    link x;

    for (x = l->head; x != NULL; x = x->next) {
        printf("%s %d\n", x->val.name, x->val.age);
    }
}

int main(void) {
    List l = malloc(sizeof(*l));
    l->head = NULL;

    Item a = {"Giulia", 31};
    Item b = {"Marco", 15};
    Item c = {"Anna", 17};
    Item d = {"Luca", 25};

    listInsertHead(l, a);
    listInsertHead(l, b);
    listInsertHead(l, c);
    listInsertHead(l, d);

    printf("Lista iniziale:\n");
    listPrint(l);

    int deleted = listDeleteYoung(l, 18);

    printf("\nNodi cancellati: %d\n", deleted);

    printf("\nLista finale:\n");
    listPrint(l);

    return 0;
}