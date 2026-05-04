#ifndef GIUGNO25_LIST_H
#define GIUGNO25_LIST_H

typedef struct node {
    char *val;
    struct node *next;
} *link;

typedef struct list {
    link head;
} *List;

link LINKnew(char *val, link next);

void LINKfree(link l);

void LINKprint(link l);


#endif //GIUGNO25_LIST_H
