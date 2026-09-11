#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ------------------------------------------------------------------
 * PROBLEMA
 * Data una matrice NxM di caratteri ('0' = casella libera, '1' =
 * occupata) e le coordinate di due caselle libere, determinare la
 * lunghezza del percorso minimo che le connette. Un percorso e' una
 * sequenza di caselle libere adiacenti in orizzontale o verticale;
 * la lunghezza e' il numero di caselle che lo compongono.
 *
 * MODELLO
 * A ogni passo si sceglie fra quattro direzioni (su, giu', sinistra,
 * destra): disposizioni con ripetizione di 4 valori. La lunghezza del
 * percorso NON e' nota a priori e va minimizzata, quindi la ricorsione
 * non scorre le caselle di un vettore sol[] ma si sposta sulla
 * griglia: lo stato e' la posizione corrente (r0,c0).
 *
 * VINCOLI (pruning): ci si sposta su una casella solo se
 *   - sta dentro la matrice
 *   - contiene '0'
 *   - non appartiene gia' al percorso corrente (mark)
 * Il marcatore e' una matrice NxM ed e' indispensabile: senza, la
 * ricorsione tornerebbe indietro all'infinito. Come per il mark[] delle
 * disposizioni semplici, va RIPRISTINATO in uscita: vieta di ripassare
 * nel percorso corrente, non in assoluto.
 *
 * Problema di OTTIMIZZAZIONE: si esplorano tutti i percorsi semplici
 * conservando la lunghezza minima.
 * ------------------------------------------------------------------ */

int  minPath(char **area, int N, int M, int r0, int c0, int r1, int c1);
void minPathR(int level, char **area, int **mark, int N, int M,
              int r0, int c0, int r1, int c1, int *min);
int  percorribile(char **area, int **mark, int N, int M, int r, int c);

/* ------------------------ CASELLA VALIDA -------------------------- */

int percorribile(char **area, int **mark, int N, int M, int r, int c) {
    if (r < 0 || r >= N || c < 0 || c >= M)     /* fuori dalla matrice */
        return 0;
    if (area[r][c] != '0')                      /* occupata */
        return 0;
    if (mark[r][c] != 0)                        /* gia' nel percorso */
        return 0;
    return 1;
}

/* -------------------------- RICORSIVA ----------------------------- */

/* level = numero di caselle del percorso corrente, casella attuale
   compresa (la chiamata iniziale parte da 1).                       */
void minPathR(int level, char **area, int **mark, int N, int M,
              int r0, int c0, int r1, int c1, int *min) {

    mark[r0][c0] = 1;                    /* casella nel percorso */

    if (r0 == r1 && c0 == c1) {          /* arrivato */
        if (level < *min)
            *min = level;
        mark[r0][c0] = 0;                /* smarcare PRIMA di uscire */
        return;
    }

    if (percorribile(area, mark, N, M, r0 - 1, c0))          /* su */
        minPathR(level + 1, area, mark, N, M, r0 - 1, c0, r1, c1, min);

    if (percorribile(area, mark, N, M, r0 + 1, c0))          /* giu' */
        minPathR(level + 1, area, mark, N, M, r0 + 1, c0, r1, c1, min);

    if (percorribile(area, mark, N, M, r0, c0 - 1))          /* sinistra */
        minPathR(level + 1, area, mark, N, M, r0, c0 - 1, r1, c1, min);

    if (percorribile(area, mark, N, M, r0, c0 + 1))          /* destra */
        minPathR(level + 1, area, mark, N, M, r0, c0 + 1, r1, c1, min);

    mark[r0][c0] = 0;                    /* BACKTRACKING */
}

/* --------------------------- WRAPPER ------------------------------ */

/* Ritorna la lunghezza minima, oppure -1 se le due caselle non sono
   connesse o i dati di ingresso non sono validi.                    */
int minPath(char **area, int N, int M, int r0, int c0, int r1, int c1) {
    int **mark;
    int min = INT_MAX;
    int i, j;

    if (area[r0][c0] != '0' || area[r1][c1] != '0')
        return -1;                       /* estremi non liberi */

    mark = malloc(N * sizeof(int *));    /* matrice NxM azzerata */
    if (mark == NULL)
        return -1;
    for (i = 0; i < N; i++) {
        mark[i] = calloc(M, sizeof(int));
        if (mark[i] == NULL) {
            for (j = 0; j < i; j++)
                free(mark[j]);
            free(mark);
            return -1;
        }
    }

    minPathR(1, area, mark, N, M, r0, c0, r1, c1, &min);

    for (i = 0; i < N; i++)
        free(mark[i]);
    free(mark);

    return min == INT_MAX ? -1 : min;    /* nessun percorso trovato */
}

/* ---------------------------- TEST -------------------------------- */

void prova(char **area, int N, int M, int r0, int c0, int r1, int c1,
           int atteso) {
    int r = minPath(area, N, M, r0, c0, r1, c1);
    printf("  (%d,%d) -> (%d,%d) : %d  (atteso %d) %s\n",
           r0, c0, r1, c1, r, atteso, r == atteso ? "" : "<-- ERRORE");
}

int main(void) {
    /* esempio della traccia: percorso ottimo di lunghezza 5 */
    char *a[] = {"01000",
                 "00010",
                 "01000",
                 "00000"};
    /* due zone separate da un muro verticale */
    char *b[] = {"010",
                 "010",
                 "010"};
    int i;

    printf("Matrice A:\n");
    for (i = 0; i < 4; i++)
        printf("    %s\n", a[i]);
    prova(a, 4, 5, 1, 0, 2, 3, 5);
    prova(a, 4, 5, 0, 0, 0, 0, 1);       /* stessa casella */
    prova(a, 4, 5, 1, 0, 3, 4, 7);       /* 6 passi = 7 caselle */

    printf("\nMatrice B (muro verticale):\n");
    for (i = 0; i < 3; i++)
        printf("    %s\n", b[i]);
    prova(b, 3, 3, 0, 0, 0, 2, -1);      /* non connesse */

    return 0;
}