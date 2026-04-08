/*
 * Esercizio n.1: Valutazione di espressioni regolari
 *
 * I problemi di ricerca di stringhe all'interno di testi e/o collezioni di
 * stringhe (solitamente di dimensione maggiore rispetto alla stringa cercata)
 * si basano raramente su un confronto esatto, ma molto spesso necessitano di
 * rappresentare in modo compatto non una, ma un insieme di stringhe cercate,
 * evitandone per quanto possibile l'enumerazione esplicita.
 *
 * Le espressioni regolari sono una notazione molto utilizzata per rappresentare
 * in modo compatto insiemi di stringhe correlate tra loro (ad esempio aventi
 * una parte comune).
 *
 * Si scriva una funzione in C in grado di individuare (cercare) eventuali
 * occorrenze di una data regexp all'interno di una stringa di input.
 *
 * La funzione sia caratterizzata dal seguente prototipo:
 *
 *      char *cercaRegexp(char *src, char *regexp);
 *
 * dove:
 * - il parametro src rappresenta la stringa sorgente in cui cercare;
 * - il parametro regexp rappresenta l'espressione regolare da cercare;
 * - il valore di ritorno della funzione è un puntatore alla prima occorrenza
 *   di regexp in src (NULL se non trovata).
 *
 * Ai fini dell'esercizio si consideri di valutare solamente stringhe composte
 * da caratteri alfabetici.
 *
 * Si considerino inoltre solamente espressioni regolari composte da caratteri
 * alfabetici e dai seguenti metacaratteri:
 *
 * - .      trova un singolo carattere
 *          (cioè qualunque carattere può corrispondere a un punto)
 *
 * - []     trova un singolo carattere contenuto nelle parentesi
 *          (cioè uno qualsiasi dei caratteri tra parentesi va bene)
 *
 * - [^ ]   trova ogni singolo carattere non contenuto nelle parentesi
 *          (cioè tutti i caratteri tra parentesi non vanno bene)
 *
 * - \a     trova un carattere minuscolo
 *
 * - \A     trova un carattere maiuscolo
 *
 * Esempi di espressioni regolari:
 *
 * - .oto
 *   corrisponde a ogni stringa di quattro caratteri terminante con "oto",
 *   ad esempio: "voto", "noto", "foto", ...
 *
 * - [mn]oto
 *   rappresenta solamente "moto" e "noto"
 *
 * - [^f]oto
 *   rappresenta tutte le stringhe terminanti in "oto" ad eccezione di "foto"
 *
 * - \aoto
 *   rappresenta ogni stringa di quattro caratteri iniziante per lettera
 *   minuscola e terminante in "oto", ad esempio: "voto", "noto", "foto", ...
 *
 * - \Aoto
 *   rappresenta ogni stringa di quattro caratteri iniziante per lettera
 *   maiuscola e terminante in "oto", ad esempio: "Voto", "Noto", "Foto", ...
 *
 * NOTA:
 * I metacaratteri possono apparire in qualsiasi punto dell'espressione
 * regolare. I casi qui sopra sono solo una minima parte a titolo di esempio.
 *
 * Sono quindi espressioni regolari valide:
 * - A[^f]\anR.d
 * - \A[aeiou]5t[123]
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static int matchToken(const char *regexp, int *j, char c) {
    int i = *j;

    // In case src is empty
    if (regexp[i] == '\0') {
        return 0;
    }

    if (regexp[i] == '.') {
        (*j)++;
        return 1;
    }

    if (regexp[i] == '\\') {
        i++;
        if (regexp[i] == 'a') {
            *j = i + 1;
            return islower((unsigned char)c);
        } else if (regexp[i] == 'A') {
            *j = i + 1;
            return isupper((unsigned char)c);
        } else {
            return 0;
        }
    }

    if (regexp[i] == '[') {
        int negato = 0;
        int trovato = 0;

        i++;

        if (regexp[i] == '^') {
            negato = 1;
            i++;
        }

        while (regexp[i] != '\0' && regexp[i] != ']') {
            if (regexp[i] == c) {
                trovato = 1;
            }
            i++;
        }

        if (regexp[i] != ']') {
            return 0;
        }

        *j = i + 1;

        if (negato)
            return !trovato;
        else
            return trovato;
    }

    (*j)++;
    return regexp[i] == c;
}

static int matchHere(const char *src, const char *regexp, int pos) {
    int i = pos;
    int j = 0;

    while (regexp[j] != '\0') {
        if (src[i] == '\0') {
            return 0;
        }

        if (!matchToken(regexp, &j, src[i])) {
            return 0;
        }

        i++;
    }

    return 1;
}

char *cercaRegexp(char *src, char *regexp) {
    int i;

    if (src == NULL || regexp == NULL) {
        return NULL;
    }

    for (i = 0; src[i] != '\0'; i++) {
        if (matchHere(src, regexp, i)) {
            return &src[i];
        }
    }

    return NULL;
}

/* conta quanti caratteri di src consuma la regexp */
int lunghezzaMatch(const char *regexp) {
    int i = 0;
    int len = 0;

    while (regexp[i] != '\0') {
        if (regexp[i] == '.') {
            len++;
            i++;
        } else if (regexp[i] == '\\') {
            if (regexp[i + 1] == 'a' || regexp[i + 1] == 'A') {
                len++;
                i += 2;
            } else {
                return -1; /* regexp non valida */
            }
        } else if (regexp[i] == '[') {
            i++;
            if (regexp[i] == '^') {
                i++;
            }
            while (regexp[i] != '\0' && regexp[i] != ']') {
                i++;
            }
            if (regexp[i] != ']') {
                return -1; /* regexp non valida */
            }
            i++;   /* salto ']' */
            len++; /* tutta la classe matcha 1 solo carattere */
        } else {
            len++;
            i++;
        }
    }

    return len;
}


int main(void) {
    char *ris;

    printf("=== Test regexp .oto ===\n");
    ris = cercaRegexp("voto", ".oto");
    printf(".oto su voto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("moto", ".oto");
    printf(".oto su moto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("noto", ".oto");
    printf(".oto su noto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("foto", ".oto");
    printf(".oto su foto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("abc", ".oto");
    printf(".oto su abc -> %s\n\n", ris != NULL ? "MATCH" : "NO MATCH");

    printf("=== Test regexp [mn]oto ===\n");
    ris = cercaRegexp("voto", "[mn]oto");
    printf("[mn]oto su voto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("moto", "[mn]oto");
    printf("[mn]oto su moto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("noto", "[mn]oto");
    printf("[mn]oto su noto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("foto", "[mn]oto");
    printf("[mn]oto su foto -> %s\n\n", ris != NULL ? "MATCH" : "NO MATCH");


    printf("=== Test regexp [^f]oto ===\n");
    ris = cercaRegexp("voto", "[^f]oto");
    printf("[^f]oto su voto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("moto", "[^f]oto");
    printf("[^f]oto su moto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("noto", "[^f]oto");
    printf("[^f]oto su noto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("foto", "[^f]oto");
    printf("[^f]oto su foto -> %s\n\n", ris != NULL ? "MATCH" : "NO MATCH");


    printf("=== Test regexp \\\\aoto ===\n");
    ris = cercaRegexp("voto", "\\aoto");
    printf("\\aoto su voto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("moto", "\\aoto");
    printf("\\aoto su moto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("Noto", "\\aoto");
    printf("\\aoto su Noto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("Foto", "\\aoto");
    printf("\\aoto su Foto -> %s\n\n", ris != NULL ? "MATCH" : "NO MATCH");


    printf("=== Test regexp \\\\Aoto ===\n");
    ris = cercaRegexp("voto", "\\Aoto");
    printf("\\Aoto su voto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("moto", "\\Aoto");
    printf("\\Aoto su moto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("Noto", "\\Aoto");
    printf("\\Aoto su Noto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    ris = cercaRegexp("Foto", "\\Aoto");
    printf("\\Aoto su Foto -> %s\n", ris != NULL ? "MATCH" : "NO MATCH");

    return 0;
}