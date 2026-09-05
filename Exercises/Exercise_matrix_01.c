/*
Data una matrice di interi r × c allocata dinamicamente,
si scriva una funzione che restituisca by pointer un vettore allocato dinamicamente contenente,
per ogni riga, il valore massimo di quella riga. La funzione ritorni il numero di elementi del vettore.

int maxPerRiga(int **m, int r, int c, int **vp);

*/

#include <stdio.h>
#include <stdlib.h>

/* Versione con variabile v che muore dentro la funzione e assegnazione finale

int maxPerRiga(int **m, int r, int c, int **vp) {

    int i, j, maxTmp;
    int *v;

    v = malloc(r * sizeof(int));
    if (v == NULL) return -1;

    for (i = 0; i < r; i++) {
        maxTmp = m[i][0];
        for (j = 1; j < c; j++)
            if (m[i][j] > maxTmp)
                maxTmp = m[i][j];
        v[i] = maxTmp;
    }

    *vp = v;
    return r;
}

*/

int maxPerRiga(int **m, int r, int c, int **vp) {
    int i,j, maxTmp;

    *vp = malloc(r*sizeof(int));
    if (*vp == NULL) return -1;

    for (i=1; i<r; i++) {
        maxTmp = m[i][0];
        for (j=0; j<c; j++) {
            if (m[i][j] > maxTmp) {
                maxTmp = m[i][j];
            }

        }
        (*vp)[i] = maxTmp;
    }

    return r;
}