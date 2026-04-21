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

char *KEYget(Item *item);
int ProcessItems(Item *vet, int n, Key *keys, Item *maxp);


int KEYcmp(Key k1, Key k2) {
    return strcmp(k1,k2);
}

void ITEMprint(Item *item) {
    printf("name: %s, val: %f\n", item->name, item->val);
}


char *KEYget(Item *item){
    return item->name;
}

int ProcessItems(Item *vet, int n, Key *keys, Item *maxp){
    int sum = 0;
    int dimS = 0;

    // Calcolo la dimensione della stringa concatenata
    for(int i = 0; i <n; i++){
        dimS = dimS + strlen(KEYget(&(vet[i])));
    }

    // Alloco la nuova stringa conoscendo dimS
    char *s = malloc(dimS*sizeof(char));

    for (int i = 0; i<dimS; i++){
        s[i] = KEYget(&(vet[i]));
    }
    printf("%s\n", s);

    char *tmp = KEYget(&(vet[0]));
    for(int i = 0; i<n; i++){
        if(KEYcmp(KEYget(&(vet[i])), &tmp)){
            *tmp = KEYget(&(vet[i]));
        }
        sum = sum + vet[i].val;
    }

    *maxp;

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