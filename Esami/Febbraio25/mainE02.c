#include <stdio.h>
#include "bst.h"


static void test(const char *nome_test, BST b, int expected) {
    int result = BSTisBalanced(b);

    printf("%s: ", nome_test);

    if (result == expected) {
        printf("OK");
    } else {
        printf("ERRORE");
    }

    printf(" | atteso = %d, ottenuto = %d\n", expected, result);

    BSTfree(b);
}

int main(void) {
    BST b;

    /*
        Test 1: albero vuoto
        Atteso: bilanciato
    */
    b = BSTnew();
    test("Albero vuoto", b, 1);

    /*
              10
    */
    b = BSTnew();
    BSTsetRoot(b, 10);
    test("Un solo nodo", b, 1);

    /*
              10
             /  \
            5    15
    */
    b = BSTnew();
    BSTsetRoot(b, 10);
    BSTinsertLeft(b, 10, 5);
    BSTinsertRight(b, 10, 15);
    test("Radice con due figli", b, 1);

    /*
              10
             /
            5
    */
    b = BSTnew();
    BSTsetRoot(b, 10);
    BSTinsertLeft(b, 10, 5);
    test("Solo figlio sinistro", b, 1);

    /*
              10
             /
            5
           /
          2
    */
    b = BSTnew();
    BSTsetRoot(b, 10);
    BSTinsertLeft(b, 10, 5);
    BSTinsertLeft(b, 5, 2);
    test("Catena sinistra lunga 3", b, 0);

    /*
                10
              /    \
             5      15
            / \    /  \
           2   7  12   20
    */
    b = BSTnew();
    BSTsetRoot(b, 10);
    BSTinsertLeft(b, 10, 5);
    BSTinsertRight(b, 10, 15);
    BSTinsertLeft(b, 5, 2);
    BSTinsertRight(b, 5, 7);
    BSTinsertLeft(b, 15, 12);
    BSTinsertRight(b, 15, 20);
    test("Albero perfetto 7 nodi", b, 1);

    /*
                10
              /    \
             5      15
            / \
           2   7
    */
    b = BSTnew();
    BSTsetRoot(b, 10);
    BSTinsertLeft(b, 10, 5);
    BSTinsertRight(b, 10, 15);
    BSTinsertLeft(b, 5, 2);
    BSTinsertRight(b, 5, 7);
    test("Sbilanciato alla radice", b, 0);

    /*
                10
              /    \
             5      15
            /
           2
          /
         1
    */
    b = BSTnew();
    BSTsetRoot(b, 10);
    BSTinsertLeft(b, 10, 5);
    BSTinsertRight(b, 10, 15);
    BSTinsertLeft(b, 5, 2);
    BSTinsertLeft(b, 2, 1);
    test("Sbilanciato in sottoalbero", b, 0);

    return 0;
}