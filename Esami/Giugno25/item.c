#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

Item ItemDup(Item i) {
    char *copy;

    if (i == NULL)
        return NULL;

    copy = malloc(strlen(i) + 1);
    if (copy == NULL)
        return NULL;

    strcpy(copy, i);
    return copy;
}

void ItemFree(Item i) {
    free(i);
}

void ItemPrint(Item i) {
    if (i != NULL)
        printf("%s", i);
}

int ItemCmp(Item a, Item b) {
    return strcmp(a, b);
}