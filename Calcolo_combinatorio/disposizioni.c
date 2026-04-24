#include <stdio.h>
#include <stdlib.h>

// Disposizioni con ripetizioni
void disp_rip(int *val, int n, int k);
void disp_rip_r(int level, int *val, int *sol, int n, int k);

// Dispozioni semplici
void disp(int *val, int n, int k);
void disp_r(int level, int *val, int *sol, int *mark, int n, int k);

int main(void) {
    int val[] = {1,2,3,4,5};
    int n = sizeof(val)/sizeof(val[0]);
    int k = 2;

    //disp_rip(val,n,k);
    disp(val,n,k);

    return 0;
}

void disp_rip(int *val, int n, int k) {
    int *sol = calloc(k, sizeof(int));
    disp_rip_r(0,val,sol,n,k);

    free(sol);
}

void disp_rip_r(int level, int *val, int *sol, int n, int k) {
    // Terminazione
    if (level >= k) {
        for (int i = 0; i < k; i++) {
            printf("%d ", sol[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        sol[level] = val[i];
        disp_rip_r(level+1,val,sol,n,k);
    }
}

// Disposizioni semplici
void disp(int *val, int n, int k) {
    int *sol = calloc(k, sizeof(int));
    int *mark = calloc(n, sizeof(int));
    disp_r(0,val,sol,mark,n,k);
    free(sol);
    free(mark);
}

void disp_r(int level, int *val, int *sol, int *mark, int n,int k) {
    if (level >= k) {
        for (int i = 0; i < k; i++) {
            printf("%d ", sol[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (mark[i] == 0) {
            sol[level] = val[i];
            mark[i] = 1;
            disp_r(level+1,val,sol,mark,n,k);
            mark[i] = 0;
        }
    }
}