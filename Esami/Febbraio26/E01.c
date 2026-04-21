/*  Sono dati il quasi ADT Item, il tipo Key e le funzioni KEYcmp e ITEMprint, definiti sotto.
    Sapendo che il campo name è la chiave, si scriva la funzione KEYget, che, dato un Item, ne ritorni la chiave.
    Si realizzi poi la funzione ProcessItems che, dato un vettore di Item, ritorni 3 risultati

    A. una stringa dinamica contenente la concatenazione delle chiavi presenti nel vettore (la stringa va
    allocata esattamente della dimensione necessaria, senza sovrallocazione),

    B. il puntatore all’item contenente la chiave più grande (usando KEYcmp per i confronti)

    C. la somma di tutti i campi val nel vettore.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXS 40

typedef struct {
    char name[MAXS];
    float val;
} Item;

typedef char *Key;


int KEYcmp(Key k1, Key k2);
void ITEMprint(Item *item);

Key KEYget(Item *item);
float ProcessItems(Item *vet, int n, Key *keys, Item **maxp);


int KEYcmp(Key k1, Key k2) {
    return strcmp(k1,k2);
}

void ITEMprint(Item *item) {
    printf("name: %s, val: %f\n", item->name, item->val);
}


Key KEYget(Item *item){
    return item->name;
}

float ProcessItems(Item *vet, int n, Key *keys, Item **maxp){
    float sum = 0;
    int i, lenTot = 0, posMax = 0;

    for (i = 0; i < n; i++) {
        sum += vet[i].val;
        lenTot += strlen(KEYget(&vet[i]));

        if (KEYcmp(KEYget(&vet[i]), KEYget(&vet[posMax])) > 0)
            posMax = i;
    }

    *keys = malloc((lenTot + 1) * sizeof(char));

    if (*keys == NULL)
        return 0;

    // Stringa vuota
    (*keys)[0] = '\0';

    // Concatenazione
    for (i = 0; i < n; i++) {
        strcat(*keys, KEYget(&vet[i]));
    }

    // Assegnazione del massimo
    *maxp = &vet[posMax];

    return sum;
}

int main (void) {
    Item vet[]={{"Parigi",2.2},{"Roma",2.75},{"Londra",8.8},{"Berlino",3.75}};
    Item *maxp;
    char *keys; float sumVal;
    int n=sizeof(vet)/sizeof(Item);
    sumVal = ProcessItems(vet,n,&keys,&maxp);
    printf("La somma dei valori e': %f\n", sumVal);
    printf("La concatenazione delle stringhe e': %s\n", keys);
    printf("Il massimo e': ");
    ITEMprint(maxp);
    free(keys);
    return 0;
}