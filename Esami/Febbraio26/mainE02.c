#include <stdio.h>
#include <string.h>
#include "E02.h"

int main(void) {
    BST b, c;
    Item x;

    b = BSTinit();

    strcpy(x.name, "M");
    BSTinsertLeaf(b, x);

    strcpy(x.name, "C");
    BSTinsertLeaf(b, x);

    strcpy(x.name, "T");
    BSTinsertLeaf(b, x);

    strcpy(x.name, "A");
    BSTinsertLeaf(b, x);

    strcpy(x.name, "E");
    BSTinsertLeaf(b, x);

    strcpy(x.name, "R");
    BSTinsertLeaf(b, x);

    strcpy(x.name, "Z");
    BSTinsertLeaf(b, x);

    printf("BST originale:\n");
    BSTshow(b);

    c = BSTdup(b);

    printf("\nBST duplicato:\n");
    BSTshow(c);

    BSTfree(b);
    BSTfree(c);

    return 0;
}