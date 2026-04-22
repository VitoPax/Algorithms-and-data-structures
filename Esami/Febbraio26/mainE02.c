#include <stdio.h>
#include <string.h>
#include "E02.h"

int main(void) {
    BST b, bDup;
    Item x;

    b = BSTinit();
    if (b == NULL)
        return 1;

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

    bDup = BSTdup(b);
    if (bDup == NULL) {
        BSTfree(b);
        return 1;
    }

    printf("\nBST duplicato:\n");
    BSTshow(bDup);

    BSTfree(b);
    BSTfree(bDup);

    return 0;
}