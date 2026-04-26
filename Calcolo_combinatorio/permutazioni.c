#include <stdio.h>
#include <stdlib.h>

// Permutazioni semplici
void perm(int *val, int n);
void perm_r(int level, int *val, int *sol, int *mark,int n);

// Permutazioni con ripetizioni
void perm_rip(int *val, int n);
void perm_rip_r(int level, int *val, int *sol, int n);


int main() {

    int val[] = {1,2,3};
    perm(val,3);

    return 0;
}

void perm_rip(int *val, int n) {
    int *sol = malloc(n * sizeof(int));
    perm_rip_r(0, val, sol, n);
    free(sol);
}

void perm_rip_r(int level, int *val, int *sol, int n) {
    int i;

    if (level == n) {
        for (i = 0; i < n; i++) {
            printf("%d ", sol[i]);
        }
        printf("\n");
        return;
    }

    for (i = 0; i < n; i++) {
        sol[level] = val[i];
        perm_rip_r(level + 1, val, sol, n);
    }
}

void perm(int *val, int n) {
    int *sol = malloc(n*sizeof(int));
    int *mark = calloc(n,sizeof(int));
    perm_r(0,val,sol,mark,n);
    free(sol);
    free(mark);
}


void perm_r(int level, int *val, int *sol, int *mark, int n) {
    int i;

    if (level >= n) {
        //STAMPA LA SOLUZIONE
        for (i = 0; i < n; i++) {
            printf("%d", sol[i]);
        }
        printf("\n");
        return;
    }

    for (i = 0; i<n; i++) {
        if (mark[i]==0) {
            sol[level]= val[i];
            mark[i] = 1;
            perm_r(level+1, val,sol,mark,n);
            mark[i] = 0;
        }
    }
}