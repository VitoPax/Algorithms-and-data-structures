#include <stdio.h>
#include <stdlib.h>

/*
    Dato un insieme di n elementi (ad esempio numeri da 1 a n), devi stampare tutte le disposizioni semplici di k elementi,
    cioè tutte le sequenze ordinate senza ripetizione.

👉 In pratica: tutte le possibili sequenze di lunghezza k usando numeri da 1 a n, senza ripetere elementi.
*/


void stampa(int *sol, int k) {
    for (int i = 0; i < k; i++) {
        printf("%d ", sol[i]);
    }
    printf("\n");
}

void disp_r(int level, int *val, int *sol, int *mark, int n, int k) {
    if (level >= k) {
        stampa(sol, k);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[level] = val[i];

            disp_r(level + 1, val, sol, mark, n, k);

            mark[i] = 0;
        }
    }
}

void disp(int *val, int n, int k) {
    int *sol = malloc(k * sizeof(int));
    int *mark = calloc(n, sizeof(int));

    if (sol == NULL || mark == NULL) {
        printf("Errore di allocazione\n");
        free(sol);
        free(mark);
        return;
    }

    disp_r(0, val, sol, mark, n, k);

    free(sol);
    free(mark);
}

int main() {
    int val[] = {1, 2, 3};

    disp(val, 3, 2);

    return 0;
} 