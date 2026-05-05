#ifndef FEBBRAIO25_BST_H
#define FEBBRAIO25_BST_H


typedef struct bst *BST;

BST BSTnew(void);
void BSTfree(BST b);

void BSTsetRoot(BST b, int val);
void BSTinsertLeft(BST b, int parent_val, int val);
void BSTinsertRight(BST b, int parent_val, int val);

int BSTisBalanced(BST b);


#endif //FEBBRAIO25_BST_H
