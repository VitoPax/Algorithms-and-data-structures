#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

static link newNode(Item item, link left, link right);
static link insertR(link root, Item item);
static void printPreorderR(link root);
static void freeR(link root);

BST BSTinit(void) {
    BST b;

    b = malloc(sizeof *b);
    if (b == NULL)
        return NULL;

    b->root = NULL;

    return b;
}

static link newNode(Item item, link left, link right) {
    link x;

    x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;

    x->item = ItemDup(item);
    x->left = left;
    x->right = right;

    return x;
}

void BSTinsert(BST b, Item item) {
    if (b == NULL)
        return;

    b->root = insertR(b->root, item);
}

static link insertR(link root, Item item) {
    if (root == NULL)
        return newNode(item, NULL, NULL);

    if (ItemCmp(item, root->item) < 0)
        root->left = insertR(root->left, item);
    else
        root->right = insertR(root->right, item);

    return root;
}

void BSTprintPreorder(BST b) {
    if (b == NULL)
        return;

    printPreorderR(b->root);
    printf("\n");
}

static void printPreorderR(link root) {
    if (root == NULL)
        return;
    ItemPrint(root->item);
    printf(" ");
    printPreorderR(root->left);
    printPreorderR(root->right);
}

void BSTfree(BST b) {
    if (b == NULL)
        return;

    freeR(b->root);
    free(b);
}

static void freeR(link root) {
    if (root == NULL)
        return;

    freeR(root->left);
    freeR(root->right);

    ItemFree(root->item);
    free(root);
}