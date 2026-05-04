#ifndef GIUGNO25_BST_H
#define GIUGNO25_BST_H

#include "item.h"

#include "item.h"

typedef struct BSTnode *link;

struct BSTnode {
    Item item;
    link left;
    link right;
};

typedef struct bst *BST;

struct bst {
    link root;
};

BST BSTinit(void);
void BSTinsert(BST b, Item item);
void BSTprintPreorder(BST b);
void BSTfree(BST b);

#endif //GIUGNO25_BST_H
