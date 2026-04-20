/*
    Si vogliono contare i numeri in una data base (base, compresa tra 2 e 10), aventi un dato numero di cifre
    (nDigits) tali da rispettare i seguenti vincoli:
    A. ogni cifra può comparire al più maxRip volte nel numero
    B. la differenza (in valore assoluto) tra due cifre consecutive può essere al massimo 2
    C. il numero di cifre distinte (senza tener conto delle ripetizioni) deve essere almeno pari a nDigits/2
    (divisione tra interi)
    Ad esempio, con base 8, 7 cifre, massimo numero di ripetizioni 3, il numero 5356533 rispetta i vincoli,
    3232224 non rispetta il primo vincolo, 5376551 non rispetta il secondo, 3223322 non rispetta il primo e il
    terzo.
    La funzione da realizzare ritorna come risultato il conteggio dei numeri che rispettano i vincoli. Il prototipo è
    int cntNum(int base, int nDigits, int maxRip);
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int cntNum(int base, int nDigits, int maxRip);
int cntNumR(int level, int *sol, int *occ, int base, int nDigits, int maxRip, int lastDigit, int nDistinte);

int main(void) {
    int base = 10;
    int maxRip = 3;
    int nDigits = 9;

    int res = cntNum(base, nDigits, maxRip);

    printf("counter of solutions: %d\n", res);
    return 0;
}

/*
   La soluzione e' una variante del modello delle disposizioni con ripetizioni,
   in cui il numero di ripetizioni e' limitato a maxRip.
   Il vettore occ tiene il conto delle occorrenze di ogni cifra.
   Si fa pruning sulla differenza tra cifre adiacenti.
   Il conteggio delle cifre distinte viene aggiornato ad ogni chiamata ricorsiva
   e verificato nel caso terminale.
*/
int cntNumR(int level, int *sol, int *occ, int base, int nDigits, int maxRip, int lastDigit, int nDistinte) {
    int i, cnt = 0;
    int start;

    if (level == nDigits)
        return (nDistinte >= nDigits / 2) ? 1 : 0;

    start = (level == 0) ? 1 : 0;

    for (i = start; i < base; i++) {
        if (occ[i] >= maxRip)
            continue;

        if (level > 0 && abs(i - lastDigit) > 2)
            continue;

        if (occ[i]++ == 0)
            nDistinte++;

        sol[level] = i;
        cnt += cntNumR(level + 1, sol, occ, base, nDigits, maxRip, i, nDistinte);

        if (--occ[i] == 0)
            nDistinte--;
    }

    return cnt;
}

int cntNum(int base, int nDigits, int maxRip) {
    int *sol = malloc(nDigits * sizeof(int));
    int *occ = calloc(base, sizeof(int));
    int cntOK;

    if (sol == NULL || occ == NULL) {
        free(sol);
        free(occ);
        return 0;
    }

    cntOK = cntNumR(0, sol, occ, base, nDigits, maxRip, -1, 0);

    free(sol);
    free(occ);

    return cntOK;
}