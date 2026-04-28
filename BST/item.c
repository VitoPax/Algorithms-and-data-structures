#include <stdio.h>
#include <string.h>
#include "item.h"

/*
 * Legge una stringa da tastiera e la salva dentro val.name.
 *
 * %10s evita di leggere più di 10 caratteri,
 * perché MAXC vale 11 e ci serve spazio per '\0'.
 */
Item ITEMscan(void) {
    Item val;

    scanf("%10s", val.name);

    return val;
}

/*
 * Crea un Item nullo.
 *
 * Mettiamo la stringa vuota "" dentro name.
 * Quindi val.name[0] = '\0'.
 */
Item ITEMsetNull(void) {
    Item val;

    val.name[0] = '\0';

    return val;
}

/*
 * Un Item è nullo se la sua stringa è vuota.
 */
int ITEMcheckNull(Item val) {
    return val.name[0] == '\0';
}

/*
 * Stampa l'Item solo se non è nullo.
 */
void ITEMstore(Item val) {
    if (!ITEMcheckNull(val)) {
        printf("%s", val.name);
    }
}

/*
 * Restituisce la chiave dell'Item.
 *
 * Qui la chiave coincide con name.
 */
Key KEYget(Item *pval) {
    return pval->name;
}

/*
 * Confronto tra due chiavi stringa.
 *
 * strcmp ritorna:
 * - valore < 0 se k1 viene prima di k2
 * - valore > 0 se k1 viene dopo k2
 * - 0 se sono uguali
 *
 * Noi normalizziamo il risultato a -1, 0, 1.
 */
int KEYcmp(Key k1, Key k2) {
    int cmp;

    cmp = strcmp(k1, k2);

    if (cmp < 0) {
        return -1;
    }

    if (cmp > 0) {
        return 1;
    }

    return 0;
}

/*
 * Legge una chiave da tastiera.
 */
void KEYscan(char *k) {
    scanf("%10s", k);
}