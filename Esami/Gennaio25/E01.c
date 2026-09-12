/*
 * Esercizio: sotto-sequenza
 *
 * Sono dati due vettori di interi a, b (non ordinati e contenenti
 * eventualmente dati ripetuti), di dimensione rispettivamente na e nb.
 * Si scriva una funzione che verifichi se il primo vettore sia una
 * sotto-sequenza del secondo.
 *
 *     ris = subSeq(a, na, b, nb);
 *
 * Nel file ci sono piu' versioni con nomi diversi, cosi' compilano
 * tutte insieme. All'esame la funzione va chiamata subSeq.
 *
 * Compilazione:  gcc -Wall -o subseq subseq.c
 */

#include <stdio.h>

/* ------------------------------------------------------------------
 * 1. Iterativa con for (versione di riferimento)
 *
 * Una sola passata su b: j avanza sempre, i avanza solo quando
 * a[i] == b[j]. Nessuno dei due indici torna mai indietro, quindi
 * l'ordine e' rispettato. La condizione i < na evita di leggere a[na].
 * Costo: O(nb)
 * ------------------------------------------------------------------ */
int subSeqFor(int *a, int na, int *b, int nb) {
    int i = 0, j;

    for (j = 0; j < nb && i < na; j++) {
        if (a[i] == b[j])
            i++;
    }

    if (i != na)
        return 0;

    return 1;
}

/* ------------------------------------------------------------------
 * 2. Iterativa con while e due indici
 *
 * Stessa logica della versione 1, scritta in modo simmetrico.
 * Costo: O(nb)
 * ------------------------------------------------------------------ */
int subSeqWhile(int *a, int na, int *b, int nb) {
    int i = 0, j = 0;

    while (i < na && j < nb) {
        if (a[i] == b[j])
            i++;
        j++;
    }
    return i == na;
}

/* ------------------------------------------------------------------
 * 3. Ricorsiva
 *
 * Si guarda solo il primo elemento di ciascun vettore:
 *  - a vuoto            -> 1 (il vettore vuoto e' sotto-sequenza di tutto)
 *  - a non vuoto, b vuoto -> 0
 *  - a[0] == b[0]       -> ricorro su entrambi i resti
 *  - altrimenti         -> scarto b[0] e ricorro sul resto di b
 *
 * ATTENZIONE: il controllo su na va PRIMA di quello su nb,
 * altrimenti con na == 0 e nb == 0 si restituirebbe 0.
 * a+1, na-1 indica "il resto del vettore" senza copiare nulla.
 * Costo: O(nb) tempo, O(nb) spazio sullo stack.
 * ------------------------------------------------------------------ */
int subSeqRic(int *a, int na, int *b, int nb) {
    if (na == 0) return 1;
    if (nb == 0) return 0;

    if (a[0] == b[0])
        return subSeqRic(a+1, na-1, b+1, nb-1);

    return subSeqRic(a, na, b+1, nb-1);
}

/* ------------------------------------------------------------------
 * 4. Variante: sotto-sequenza CONTIGUA (sottovettore)
 *
 * Solo se il testo intende che gli elementi di a compaiono in b
 * uno dopo l'altro, senza buchi. Si prova ogni posizione di partenza
 * s in b; s + na <= nb evita di uscire da b.
 * Costo: O(na * nb) nel caso peggiore.
 * ------------------------------------------------------------------ */
int subSeqContigua(int *a, int na, int *b, int nb) {
    int s, k;

    for (s = 0; s + na <= nb; s++) {
        for (k = 0; k < na && a[k] == b[s+k]; k++)
            ;
        if (k == na)
            return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------
 * main di test
 * ------------------------------------------------------------------ */
typedef struct {
    int *a; int na;
    int *b; int nb;
    int attesoSubSeq;     /* risultato atteso per le versioni 1-3 */
    int attesoContigua;   /* risultato atteso per la versione 4   */
    char *descr;
} Test;

int main(void) {
    int a1[] = {1, 3},    b1[] = {1, 2, 3};
    int a2[] = {3, 1},    b2[] = {1, 3};
    int a3[] = {5},       b3[] = {1, 2};
    int a4[] = {2, 3},    b4[] = {1, 2, 3, 4};
    int a5[] = {1, 1},    b5[] = {1, 2, 1};
    int a6[] = {1, 2, 3}, b6[] = {1, 2};
    int b7[] = {1, 2};

    Test t[] = {
        { a1, 2, b1, 3, 1, 0, "{1,3} in {1,2,3}      (non contigua)" },
        { a2, 2, b2, 2, 0, 0, "{3,1} in {1,3}        (ordine invertito)" },
        { a3, 1, b3, 2, 0, 0, "{5} in {1,2}          (elemento assente)" },
        { a4, 2, b4, 4, 1, 1, "{2,3} in {1,2,3,4}    (contigua)" },
        { a5, 2, b5, 3, 1, 0, "{1,1} in {1,2,1}      (ripetuti)" },
        { a6, 3, b6, 2, 0, 0, "{1,2,3} in {1,2}      (a piu' lungo di b)" },
        { NULL, 0, b7, 2, 1, 1, "{} in {1,2}           (a vuoto)" },
        { NULL, 0, NULL, 0, 1, 1, "{} in {}              (entrambi vuoti)" },
    };
    int nt = sizeof(t) / sizeof(t[0]);
    int i, r1, r2, r3, r4, errori = 0;

    printf("%-42s  for while ric cont\n", "caso");
    for (i = 0; i < nt; i++) {
        r1 = subSeqFor(t[i].a, t[i].na, t[i].b, t[i].nb);
        r2 = subSeqWhile(t[i].a, t[i].na, t[i].b, t[i].nb);
        r3 = subSeqRic(t[i].a, t[i].na, t[i].b, t[i].nb);
        r4 = subSeqContigua(t[i].a, t[i].na, t[i].b, t[i].nb);

        printf("%-42s   %d    %d    %d    %d", t[i].descr, r1, r2, r3, r4);

        if (r1 != t[i].attesoSubSeq || r2 != t[i].attesoSubSeq ||
            r3 != t[i].attesoSubSeq || r4 != t[i].attesoContigua) {
            printf("   <-- ERRORE");
            errori++;
        }
        printf("\n");
    }

    printf("\n%s (%d errori)\n", errori == 0 ? "Tutti i test OK" : "Ci sono errori", errori);
    return 0;
}