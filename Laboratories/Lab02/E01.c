#include <stdio.h>
#include <stdlib.h>


int gcd(int a, int b);
void swap(int *a, int *b);

int main(void) {
    int a, b;

    printf("Inserisci due numeri: ");
    scanf("%d %d", &a, &b);

    int risultato = gcd(a, b);

    printf("MCD(%d, %d) = %d\n", a, b, risultato);

    return 0;
}

int gcd(int a, int b) {
    if (a < b)
        swap(&a, &b);

    if (b == 0)
        return a;

    if (a == b)
        return a;

    if (a % 2 == 0 && b % 2 == 0)
        return 2 * gcd(a / 2, b / 2);

    if (a % 2 == 0 && b % 2 != 0)
        return gcd(a / 2, b);

    if (a % 2 != 0 && b % 2 == 0)
        return gcd(a, b / 2);

    return gcd((a - b) / 2, b);
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;

}