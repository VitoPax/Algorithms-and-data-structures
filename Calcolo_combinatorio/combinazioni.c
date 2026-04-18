#include <stdio.h>
#include <stdlib.h>


void comb_rip(int *val, int n, int k);
void comb_rip_r(int level, int *val, int *sol, int n, int k, int start);

void comb(int *val, int n, int k);
void comb_r(int level, int *val, int *sol, int n, int k, int start);

int main(void) {
    int val[] = {1,2,3,4,5,6};
    int n = sizeof(val)/sizeof(val[0]);
    int k = 2;

    comb(val,n,k);

    return 0;

}


//Combinazioni ripetute
void comb_rip(int *val, int n, int k){
    int *sol = calloc(k, sizeof(int));
    comb_rip_r(0,val,sol,n,k,0);
    free(sol);
}

void comb_rip_r(int level, int *val, int *sol, int n, int k, int start) {
    if (level >=k) {
        for (int i = 0; i < k; i++) {
            printf("%d ", sol[i]);
        }
        printf("\n");
        return;
    }

    for (int i = start; i<n; i++) {
        sol[level] = val[i];
        comb_rip_r(level+1,val,sol,n,k,i);     // start = i
    }
}

// Combinazioni semplici
void comb(int *val, int n, int k) {
    int *sol = calloc(k, sizeof(int));
    comb_r(0,val,sol,n,k,0);
    free(sol);
}

void comb_r(int level, int *val, int *sol, int n, int k, int start) {
    if (level >=k) {
        for (int i = 0; i < k; i++) {
            printf("%d ", sol[i]);
        }
        printf("\n");
        return;
    }

    for (int i = start; i<n; i++) {
        sol[level] = val[i];
        comb_r(level+1,val,sol,n,k,i+1);
    }
}