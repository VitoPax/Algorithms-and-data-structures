/*
 Dato un vettore di n interi distinti, scrivere una funzione ricorsiva che stampi tutte le disposizioni semplici
 di lunghezza k tali che la somma degli elementi scelti sia pari.
*/

#include <stdio.h>
#include <stdlib.h>

void disp(int *val , int n, int k);
int dispR(int level, int *val, int *sol, int *mark, int n, int k);
void stampaIF(int *sol, int k);

int main(void) {
    int val[] = {1, 2, 3, 4};
    disp(val,4,2);
    return 0;
}

void stampIF(int *sol, int k) {
    for (int i = 0; i < k; i++) {
        printf("%d", sol[i]);
    }
}

void disp(int *val, int n, int k) {
    int *sol = calloc(k,sizeof(int));
    int *mark = calloc(n,sizeof(int));
    dispR(0, val, sol, mark, n, k);
    free(sol);
    free(mark);
}

int dispR(int level, int *val, int *sol, int *mark, int n, int k) {
    int sum = 0;

    if (level >= n && sum % 2 == 0) {
        stampaIF(sol, k);
    }

    for (int i = 0; i < n; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[level] = val[i];
            sum = sum + sol[i];
            mark[i] = 0; // Backtracking
        }
    }

    return sum;
}