#ifndef FEBBRAIO26_E02_H
#define FEBBRAIO26_E02_H

#define MAXC 40

typedef struct {
    char name[MAXC];
} Item;

typedef struct binarysearchtree *BST;

BST BSTinit(void);
void BSTfree(BST b);
BST BSTdup(BST b);

void BSTshow(BST b);

#endif //FEBBRAIO26_E02_H