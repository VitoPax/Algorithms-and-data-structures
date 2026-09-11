/*
Sono dati due vettori di interi ordinati in modo crescente e privi di ripetizioni.
Si scriva una funzione che generi un vettore (allocato dinamicamente) contenente gli interi appartenenti al primo vettore e non al secondo.
La funzione deve essere chiamata come segue:

c = diffVett(a,na,b,nb,&nc);

a e b sono i due vettori, na e nb il numero di dati che contengono; c è il vettore risultato,
allocato dinamicamente nella funzione, nc il numero di interi nel vettore risultato.

Si richiede di realizzare (SOLO) la funzione diffVett (quindi non del programma chiamante).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Soluzione mia NON ottimale

int *diffVett(int *a, int na, int *b, int nb, int *nc) {
    int i,j;
    *nc = 0;
    int k = 0;

    for (i = 0; i < na; i++) {
        int trovato = 0;
        for (j=0; j < nb; j++) {
            if (a[i] == b[j]) {
                trovato = 1;
            }
        }

        if (!trovato)
            (*nc)++;
    }

    int *c = malloc((*nc)*sizeof(int));

    for (i = 0; i < na; i++) {
        int trovato = 0;
        for (j=0; j < nb; j++) {
            if (a[i] == b[j]) {
                trovato = 1;
            }
        }

        if (!trovato)
            c[k++] = a[i];
    }

    return c;
}


int *diffVettOPT(int *a, int na, int *b, int nb, int *nc) {
    int i = 0, j = 0, k = 0;

    int *c = malloc(na * sizeof(int));

    while (i < na && j < nb) {

        if (a[i] < b[j]) {
            c[k++] = a[i];
            i++;
        }
        else if (a[i] > b[j]) {
            j++;
        }
        else {
            // a[i] == b[j], quindi non va inserito
            i++;
            j++;
        }
    }

    // Se b è terminato, tutti gli elementi rimasti in a
    // appartengono alla differenza
    while (i < na) {
        c[k++] = a[i];
        i++;
    }

    *nc = k;

    c = realloc(c, (*nc) * sizeof(int));

    return c;
}