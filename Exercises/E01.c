/*
 Dato un vettore di n interi distinti, scrivere una funzione ricorsiva che stampi tutte le disposizioni semplici
 di lunghezza k tali che la somma degli elementi scelti sia pari.
*/

#include <stdio.h>
#include <stdlib.h>

void disp(int *val , int n, int k);
void dispR(int level, int *val, int *sol, int *mark, int n, int k, int sum);
void stampaIF(int *sol, int k);

int main(void) {
    int val[] = {1, 2, 3, 4};
    disp(val, 4, 2);
    return 0;
}

void stampaIF(int *sol, int k) {
    for (int i = 0; i < k; i++) {
        printf("%d ", sol[i]);
    }
    printf("\n");
}

void disp(int *val, int n, int k) {
    int *sol = calloc(k, sizeof(int));
    int *mark = calloc(n, sizeof(int));

    dispR(0, val, sol, mark, n, k, 0);
    free(sol);
    free(mark);
}

void dispR(int level, int *val, int *sol, int *mark, int n, int k, int sum) {
    if (level == k) {
        if (sum % 2 == 0) {
            stampaIF(sol, k);
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[level] = val[i];
            dispR(level + 1, val, sol, mark, n, k, sum + val[i]);
            mark[i] = 0;
        }
    }
}