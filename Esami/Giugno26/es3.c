#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char *name; } Item;

typedef struct node {
    Item val;
    struct node *next;
} *link;

int GenListsByLength(char **names, int n, link **listArrayP);

int GenListsByLength(char **names, int n, link **listArrayP) {

}


int main(int argc, char **argv) {
    /* you can implement your test case here [NOT NEEDED] */
    return 0;
}