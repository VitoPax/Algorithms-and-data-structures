/*
Data una stringa s e un carattere separatore sep, si scriva una funzione che spezzi la stringa nei token separati da sep
e restituisca by pointer un vettore di stringhe allocate dinamicamente.
La funzione ritorna il numero di token.

int splitString(char *s, char sep, char ***tokensP);

Esempio: s = "ciao;come;stai", sep = ';' → {"ciao", "come", "stai"}, ritorna 3.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int splitString(char *s, char sep, char ***tokensP) {
    int i, j, k, t = 0, count = 0;
    int len = strlen(s);
    char **token;
    int lunghezzaToken;

    /* PASSATA 1: conto i separatori */
    for (i = 0; i < len; i++)
        if (s[i] == sep)
            count++;

    /* ALLOCO: count separatori -> count+1 token */
    token = malloc((count + 1) * sizeof(char *));
    if (token == NULL) return -1;

    /* PASSATA 2: estraggo i token */
    i = 0;
    while (i <= len) {
        j = i;
        while (s[j] != sep && s[j] != '\0')
            j++;

        lunghezzaToken = j - i;

        token[t] = malloc((lunghezzaToken + 1) * sizeof(char));
        if (token[t] == NULL) return -1;

        for (k = 0; k < lunghezzaToken; k++)
            token[t][k] = s[i + k];
        token[t][lunghezzaToken] = '\0';

        t++;
        i = j + 1;
    }

    *tokensP = token;
    return count + 1;
}

/* ---------------------------------------------------------------
   Funzione di servizio: libera il vettore di stringhe.
   PRIMA le singole stringhe, POI il vettore di puntatori.
   --------------------------------------------------------------- */
void freeTokens(char **token, int n) {
    int i;
    for (i = 0; i < n; i++)
        free(token[i]);
    free(token);
}

/* ---------------------------------------------------------------
   Esegue un caso di prova e stampa il risultato.
   --------------------------------------------------------------- */
void prova(char *s, char sep, int attesi) {
    char **token;
    int i, n;

    n = splitString(s, sep, &token);

    printf("input:  \"%s\"  sep='%c'\n", s, sep);

    if (n < 0) {
        printf("  ERRORE di allocazione\n\n");
        return;
    }

    printf("  n = %d", n);
    if (n == attesi)
        printf("  [OK]\n");
    else
        printf("  [ATTESI %d]\n", attesi);

    for (i = 0; i < n; i++)
        printf("  token[%d] = \"%s\"  (len %d)\n",
               i, token[i], (int)strlen(token[i]));
    printf("\n");

    freeTokens(token, n);
}

int main(void) {
    printf("=== casi normali ===\n\n");
    prova("ciao;come;stai", ';', 3);
    prova("uno,due,tre,quattro", ',', 4);

    printf("=== casi limite ===\n\n");
    prova("ciao", ';', 1);          /* nessun separatore */
    prova("a;b;", ';', 3);          /* separatore finale -> ultimo token vuoto */
    prova(";a;b", ';', 3);          /* separatore iniziale -> primo token vuoto */
    prova("a;;b", ';', 3);          /* separatori consecutivi -> token vuoto in mezzo */
    prova(";", ';', 2);             /* solo il separatore */
    prova("", ';', 1);              /* stringa vuota -> un token vuoto */

    return 0;
}