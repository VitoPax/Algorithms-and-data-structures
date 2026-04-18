/*
 *Esercizio 1
    Sia dato un vettore vet di N naturali. Si definisce elemento maggioritario, se esiste, quel valore che
    ha numero di occorrenze > N/2.

    Esempio: se N= 7 e vet contiene 3, 3, 9, 4, 3, 5, 3 l’elemento maggioritario è 3.
    Se N=8 e vet contiene 0, 1, 0, 2, 3, 4, 0, 5 non esiste elemento maggioritario.

    Si scriva una funzione maggioritario che, dati N e vet, visualizzi l’elemento maggioritario se
    esiste, -1 se non esiste.

    Il prototipo sia:
    int majority( int *a, int N);

    Vincoli: si risolva mediante ricorsione. Non è lecito utilizzare né algoritmi di ordinamento, né
    algoritmi di complessità O(n) che si possono trovare in rete.

*/

#include <stdio.h>

int majority(int *a, int N);
int majorityR(int *a, int l, int r);

int main(void){
    int v1[] = {3, 3, 9, 4, 3, 5, 3};
    int N1 = 7;

    int v2[] = {0, 1, 0, 2, 3, 4, 0, 5};
    int N2 = 8;

    int ris1 = majority(v1, N1);
    int ris2 = majority(v2, N2);

    printf("Risultato vettore 1: %d\n", ris1);
    printf("Risultato vettore 2: %d\n", ris2);

    return 0;
}

int majority(int *a, int N) {
    return majorityR(a, 0, N - 1);
}


int majorityR(int *a, int l, int r) {
    // caso base: intervallo con un solo elemento
    if (l == r)
        return a[l];

    // divido il vettore in due metà
    int m = (l + r) / 2;

    // candidato dalla metà sinistra
    int sx = majorityR(a, l, m);

    // candidato dalla metà destra
    int dx = majorityR(a, m + 1, r);

    // se coincidono, posso restituirlo subito
    if (sx == dx)
        return sx;

    // lunghezza dell'intervallo corrente
    int len = r - l + 1;

    // conto quante volte compaiono sx e dx nell'intervallo [l..r]
    int countSx = 0;
    int countDx = 0;

    for (int i = l; i <= r; i++) {
        if (a[i] == sx)
            countSx++;

        if (a[i] == dx)
            countDx++;
    }

    // verifico se sx è maggioritario
    if (countSx > len / 2)
        return sx;

    // verifico se dx è maggioritario
    if (countDx > len / 2)
        return dx;

    // se nessuno dei due supera metà, non esiste maggioritario
    return -1;
}