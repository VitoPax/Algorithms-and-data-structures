/*

Una mappa rettangolare NxM è rappresentata da una matrice di interi:
il valore 0 indica una casella invalicabile (roccia), un valore
positivo indica l'altitudine della casella.

Un escursionista parte da una casella (r0,c0) e deve raggiungere
(r1,c1), muovendosi solo in orizzontale o verticale fra caselle
valicabili e senza mai passare due volte sulla stessa casella.

La fatica di un percorso è la somma delle altitudini di tutte le
caselle che lo compongono, inclusa quella di partenza e di arrivo.

Si scriva una funzione che determini la fatica minima di un percorso
da (r0,c0) a (r1,c1). Se le due caselle non sono connesse la funzione
ritorna -1.

La funzione abbia prototipo:

int minFatica(int **mappa, int N, int M, int r0, int c0, int r1, int c1);


Esempio: mappa 3x4

   1  9  9  1
   1  0  2  1
   1  1  2  9

Da (0,0) a (0,3) la fatica minima è 11:
scendendo lungo la prima colonna, attraversando l'ultima riga e
risalendo per la colonna 3 → 1+1+1+1+2+1+... (verificalo tu)

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


int percorribile(int **mappa, int **mark, int N, int M, int r, int c){

   if (r < 0 || r >= N || c < 0 || c >= M)     /* fuori dalla matrice */
      return 0;
   if (mappa[r][c] == 0)
      return 0;
   if (mark[r][c] != 0)
      return 0;

   return 1;
}

void minFaticaR(int fatica, int **mappa, int **mark, int N, int M, int r0, int c0, int r1, int c1, int *min) {
    int faticaTot =0;

   mark[r0][c0] = 1;

   if (r0 == r1 && c0 == c1) {
      if (fatica < *min) {
         *min = fatica;
      }
      mark[r0][c0] = 0;
      return;
   }

   // Verifico su
   if (percorribile(mappa,mark,N,M,r0-1,c0)) {
      faticaTot = mappa[r0-1][c0];
      minFaticaR(faticaTot+fatica, mappa,mark,N,M,r0-1,c0,r1,c1,min);
   }

   if (percorribile(mappa,mark,N,M,r0+1,c0)) {
      faticaTot = mappa[r0+1][c0];
      minFaticaR(fatica+faticaTot,mappa,mark,N,M,r0+1,c0,r1,c1,min);
   }

   if (percorribile(mappa,mark,N,M,r0,c0-1)) {
      faticaTot = mappa[r0][c0-1];
      minFaticaR(fatica+faticaTot, mappa,mark,N,M,r0,c0-1,r1,c1,min);
   }

   if (percorribile(mappa,mark,N,M,r0,c0+1)) {
      faticaTot = mappa[r0][c0+1];
      minFaticaR(fatica+faticaTot, mappa, mark,N,M,r0,c0+1,r1,c1,min);
   }

   mark[r0][c0] = 0;
}


int minFatica(int **mappa, int N, int M, int r0, int c0, int r1, int c1) {
   int min = INT_MAX;
   int **mark;
   int i;

   mark = malloc(N * sizeof(int *));
   for (i = 0; i < N; i++)
      mark[i] = calloc(M, sizeof(int));

   minFaticaR(mappa[r0][c0], mappa, mark, N, M, r0, c0, r1, c1, &min);

   for (i = 0; i < N; i++)
      free(mark[i]);
   free(mark);

   return min == INT_MAX ? -1 : min;
}

/* ---------------------------- TEST -------------------------------- */

/* costruisce una matrice int** da un array statico */
int **toMatrix(int *dati, int N, int M) {
   int **m = malloc(N * sizeof(int *));
   int i, j;
   for (i = 0; i < N; i++) {
      m[i] = malloc(M * sizeof(int));
      for (j = 0; j < M; j++)
         m[i][j] = dati[i * M + j];
   }
   return m;
}

void liberaMatrix(int **m, int N) {
   int i;
   for (i = 0; i < N; i++)
      free(m[i]);
   free(m);
}

void prova(int *dati, int N, int M, int r0, int c0, int r1, int c1,
           int atteso) {
   int **m = toMatrix(dati, N, M);
   int r = minFatica(m, N, M, r0, c0, r1, c1);
   printf("  (%d,%d) -> (%d,%d) : %3d   (atteso %3d) %s\n",
          r0, c0, r1, c1, r, atteso, r == atteso ? "" : "<-- ERRORE");
   liberaMatrix(m, N);
}

void stampa(int *dati, int N, int M) {
   int i, j;
   for (i = 0; i < N; i++) {
      printf("    ");
      for (j = 0; j < M; j++)
         printf("%2d ", dati[i * M + j]);
      printf("\n");
   }
}

int main(void) {
   /* mappa dell'esempio */
   int A[] = { 1, 9, 9, 1,
               1, 0, 2, 1,
               1, 1, 2, 9 };

   /* muro di roccia che separa in due */
   int B[] = { 1, 0, 1,
               1, 0, 1,
               1, 0, 1 };

   /* due strade alternative: quella lunga costa meno */
   int C[] = { 1, 50, 1,
               1,  1, 1 };

   printf("Mappa A:\n");
   stampa(A, 3, 4);
   prova(A, 3, 4, 0, 0, 0, 3, 10);    /* giu, destra, su */
   prova(A, 3, 4, 0, 0, 0, 0,  1);    /* stessa casella */
   prova(A, 3, 4, 0, 0, 2, 3, 15);

   printf("\nMappa B (muro di roccia):\n");
   stampa(B, 3, 3);
   prova(B, 3, 3, 0, 0, 0, 2, -1);    /* non connesse */

   printf("\nMappa C (la strada lunga costa meno):\n");
   stampa(C, 2, 3);
   prova(C, 2, 3, 0, 0, 0, 2, 5);     /* 1+1+1+1+1 anziche' 1+50+1 */

   return 0;
}