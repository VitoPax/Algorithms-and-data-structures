/*
    Date due stringhe s1 e s2, di lunghezza l1 e l2 (si supponga l1 > l2), verificare se rimuovendo l1-l2 caratteri da s1 si
    può ottenere una stringa uguale a s2. I caratteri possono essere rimossi in qualunque posizione delle stringa, non
    necessariamente contigui tra loro.
    La funzione di verifica ritorni 0 per indicare falso e un numero !=0 per vero. Il prototipo è

    int strContains(char *s1, char *s2);
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strContains(char *s1, char *s2);
int comb(int level, char *s1, char *s2, int n, int k, int start);

void test(char *s1, char *s2, int atteso) {
    int res = strContains(s1, s2);
    printf("s1 = \"%s\", s2 = \"%s\" -> %d (%s) [atteso: %d]\n",
           s1, s2, res, (res ? "vero" : "falso"), atteso);
}

int main(void) {
    test("abcdef", "ace", 1);        // tolgo b,d,f
    test("abcdef", "acf", 1);        // tolgo b,d,e
    test("abcdef", "abcdef", 1);     // uguali
    test("abcdef", "abd", 1);        // tolgo c,e,f
    test("abcdef", "af", 1);         // tolgo b,c,d,e

    test("abcdef", "aec", 0);        // ordine non rispettato
    test("abcdef", "gha", 0);        // caratteri assenti
    test("abcdef", "acg", 0);        // g assente
    test("abc", "abcd", 0);          // s2 più lunga
    test("abc", "", 1);              // stringa vuota contenuta
    test("", "", 1);                 // entrambe vuote
    test("", "a", 0);                // impossibile

    test("aabcc", "abc", 1);         // posso scegliere a,b,c
    test("aabcc", "acc", 1);         // posso scegliere a,c,c
    test("aabcc", "cac", 0);         // ordine non rispettato

    return 0;
}

int comb(int level, char *s1, char *s2, int n, int k, int start) {
    int i;
    if (level >= k) {
        return 1;
    }

    for (i = start; i + (k - level - 1) < n; i++) {
        if (s2[level] == s1[i])
            if (comb(level + 1, s1, s2, n, k, i + 1))
                return 1;
    }
    return 0;
}

int strContains(char *s1, char *s2) {
    int l1 = strlen(s1), l2 = strlen(s2);
    if (l2 > l1)
        return 0;
    return comb(0, s1, s2, l1, l2, 0);
}