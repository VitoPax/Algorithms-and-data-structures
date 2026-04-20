/*
    Si vogliono contare i numeri in una data base (base, compresa tra 2 e 10), aventi un dato numero di cifre
    (nDigits) tali da rispettare i seguenti vincoli:
    A. ogni cifra può comparire al più maxRip volte nel numero
    B. la differenza (in valore assoluto) tra due cifre consecutive può essere al massimo 2
    C. il numero di cifre distinte (senza tener conto delle ripetizioni) deve essere almeno pari a nDigits/2
    (divisione tra interi)
    Ad esempio, con base 8, 7 cifre, massimo numero di ripetizioni 3, il numero 5356533 rispetta i vincoli,
    3232224 non rispetta il primo vincolo, 5376551 non rispetta il secondo, 3223322 non rispetta il primo e il
    terzo.
    La funzione da realizzare ritorna come risultato il conteggio dei numeri che rispettano i vincoli. Il prototipo è
    int cntNum(int base, int nDigits, int maxRip);
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int cntNum(int base, int nDigits, int maxRip);


int cntNum(int base, int nDigits, int maxRip) {
    // Contatore dei numeri che rispettano i vincoli
    int cntOK = 0;


    return cntOK;
}


int main(int argc, char **argv) {
    /* you can implement your test case here [NOT NEEDED] */
    return 0;
}