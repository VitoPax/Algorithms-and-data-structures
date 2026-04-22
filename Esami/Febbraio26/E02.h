#ifndef FEBBRAIO26_E02_H
#define FEBBRAIO26_E02_H

#define MAXC 40

typedef struct {
    char name[MAXC];
} Item;

typedef struct binarysearchtree *BST;

/* operazioni pubbliche */
BST BSTdup(BST b);
BST BSTinit(void);
void BSTfree(BST b);

/* funzioni utili per il test */
void BSTinsertLeaf(BST b, Item item);
void BSTshow(BST b);

#endif //FEBBRAIO26_E02_H