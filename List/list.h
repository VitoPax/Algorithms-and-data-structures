#ifndef LIST_LIST_H
#define LIST_LIST_H

#ifndef LIST_H
#define LIST_H

typedef int Item;
typedef int Key;

/* Tipo opaco dell'ADT */
typedef struct list *LIST;

/* Operazioni su Item e Key */
Key KEYget(Item item);
int KEYeq(Key k1, Key k2);
Item ITEMsetvoid(void);

/* Creazione della lista */
LIST LISTinit(void);

/* Controllo lista vuota */
int LISTempty(LIST l);

/* Inserimenti */
void LISTinsHead(LIST l, Item item);
void LISTinsTail(LIST l, Item item);

Item LISTsearch(LIST l, Key k);

void LISTdelHead(LIST l);

Item LISTextractHead(LIST l);

void LISTdelKey(LIST l, Key k);

/* Visualizzazione */
void LISTdisplay(LIST l);

#endif


#endif //LIST_LIST_H
