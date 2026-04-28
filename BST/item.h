#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>

#define MAXC 11

/*
 * In questo esempio:
 * - la chiave è una stringa
 * - l'Item contiene solo un campo name
 *
 * typedef const char *Key;
 * significa che Key è un puntatore a carattere costante.
 * In pratica useremo Key per confrontare le stringhe.
 */
typedef const char *Key;

typedef struct {
    char name[MAXC];
} Item;

/*
 * Legge un Item da tastiera.
 */
Item ITEMscan(void);

/*
 * Restituisce un Item "nullo".
 * Lo usiamo quando una ricerca fallisce.
 */
Item ITEMsetNull(void);

/*
 * Controlla se un Item è nullo.
 */
int ITEMcheckNull(Item val);

/*
 * Stampa un Item.
 */
void ITEMstore(Item val);

/*
 * Restituisce la chiave di un Item.
 *
 * Uso il puntatore Item *pval perché così evitiamo copie inutili
 * e restiamo vicini allo stile ADT.
 */
Key KEYget(Item *pval);

/*
 * Confronta due chiavi.
 *
 * Ritorna:
 * -1 se k1 < k2
 *  0 se k1 == k2
 *  1 se k1 > k2
 */
int KEYcmp(Key k1, Key k2);

/*
 * Legge una chiave da tastiera.
 */
void KEYscan(char *k);

#endif