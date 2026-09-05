/*
È data una matrice di interi m di dimensioni r × c, allocata dinamicamente come vettore di puntatori a riga.
Si vuole ottenere il vettore di tutti gli elementi della matrice che sono massimi locali di riga
e di colonna contemporaneamente, cioè elementi m[i][j] tali che nessun altro elemento della riga i
e nessun altro elemento della colonna j sia maggiore di essi.

Il vettore risultato va allocato dinamicamente (della dimensione esatta, senza sprechi) e restituito by pointer.
La funzione ritorna il numero di elementi trovati, oppure -1 in caso di errore di allocazione.

int puntiSella(int **m, int r, int c, int **outP);

Esempio. Con la matrice

3  1  7
2  9  4
8  5  7

l'output è {7, 9}: il 7 in posizione (0,2) è il massimo della riga 0 e della colonna 2;
il 9 in (1,1) è massimo della riga 1 e della colonna 1. L'8 in (2,0) è massimo della colonna 0 ma non della riga 2.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int isMax(int **m, int r, int c, int i, int j) {
    int k;
    /* controllo la riga i: scorro le colonne */
    for (k = 0; k < c; k++)
        if (m[i][k] > m[i][j])
            return 0;
    /* controllo la colonna j: scorro le righe */
    for (k = 0; k < r; k++)
        if (m[k][j] > m[i][j])
            return 0;
    return 1;    /* nessuno lo supera */
}

int puntiSella(int **m, int r, int c, int **outP) {
    int i,j, maxLoc, count = 0,k = 0;

    for (i = 0; i <r; i++) {
        for (j = 0; j<c; j++) {
            if (isMax(m,r,c,i,j))
                count++;
        }
    }

    *outP = malloc(count*sizeof(int));
    if (*outP == NULL) return -1;

    for (i = 0; i <r; i++) {
        for (j = 0; j<c; j++) {
            if (isMax(m,r,c,i,j))
                (*outP)[k++] = m[i][j];
        }
    }
    

    return count;


}