#ifndef BST_BST_H
#define BST_BST_H

#include "item.h"

typedef struct bst *BST;

BST BSTinit(void);
void BSTfree(BST bst);

Item BSTsearch(BST bst, Key k);

void BSTinsert_leafR(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);


#endif //BST_BST_H