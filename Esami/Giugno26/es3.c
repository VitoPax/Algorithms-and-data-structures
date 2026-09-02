/*
È dato un vettore di nomi (stringhe)
Si vuole generare un vettore di liste di nomi, nel quale, all’indice n si
trova la lista dei nomi aventi lunghezza n. Se ad esempio il vettore contenesse i nomi: “Bologna”, “Roma”,
“Napoli”, “Torino”, “Bari”, il  vettore avrebbe lunghezza 8 e conterrebbe, nelle 8 caselle,
 vett[0]: ∅
 vett[1]: ∅
 vett[2]: ∅
 vett[3]: ∅
 vett[4]: “Roma” → “Bari” → ∅
 vett[5]: ∅
 vett[6]: “Napoli” → “Torino” → ∅
 vett[7]: “Bologna” → ∅
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char *name; } Item;

typedef struct node {
    Item val;
    struct node *next;
} *link;

int GenListsByLength(char **names, int n, link **listArrayP);
static link newNode(Item item, link next);

static link newNode(Item val, link next) {
    link nuovo = malloc(sizeof *nuovo);
    if (nuovo == NULL) return NULL;
    nuovo->val.name = strdup(val.name);
    nuovo->next = next;
    return nuovo;
}

int GenListsByLength(char **names, int n, link **listArrayP) {
    int i, maxLen = 0, countChar = 0;
    Item tmp;
    link x;
    for (i = 0; i < n; i++) {
        countChar = strlen(names[i]);

        if (countChar > maxLen)
            maxLen = countChar;
    }

    *listArrayP = malloc((maxLen+1)*sizeof(link));
    if (*listArrayP == NULL)
        return 0;

    for (i = 0; i < maxLen+1; i++) {
        (*listArrayP)[i] = NULL;
    }

    for (i = 0; i< n; i++) {
        countChar = strlen(names[i]);
        tmp.name = names[i];

        if ((*listArrayP)[countChar] == NULL)
            (*listArrayP)[countChar] = newNode(tmp, NULL);
        else {
            for (x = (*listArrayP)[countChar]; x->next != NULL; x = x->next)
                ;
            x->next = newNode(tmp, NULL);
        }
    }

    return maxLen+1;
}


int main(int argc, char **argv) {
    /* you can implement your test case here [NOT NEEDED] */
    return 0;
}