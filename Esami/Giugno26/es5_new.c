#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printSequence(char *n);

void printSequence_r(int level, char *n, int *sol, int k, int start) {
    if (level >= k) {
        for (int i = 1; i < k; ++i) {
            if (sol[i] < sol[i - 1]) {
                return;
            }
        }

        for (int g = 0; g < k; ++g) {
            for (int i = 0; i < k; ++i) {
                if (sol[i] == g) {
                    printf("%c", n[i]);
                }
            }
            printf(" ");
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < start; ++i) {
        sol[level] = i;
        printSequence_r(level + 1, n, sol, k, start);
    }

    sol[level] = start;
    printSequence_r(level + 1, n, sol, k, start + 1);
}

void printSequence(char *n) {
    int k = strlen(n) / sizeof(char);
    int *sol = calloc(k, sizeof(int));
    printSequence_r(0, n, sol, k, 0);
}


int main(int argc, char **argv) {
    /* Main di test */
    char n[] = "123";
    printSequence(n);

    return 0;
}
