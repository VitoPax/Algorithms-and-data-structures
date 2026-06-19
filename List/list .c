#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/* Tipo privato: puntatore a nodo */
typedef struct node *link;

/* Struttura privata del nodo */
struct node {
    Item item;
    link next;
};

/* Struttura privata dell'ADT */
struct list {
    link root;
};

/* Crea un nuovo nodo */
static link newNode(Item item, link next)
{
    link nuovo;

    nuovo = malloc(sizeof *nuovo);

    if (nuovo == NULL)
        return NULL;

    nuovo->item = item;
    nuovo->next = next;

    return nuovo;
}

/* Inserimento in testa sulla catena di nodi */
static link listInsHead(link h, Item item)
{
    link nuovo;

    nuovo = newNode(item, h);

    if (nuovo == NULL)
        return h;

    return nuovo;
}

/* Inserimento in coda sulla catena di nodi */
static link listInsTail(link h, Item item)
{
    link x;
    link nuovo;

    nuovo = newNode(item, NULL);

    if (nuovo == NULL)
        return h;

    /* Lista vuota: il nuovo nodo diventa la testa */
    if (h == NULL)
        return nuovo;

    /* Ricerca dell'ultimo nodo */
    for (x = h; x->next != NULL; x = x->next)
        ;

    /* Collegamento del nuovo nodo */
    x->next = nuovo;

    return h;
}

/* Crea una lista vuota */
LIST LISTinit(void)
{
    LIST l;

    l = malloc(sizeof *l);

    if (l == NULL)
        return NULL;

    l->root = NULL;

    return l;
}

/* Verifica se la lista è vuota */
int LISTempty(LIST l)
{
    if (l == NULL)
        return 1;

    return l->root == NULL;
}

/* Funzione pubblica di inserimento in testa */
void LISTinsHead(LIST l, Item item)
{
    if (l == NULL)
        return;

    l->root = listInsHead(l->root, item);
}

/* Funzione pubblica di inserimento in coda */
void LISTinsTail(LIST l, Item item)
{
    if (l == NULL)
        return;

    l->root = listInsTail(l->root, item);
}

/* Attraversamento e stampa */
void LISTdisplay(LIST l)
{
    link x;

    if (l == NULL)
        return;

    for (x = l->root; x != NULL; x = x->next)
        printf("%d -> ", x->item);

    printf("NULL\n");
}

Key KEYget(Item item){
    return item;
}

int KEYeq(Key k1, Key k2){
    return k1 == k2;
}

int KEYgreater(Key k1, Key k2)
{
    return k1 > k2;
}

int KEYgeq(Key k1, Key k2)
{
    return k1 >= k2;
}

Item ITEMsetvoid(void){
    return -1;
}

static Item listSearch(link h, Key k){
    link x;

    for (x = h; x != NULL; x = x->next) {
        if (KEYeq(KEYget(x->item), k))
            return x->item;
    }

    return ITEMsetvoid();
}

Item LISTsearch(LIST l, Key k){
    if (l == NULL)
        return ITEMsetvoid();

    return listSearch(l->root, k);
}

static link listDelHead(link h)
{
    link t;

    if (h == NULL)
        return NULL;

    t = h;
    h = h->next;
    free(t);

    return h;
}

void LISTdelHead(LIST l)
{
    if (l == NULL)
        return;

    l->root = listDelHead(l->root);
}

static Item listExtrHeadP(link *hp)
{
    link t;
    Item item;

    if (*hp == NULL)
        return ITEMsetvoid();

    t = *hp;
    item = t->item;

    *hp = t->next;

    free(t);

    return item;
}

Item LISTextractHead(LIST l)
{
    if (l == NULL)
        return ITEMsetvoid();

    return listExtrHeadP(&(l->root));
}

/* ALTERNATIVA SENZA WRAPPER
Item LISTextractHead(List l)
{
    link t;
    Item item;

    if (l == NULL || l->root == NULL)
        return ITEMsetvoid();

    t = l->root;
    item = t->item;

    l->root = t->next;

    free(t);

    return item;
}
*/

static link listDelKey(link h, Key k)
{
    link x;
    link p;

    if (h == NULL)
        return NULL;

    for (x = h, p = NULL;
         x != NULL;
         p = x, x = x->next) {

        if (KEYeq(KEYget(x->item), k)) {

            if (p == NULL)
                h = x->next;
            else
                p->next = x->next;

            free(x);
            break;
        }
         }

    return h;
}

void LISTdelKey(LIST l, Key k)
{
    if (l == NULL)
        return;

    l->root = listDelKey(l->root, k);
}

/* VERSIONE SENZA WRAPPER

void LISTdelKey(LIST l, Key k)
{
    link x;
    link p;

    if (l == NULL || l->root == NULL)
        return;

    for (x = l->root, p = NULL;
         x != NULL;
         p = x, x = x->next) {

        if (KEYeq(KEYget(x->item), k)) {

            if (p == NULL)
                l->root = x->next;
            else
                p->next = x->next;

            free(x);
            return;
        }
         }
}
*/


/* FINE FUNZIONI SU LISTE NON ORDINATE */

/* LISTE ORDINATE */

static link SortListIns(link h, Item item){
    link x;
    link p;
    link nuovo;
    Key k;

    k = KEYget(item);

    if (h == NULL || KEYgreater(KEYget(h->item), k)) {
        nuovo = newNode(item, h);

        if (nuovo == NULL)
            return h;

        return nuovo;
    }

    for (x = h->next, p = h;
         x != NULL && KEYgreater(k, KEYget(x->item));
         p = x, x = x->next)
        ;

    nuovo = newNode(item, x);

    if (nuovo == NULL)
        return h;

    p->next = nuovo;

    return h;
}


void LISTsortIns(LIST l, Item item){
    if (l == NULL)
        return;

    l->root = SortListIns(l->root, item);
}

static Item SortListSearch(link h, Key k){
    link x;

    x = h;

    while (x != NULL &&
           KEYgeq(k, KEYget(x->item))) {

        if (KEYeq(KEYget(x->item), k))
            return x->item;

        x = x->next;
           }

    return ITEMsetvoid();
}

Item LISTsortSearch(LIST l, Key k){
    if (l == NULL)
        return ITEMsetvoid();

    return SortListSearch(l->root, k);
}

static link SortListDel(link h, Key k){
    link x;
    link p;

    if (h == NULL)
        return NULL;

    for (x = h, p = NULL;
         x != NULL && KEYgeq(k, KEYget(x->item));
         p = x, x = x->next) {

        if (KEYeq(KEYget(x->item), k)) {

            if (p == NULL)
                h = x->next;
            else
                p->next = x->next;

            free(x);
            break;
        }
         }

    return h;
}

void LISTsortDel(LIST l, Key k){
    if (l == NULL)
        return;

    l->root = SortListDel(l->root, k);
}

/* Applicazioni */

// Inversione di lista prima versione: in questa versione usiamo le funzioni di estrazione ed inserimento

static link listReverseF(link h){
    link y;
    link r;
    Item item;

    y = h;
    r = NULL;

    while (y != NULL) {
        item = listExtrHeadP(&y);
        r = listInsHead(r, item);
    }

    return r;
}

void LISTreverse(LIST l){
    if (l == NULL)
        return;

    l->root = listReverseF(l->root);
}

// Seconda versione: giriamo i puntatori 

static link listReverse(link h){
    link y;
    link r;
    link t;

    y = h;
    r = NULL;

    while (y != NULL) {
        t = y->next;
        y->next = r;
        r = y;
        y = t;
    }

    return r;
}