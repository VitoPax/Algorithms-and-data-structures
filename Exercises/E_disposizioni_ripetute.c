/*
Dato un insieme di n elementi (ad esempio numeri da 1 a n), devi stampare tutte le disposizioni, ammettendo ripetizioni di k elementi,
    cioè tutte le sequenze ordinate senza ripetizione.
*/

#include <stdio.h>
#include <stdlib.h>

void disp_rip(int *val, int n, int k);
void disp_ripR(int level, int *val, int *sol, int n, int k);
void stampaSol(int *sol, int k);

int main(void) {

    int vett[] = {1,2,3};
    disp_rip(vett,3,2);

    return 0;
}

void stampaSol(int *sol, int k) {
    int i;
    for (i = 0; i< k; i++) {
        printf("%d", sol[i]);
    }
    printf("\n");
}


void disp_rip(int *val, int n, int k) {
    int *sol = calloc(k,sizeof(int));
    disp_ripR(0,val,sol,n,k);
    free(sol);
}

void disp_ripR(int level, int *val, int *sol, int n, int k) {
    if (level >= n) {
        stampaSol(val,k);
        return;
    }


    for (int i = 0; i < n; i++) {
        sol[level] = val[i];
        disp_ripR(level+1,val,sol,n,k);
    }
}