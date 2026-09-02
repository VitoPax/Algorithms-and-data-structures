#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

typedef struct {
    int val;
} Item;
typedef struct node* link;
struct node { Item item; link left; link right; };
struct btree_s { link root; };





int BTREEmaxSeq(BTREE t) {

}
//client
int main(int argc, char **argv) {
    /* you can implement your test case here [NOT NEEDED] */
    return 0;
}