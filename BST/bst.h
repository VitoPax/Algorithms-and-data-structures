#ifndef BST_H
#define BST_H

#include "item.h"

/*
 * Costanti per scegliere il tipo di visita.
 */
#define PREORDER  0
#define INORDER   1
#define POSTORDER 2

/*
 * ADT di prima classe.
 *
 * Fuori dal modulo bst.c non si vede com'è fatta davvero struct bst.
 * L'utente usa solo il tipo BST.
 */
typedef struct bst *BST;

/*
 * Inizializzazione e deallocazione.
 */
BST  BSTinit(void);
void BSTfree(BST bst);

/*
 * Operazioni di base.
 */
int  BSTcount(BST bst);
int  BSTempty(BST bst);

Item BSTsearch(BST bst, Key k);

/*
 * Inserimenti.
 */
void BSTinsert_leafR(BST bst, Item x);
void BSTinsert_leafI(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);

/*
 * Minimo e massimo.
 */
Item BSTmin(BST bst);
Item BSTmax(BST bst);

/*
 * Visite.
 */
void BSTvisit(BST bst, int strategy);

#endif