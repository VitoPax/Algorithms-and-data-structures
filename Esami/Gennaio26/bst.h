#ifndef GENNAIO26_BST_H
#define GENNAIO26_BST_H

#include "item.h"

#define PREORDER  -1
#define INORDER    0
#define POSTORDER  1

typedef struct  bst *BST;

BST BSTinit(void);
void BSTinsert_leafR(BST b, Item val);
int BSTcountBetween(BST b, Key k1, Key k2);
void BSTshow(BST b);


#endif //GENNAIO26_BST_H