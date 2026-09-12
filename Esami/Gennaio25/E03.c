/*
Due stringhe s1 e s2 possono essere concatenate se il prefisso (proprio) di ordine l di s2 coincide col suffisso (proprio) di ordine l di s1.
Si ricorda che il prefisso (suffisso) di ordine l di una stringa è una sottostringa iniziale (terminale) di l elementi,
che si dice proprio se non coincide con la stringa stessa (l è minore della lunghezza della stringa).
Si scriva una funzione checkConcat che, date due stringhe, verifichi se possono essere concatenate.
Si scriva poi una funzione che, dato un insieme S di stringhe, trovi la più lunga sequenza di stringhe concatenabili, appartenenti all’insieme.
L’insieme S è rappresentato come vettore. Non sono ammesse ripetizioni.
come lunghezza (da massimizzare) si intende il conteggio delle stringhe nella sequenza.

La funzione abbia prototipo:

int maxConcatSeq(char **S, int n);

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkConcat(char *s1, char *s2) {
    int I, k, l1=strlen(s1), l2=strlen(s2);
    int minL = l1<l2?l1:l2;
    for (I=1; I<minL; I++) {
        int concat = 1;

        for (k = 0; k < I; k++)
            if (s1[l1 - I + k] != s2[k])
                concat = 0;

        if (concat)
            return 1;
    }
    return 0;
}

void maxConcatSeq_r(int level, char **S, int n, int *sol, int *mark,
                    int *best, int *bestSol) {
    int i;

    /* ogni nodo e' gia' una sequenza valida: valuto SEMPRE */
    if (level > *best) {
        *best = level;
        for (i = 0; i < level; i++)
            bestSol[i] = sol[i];
    }

    if (level >= n)                      /* guardia: array esauriti */
        return;

    for (i = 0; i < n; i++) {
        /* pruning: non usata, e concatenabile con la precedente */
        if (mark[i] == 0 &&
            (level == 0 || checkConcat(S[sol[level-1]], S[i]))) {

            sol[level] = i;              /* INDICI, non stringhe */
            mark[i] = 1;
            maxConcatSeq_r(level + 1, S, n, sol, mark, best, bestSol);
            mark[i] = 0;                 /* BACKTRACKING */
        }
    }
}

/* --------------------------- WRAPPER ------------------------------ */

int maxConcatSeq(char **S, int n) {
    int *sol    = malloc(n * sizeof(int));
    int *bestSol = malloc(n * sizeof(int));
    int *mark    = calloc(n, sizeof(int));
    int best = 0;
    int i;

    if (sol == NULL || bestSol == NULL || mark == NULL) {
        free(sol); free(bestSol); free(mark);
        return -1;
    }

    maxConcatSeq_r(0, S, n, sol, mark, &best, bestSol);

    printf("  sequenza (%d): ", best);
    for (i = 0; i < best; i++)
        printf("%s%s", S[bestSol[i]], i < best - 1 ? " -> " : "");
    printf("\n");

    free(sol);
    free(bestSol);
    free(mark);
    return best;
}

/* ---------------------------- MAIN -------------------------------- */

int main(void) {
    char *A[] = {"abc", "bcd", "cde", "xyz"};
    char *B[] = {"casa", "sale", "lego", "gomma"};
    char *C[] = {"aaa", "bbb", "ccc"};
    char *D[] = {"abc"};

    printf("A: abc bcd cde xyz\n");
    printf("  risultato = %d\n\n", maxConcatSeq(A, 4));

    printf("B: casa sale lego gomma\n");
    printf("  risultato = %d\n\n", maxConcatSeq(B, 4));

    printf("C: aaa bbb ccc  (nessuna concatenabile)\n");
    printf("  risultato = %d\n\n", maxConcatSeq(C, 3));

    printf("D: abc  (una sola stringa)\n");
    printf("  risultato = %d\n", maxConcatSeq(D, 1));

    return 0;
}