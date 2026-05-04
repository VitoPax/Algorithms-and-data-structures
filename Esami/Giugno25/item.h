#ifndef GIUGNO25_ITEM_H
#define GIUGNO25_ITEM_H

typedef char *Item;

Item ItemDup(Item i);
void ItemFree(Item i);
void ItemPrint(Item i);
int ItemCmp(Item a, Item b);

#endif //GIUGNO25_ITEM_H
