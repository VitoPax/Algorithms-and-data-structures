#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Item; // Dichiaro un Item di tipo intero solo per rimanere generico usando poi Item .

typedef struct node *link;

struct node {
    Item val;
    link next;
};

struct list {
    link root;
    int N;
};
