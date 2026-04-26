#include <stdio.h>
#include <stdlib.h>

/* DEFINIZIONE POWERSET
 * Trovare tutti i possibili sottoinsiemi S di un insieme
*/

int cnt;

// Divide et impera
void powerset(int *val,int n);
void powerset_r(int level, int *val, int *sol, int n, int start);

// Disposizioni con ripetizioni
void powersetDISP(int *val, int n);
void powersetDISP_r(int level,int *val, int *sol, int n);

// Combinazioni con ripetizioni
void powersetCOMB(int *val, int n);
void powersetCOMB_r(int level,int *val, int *sol, int n,int k,  int start);


int main() {
    int set[] = {1, 2, 3};
    int n = sizeof(set) / sizeof(set[0]);

    powerset(set, n);
    //powersetDISP(set,n);
    //powersetCOMB(set,n);

    return 0;
}


// Divide et impera
void powerset(int *val, int n) {
    int *sol = calloc(n, sizeof(int));
    powerset_r(0,val,sol,n,0);
    free(sol);

}

void powerset_r(int level,int *val, int *sol, int n, int start) {

    // stampo il sottoinsieme corrente
    printf("{ ");
    for (int i = 0; i < level; i++) {
        printf("%d ", sol[i]);
    }
    printf("}\n");

    for (int i = start; i < n; i++) {
        sol[level] = val[i];
        powerset_r(level+1, val,sol,n,i+1);
    }
}

// Powerset con disposizioni
void powersetDISP(int *val, int n) {
    int *sol = calloc(n, sizeof(int));
    cnt = 1;
    powersetDISP_r(0,val,sol,n);
    free(sol);
}

void powersetDISP_r(int level,int *val, int *sol, int n) {
    if (level >=n) {
        printf("{ ");
        for (int i = 0; i < n; i++) {
            if (sol[i]) {
                printf("%d ", val[i]);
            }
        }
        printf("}\n");
        // Volendo contare aggiungo cnt
        printf("%d\n", cnt++);
        return ;
    }


    // i-esimo livello escluso
    sol[level] = 0;
    powersetDISP_r(level+1,val,sol,n);

    // i-esimo livello incluso
    sol[level] = 1;
    powersetDISP_r(level+1,val,sol,n);
}


// Combinazioni
void powersetCOMB(int *val, int n) {
    int *sol = calloc(n, sizeof(int));
    for (int k = 0; k <= n; k++) {
        powersetCOMB_r(0,val,sol,n,k,0);
    }
}


void powersetCOMB_r(int level, int *val, int *sol, int n, int k, int start) {
    if (level >=k) {
        printf("{ ");
        for (int i = 0; i < k; i++) {
            printf("%d ", sol[i]);
        }
        printf("}\n");
        return;
    }

    for (int i = start; i<n; i++) {
        sol[level] = val[i];
        powersetCOMB_r(level+1,val,sol,n,k,i+1);     // start = i
    }
}