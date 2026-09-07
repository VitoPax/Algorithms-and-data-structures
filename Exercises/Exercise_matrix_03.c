/*
È data una matrice di caratteri m di dimensioni r × c (allocata come vettore di puntatori a riga) e una parola w.
Si scriva una funzione che trovi tutte le occorrenze di w nella matrice, lette orizzontalmente da sinistra a destra oppure verticalmente dall'alto in basso.
La funzione restituisce by pointer un vettore di strutture Pos con le coordinate di inizio di ogni occorrenza e la direzione. Ritorna il numero di occorrenze.

typedef struct { int i, j; char dir; } Pos;   /* dir = 'O' oppure 'V'

int trovaParola(char **m, int r, int c, char *w, Pos **outP);

Esempio, con w = "CASA":

C A S A X
A X X X X
S Y C A S
A Z X X A

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int i, j;
    char dir;        /* 'O' = orizzontale, 'V' = verticale */
} Pos;

/* ---------------------------------------------------------------
   Verifica se la parola w compare a partire da (i,j) andando
   verso DESTRA. Pattern del quantificatore universale:
   cerco un controesempio, appena lo trovo esco.
   --------------------------------------------------------------- */
int checkPosOrizz(char **m, int c, int i, int j, char *w) {
    int k, len = strlen(w);

    if (j + len > c) return 0;          /* la parola non ci sta */

    for (k = 0; k < len; k++)
        if (m[i][j + k] != w[k])        /* i fisso, j+k avanza */
            return 0;

    return 1;                           // PIENA CORRISPONDNZA, ALTRIMENTI SAREI USCITO ALLA PRIMA NON CORRISPONDENZA
}

/* ---------------------------------------------------------------
   Come sopra, ma andando verso il BASSO.
   Ruoli scambiati: j fisso, i+k avanza. Il bordo da controllare
   e' r, non c.
   --------------------------------------------------------------- */
int checkPosVert(char **m, int r, int i, int j, char *w) {
    int k, len = strlen(w);

    if (i + len > r) return 0;

    for (k = 0; k < len; k++)
        if (m[i + k][j] != w[k])
            return 0;

    return 1;
}

/* ---------------------------------------------------------------
   Trova tutte le occorrenze di w, orizzontali e verticali.
   Vettore restituito by pointer, dimensione esatta.
   Ritorna il numero di occorrenze, -1 se errore di allocazione.

   INDICI:
     i, j = scorrono la MATRICE (tutte le r*c posizioni)
     t    = scorre il VETTORE risultato (avanza solo se trovo)
   --------------------------------------------------------------- */
int trovaParola(char **m, int r, int c, char *w, Pos **outP) {
    int i, j, t = 0, occorrenze = 0;
    Pos *out;

    /* PASSATA 1: conto. Due if separati, non if/else:
       la stessa posizione puo' valere in entrambe le direzioni. */
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (checkPosOrizz(m, c, i, j, w)) occorrenze++;
            if (checkPosVert(m, r, i, j, w))  occorrenze++;
        }
    }

    /* ALLOCO della dimensione esatta */
    out = malloc(occorrenze * sizeof(Pos));
    if (out == NULL) return -1;

    /* PASSATA 2: riempio, con indice t separato */
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (checkPosOrizz(m, c, i, j, w)) {
                out[t].i = i;
                out[t].j = j;
                out[t].dir = 'O';      /* apici singoli: e' un char */
                t++;
            }
            if (checkPosVert(m, r, i, j, w)) {
                out[t].i = i;
                out[t].j = j;
                out[t].dir = 'V';
                t++;
            }
        }
    }

    *outP = out;
    return occorrenze;
}

/* =============================================================
   Codice di prova
   ============================================================= */

char **creaMatrice(int r, int c, char *righe[]) {
    int i, j;
    char **m = malloc(r * sizeof(char *));
    for (i = 0; i < r; i++) {
        m[i] = malloc(c * sizeof(char));
        for (j = 0; j < c; j++)
            m[i][j] = righe[i][j];
    }
    return m;
}

void freeMatrice(char **m, int r) {
    int i;
    for (i = 0; i < r; i++)
        free(m[i]);
    free(m);
}

void stampaMatrice(char **m, int r, int c) {
    int i, j;
    for (i = 0; i < r; i++) {
        printf("    ");
        for (j = 0; j < c; j++)
            printf("%c ", m[i][j]);
        printf("\n");
    }
}

void prova(char *nome, int r, int c, char *righe[], char *w) {
    char **m = creaMatrice(r, c, righe);
    Pos *out;
    int n, k;

    printf("--- %s   parola = \"%s\" ---\n", nome, w);
    stampaMatrice(m, r, c);

    n = trovaParola(m, r, c, w, &out);

    if (n < 0) {
        printf("    ERRORE di allocazione\n\n");
        freeMatrice(m, r);
        return;
    }

    printf("    occorrenze: %d\n", n);
    for (k = 0; k < n; k++)
        printf("      (%d,%d) %s\n", out[k].i, out[k].j,
               out[k].dir == 'O' ? "orizzontale" : "verticale");
    printf("\n");

    free(out);
    freeMatrice(m, r);
}

int main(void) {
    char *m1[] = {"CASAX",
                  "AXXXX",
                  "SYCAS",
                  "AZXXA"};

    char *m2[] = {"CASA",
                  "AXXX",
                  "SXCASA",   /* riga piu' lunga: uso solo i primi c */
                  "AXXX"};

    char *m3[] = {"ABC",
                  "DEF",
                  "GHI"};

    char *m4[] = {"CCCC",
                  "AAAA",
                  "SSSS",
                  "AAAA"};

    prova("esempio della traccia", 4, 5, m1, "CASA");
    prova("occorrenze multiple",   4, 4, m2, "CASA");
    prova("nessuna occorrenza",    3, 3, m3, "CASA");
    prova("quattro verticali",     4, 4, m4, "CASA");

    return 0;
}