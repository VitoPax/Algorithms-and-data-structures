#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

link LINKnew(char *val, link next) {
    link l = malloc(sizeof(*l));
    l->val = strdup(val);
    l->next = next;
    return l;
}

void LINKfree(link l) {
    if (l == NULL) return;
    free(l->val);
    LINKfree(l->next);
    free(l);
}

void LINKprint(link l) {
    if (l == NULL) {
        printf("(null)\n");
        return;
    }

    printf("(%s) -> ", l->val);
    LINKprint(l->next);
}