/*
È dato un BST (tipo ADT BST). Si scriva una funzione che duplichi il BST, cioè generi un secondo BST con lo stesso contenuto del primo.
Si supponga di poter utilizzare una funzione

Item ItemDup(Item i);

per generare un duplicato (una copia) di un dato Item.
*/

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

static link newNodeDup(Item item, link left, link right);
static link BstDupR(link root);
BST BstDup(BST b);

static link newNodeDup(Item item, link left, link right) {
    link x;

    x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;

    x->item = ItemDup(item);
    x->left = left;
    x->right = right;

    return x;
}

static link BstDupR(link root) {
    link newRoot;

    if (root == NULL)
        return NULL;

    newRoot = newNodeDup(root->item, NULL, NULL);

    newRoot->left = BstDupR(root->left);
    newRoot->right = BstDupR(root->right);

    return newRoot;
}

BST BstDup(BST b) {
    BST new;

    if (b == NULL)
        return NULL;

    new = malloc(sizeof *new);
    if (new == NULL)
        return NULL;

    new->root = BstDupR(b->root);

    return new;
}

int main(void) {
    BST b;
    BST copia;

    b = BSTinit();

    BSTinsert(b, "D");
    BSTinsert(b, "A");
    BSTinsert(b, "J");
    BSTinsert(b, "E");

    printf("BST originale:\n");
    BSTprintPreorder(b);

    copia = BstDup(b);

    printf("BST duplicato:\n");
    BSTprintPreorder(copia);

    BSTfree(b);
    BSTfree(copia);

    return 0;
}