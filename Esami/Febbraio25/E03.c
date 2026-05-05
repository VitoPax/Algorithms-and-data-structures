/*
È dato un vettore V contenente N interi non negativi: il vettore non è ordinato e sono possibili dati ripetuti. Si
vogliono generare, come risultato, due vettori (allocati dinamicamente) V1 e V2, in cui suddividere gli interi, in
modo tale che, date la somma S1 degli interi in V1 e la somma S2 degli interi in S2, si minimizzi |S2-S1|. La
funzione deve poter essere chiamata come segue:
int N1, N2, *V1, *V2;
N1 = bestSplit(V, N, &V1, &V2);
N2 = N-N1;
V1 e V2 sono (puntatori a) vettori di interi che vanno allocati dinamicamente nella bestSplit, N1 è il numero di
interi in V1, mentre N2 è il numero di interi in V2. Si riporta una soluzione parziale che va completata

*/

#include <stdio.h>
#include <stdlib.h>

/* Prototipo della tua funzione */
int bestSplit(int *V, int N, int **V1p, int **V2p);

int checkTerminal(int n,int start,int sum,int goal) {
    if (start >= n)
        return 1;

    return 0;
}

void checkBestSol(int n,int *sol,int *bestSol,int sum,int *bestSumP,int goal) {
    // Terminazione perche' non ho una soluzione migliore di quella gia' trovata
    if (abs(sum - goal) > abs(*bestSumP - goal))
        return;

    *bestSumP = sum;
    for (int i = 0; i < n; i++) {
        bestSol[i] = sol[i];
    }

}


int buildSol(int *V, int N, int *bestSol, int **V1p, int **V2p) {
    int n1 = 0;

    for (int i = 0; i < N; i++) {
        if (bestSol[i] == 1)
            n1++;
    }

    int n2 = N - n1;

    *V1p = malloc(n1*sizeof(int));
    *V2p = malloc(n2*sizeof(int));

    int i1 = 0;
    int i2 = 0;

    for (int i = 0; i < N; i++) {
        if (bestSol[i] == 1) {
            (*V1p)[i1] = V[i];
            i1++;
        }
        else {
            (*V2p)[i2] = V[i];
            i2++;
        }
    }

    return n1;
}

void bestSolR(int *val, int *sol, int *bestSol, int sum, int *bestSumP,int goal, int n, int start) {
    int i;
    if (checkTerminal(n,start,sum,goal)) {
        checkBestSol(n,sol,bestSol,sum,bestSumP,goal);
        return;
    }
    for (i = start; i < n; i++) {
        sol[i] = 1;
        bestSolR(val,sol,bestSol,sum+val[i],bestSumP,goal,n,i+1);
        sol[i] = 0;
    }
}

int bestSplit(int *V, int N, int **V1p, int **V2p) {
    int *sol = calloc(N,sizeof(int));
    int *bestSol = calloc(N,sizeof(int));
    int bestSum=0;
    int goal = 0;
    int n1;
    for (int i=0; i<N; i++) goal += V[i];

    goal /= 2;
    // la funzione ricorsiva trova i dati per
    // uno dei due vettori; i dati non selezionati
    // andranno nel secondo vettore.
    bestSolR(V, sol, bestSol, 0,&bestSum, goal, N, 0);
    n1 = buildSol(V,N,bestSol,V1p,V2p);
    free(sol);
    free(bestSol);
    return n1;
}

static int somma(int *V, int N) {
    int s = 0;

    for (int i = 0; i < N; i++) {
        s += V[i];
    }

    return s;
}

static void stampaVettore(const char *nome, int *V, int N) {
    printf("%s = { ", nome);

    for (int i = 0; i < N; i++) {
        printf("%d", V[i]);

        if (i < N - 1) {
            printf(", ");
        }
    }

    printf(" }");
}

static void test(const char *nomeTest, int *V, int N) {
    int *V1 = NULL;
    int *V2 = NULL;

    printf("\n==============================\n");
    printf("%s\n", nomeTest);
    printf("==============================\n");

    stampaVettore("V", V, N);
    printf("\n");

    int n1 = bestSplit(V, N, &V1, &V2);
    int n2 = N - n1;

    int s1 = somma(V1, n1);
    int s2 = somma(V2, n2);

    stampaVettore("V1", V1, n1);
    printf("   somma = %d\n", s1);

    stampaVettore("V2", V2, n2);
    printf("   somma = %d\n", s2);

    printf("Differenza |S1 - S2| = %d\n", abs(s1 - s2));

    free(V1);
    free(V2);
}

int main(void) {
    int V1[] = {10, 1, 1};
    test("Caso critico: {10, 1, 1}", V1, 3);

    int V2[] = {3, 1, 4, 2, 2};
    test("Caso bilanciabile perfettamente", V2, 5);

    int V3[] = {8, 6, 5};
    test("Caso semplice dispari", V3, 3);

    int V4[] = {1, 2, 3, 4, 5};
    test("Sequenza 1..5", V4, 5);

    int V5[] = {7};
    test("Un solo elemento", V5, 1);

    int V6[] = {5, 5, 5, 5};
    test("Tutti uguali", V6, 4);

    int V7[] = {20, 10, 5, 5};
    test("Con elemento grande", V7, 4);

    int V8[] = {1, 1, 1, 1, 1};
    test("Cinque uni", V8, 5);

    return 0;
}