#include <stdio.h>
#include <stdlib.h>

/* ===============================================================
   TRACCIA
   Matrice dinamica NxN di 0/1: m[i][j]==1 se le persone i e j
   sono amiche. Dato un elenco P di NP persone, individuare e
   stampare tutte le persone NON appartenenti all'elenco che sono
   amiche di almeno due persone dell'elenco.

   void f(int **m, int N, int *P, int NP);

   NOTA: la traccia riporta "int P" nel prototipo, ma il testo
   descrive P come un vettore di NP interi. Si assume quindi
   "int *P", correggendo quello che sembra un refuso.
   =============================================================== */

/* ---------------------------------------------------------------
   Restituisce 1 se la persona k compare nell'elenco P, 0 altrimenti.
   Quantificatore esistenziale: appena trovo, esco.
   --------------------------------------------------------------- */
int isInElenco(int k, int *P, int NP) {
    int t;

    for (t = 0; t < NP; t++)
        if (k == P[t])
            return 1;       /* trovata */

    return 0;               /* scorso tutto l'elenco senza trovarla */
}

/* ---------------------------------------------------------------
   INDICI:
     k     = scorre le N persone candidate
     t     = scorre le NP persone dell'elenco
     count = amicizie di k dentro l'elenco, AZZERATO A OGNI k
   --------------------------------------------------------------- */
void f(int **m, int N, int *P, int NP) {
    int k, t, count;

    for (k = 0; k < N; k++) {

        if (isInElenco(k, P, NP))       // SE TROVATA SALTO ALLA PROSSIMA ITERAZIONE SENZA ESEGUIRE IL CODICE DI SOTTO
            continue;                   /* scarto chi e' in elenco */

        count = 0;                      /* azzerato PER OGNI k */
        for (t = 0; t < NP; t++)
            if (m[k][P[t]] == 1)        /* k amico della t-esima in elenco? */
                count++;

        if (count >= 2)                 /* test DENTRO il ciclo su k */
            printf("%d\n", k);          /* stampo la PERSONA, non la matrice */
    }
}

/* ===============================================================
   Codice di prova
   =============================================================== */

int **creaMatrice(int N, int *dati) {
    int i, j;
    int **m = malloc(N * sizeof(int *));

    for (i = 0; i < N; i++) {
        m[i] = malloc(N * sizeof(int));
        for (j = 0; j < N; j++)
            m[i][j] = dati[i * N + j];
    }
    return m;
}

void freeMatrice(int **m, int N) {
    int i;
    for (i = 0; i < N; i++)
        free(m[i]);
    free(m);
}

void stampaSituazione(int **m, int N, int *P, int NP) {
    int i, j;

    printf("  matrice amicizie:\n");
    printf("      ");
    for (j = 0; j < N; j++) printf("%d ", j);
    printf("\n");
    for (i = 0; i < N; i++) {
        printf("    %d | ", i);
        for (j = 0; j < N; j++) printf("%d ", m[i][j]);
        printf("\n");
    }
    printf("  elenco P = {");
    for (i = 0; i < NP; i++) printf("%s%d", i ? ", " : "", P[i]);
    printf("}\n");
}

void prova(char *nome, int N, int *dati, int *P, int NP) {
    int **m = creaMatrice(N, dati);

    printf("--- %s ---\n", nome);
    stampaSituazione(m, N, P, NP);
    printf("  risultato:\n");
    f(m, N, P, NP);
    printf("\n");

    freeMatrice(m, N);
}

int main(void) {
    /* 5 persone, amicizie simmetriche:
       0-1, 0-2, 0-4, 1-3, 2-3, 3-4                              */
    int d1[] = {
    /*        0  1  2  3  4  */
    /* 0 */   0, 1, 1, 0, 1,
    /* 1 */   1, 0, 0, 1, 0,
    /* 2 */   1, 0, 0, 1, 0,
    /* 3 */   0, 1, 1, 0, 1,
    /* 4 */   1, 0, 0, 1, 0
    };

    int P1[] = {1, 2};            /* atteso: 0 e 3 */
    int P2[] = {0, 3};            /* atteso: 1, 2, 4 */
    int P3[] = {0, 1, 2, 3, 4};   /* atteso: nessuno (tutti in elenco) */
    int P4[] = {1};               /* atteso: nessuno (>=2 impossibile) */

    prova("elenco {1,2}",      5, d1, P1, 2);
    prova("elenco {0,3}",      5, d1, P2, 2);
    prova("elenco = tutti",    5, d1, P3, 5);
    prova("elenco con 1 solo", 5, d1, P4, 1);

    return 0;
}