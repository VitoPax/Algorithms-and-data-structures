/*
Si scriva una funzione che dato un insieme di N numeri interi, ricevuto in un vettore, e un valore intero M, determini e
stampi il sottoinsieme di numeri la cui somma S si avvicina maggiormente (per difetto)a M (si minimizzi la differenza
M-S, di valore >=0). In caso di parita' si scelga l'insieme con piu' numeri.

Esempio

Numeri: 3,7,8,4,20,14
M: 18
Soluzione: 7,8,3 (somma 18), anche 4,14 ha somma 18, ma sono due numeri ( contro 3).

prototipo:
void maxSubs(int *V, int N, int M);
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void maxSubs(int *V, int N, int M);
void maxSubs_r(int level, int start, int *V, int N, int M, int k,
               int *sol, int *best, int *bestDiff, int *bestCount);
void bestSol(int *V, int *sol, int k, int M,
             int *best, int *bestDiff, int *bestCount);

/* --------------------------- BESTSOL ------------------------------ */

/* Verifica il sottoinsieme individuato dagli indici in sol e, se
   migliora la soluzione corrente, lo conserva in best.
   Ammissibilita': la somma non deve superare M.
   Criterio primario:   differenza M-S minore.
   Criterio secondario: a parita' di differenza, cardinalita' maggiore. */

void bestSol(int *V, int *sol, int k, int M,
             int *best, int *bestDiff, int *bestCount) {
    int i, sum = 0, diff;

    for (i = 0; i < k; i++)
        sum += V[sol[i]];

    if (sum > M)                             /* non ammissibile */
        return;

    diff = M - sum;

    if (diff < *bestDiff || (diff == *bestDiff && k > *bestCount)) {
        *bestDiff  = diff;
        *bestCount = k;
        memcpy(best, sol, k * sizeof(int));
    }
}

/* -------------------------- RICORSIVA ----------------------------- */

/* Genera le combinazioni semplici di k indici su N in ordine crescente.
   Non contiene alcuna logica applicativa: nel caso base delega.      */
void maxSubs_r(int level, int start, int *V, int N, int M, int k,
               int *sol, int *best, int *bestDiff, int *bestCount) {
    int i;

    if (level >= k) {                        /* sottoinsieme completo */
        bestSol(V, sol, k, M, best, bestDiff, bestCount);
        return;
    }

    for (i = start; i < N; i++) {
        sol[level] = i;                      /* indici, non valori */
        maxSubs_r(level + 1, i + 1, V, N, M, k,
                  sol, best, bestDiff, bestCount);
    }
}

/* --------------------------- WRAPPER ------------------------------ */

void maxSubs(int *V, int N, int M) {
    int *sol  = malloc(N * sizeof(int));
    int *best = malloc(N * sizeof(int));
    int bestDiff  = pow(2,8*sizeof(int)-1);
    int bestCount = -1;
    int k, i;

    if (sol == NULL || best == NULL) {
        printf("Errore di allocazione\n");
        free(sol);
        free(best);
        return;
    }

    /* k = 0 incluso: se ogni numero supera M la soluzione ottima e'
       l'insieme vuoto, con somma 0 e differenza M.                   */
    for (k = 0; k <= N; k++)
        maxSubs_r(0, 0, V, N, M, k, sol, best, &bestDiff, &bestCount);

    printf("Soluzione ottima: { ");
    for (i = 0; i < bestCount; i++)
        printf("%d ", V[best[i]]);
    printf("}  somma = %d, M-S = %d\n", M - bestDiff, bestDiff);

    free(sol);
    free(best);
}

int main(void) {
    int V[] = {3, 7, 8, 4, 20, 14};
    int N = 6;
    int M = 18;

    printf("Vettore: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", V[i]);
    }

    printf("\nM = %d\n", M);

    printf("Sottoinsieme migliore: ");
    maxSubs(V, N, M);

    return 0;
}