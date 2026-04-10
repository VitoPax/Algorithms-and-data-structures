#include <stdio.h>
#include <stdlib.h>

int **readMatrix(char *filename, int *nr, int *nc);
int **malloc2dR(int nr, int nc);
void free2d(int **m, int nr);
void printMatrix(int **m, int nr, int nc);

void separa(int **m, int nr, int nc, int **white, int **black, int *whiteCount, int *blackCount);
void printVector(int *v, int n);

int main() {
    int nr, nc;
    int **mat;
    int *white, *black;
    int whiteCount, blackCount;

    mat = readMatrix("../mat.txt", &nr, &nc);

    if (mat == NULL) {
        printf("Errore nella lettura della matrice\n");
        return 1;
    }

    /* Print for debugging */
    printf("Number of rows: %d\n", nr);
    printf("Number of columns: %d\n", nc);
    printMatrix(mat, nr, nc);

    separa(mat, nr, nc, &white, &black, &whiteCount, &blackCount);

    /* Print for debugging */
    printf("Vettore bianchi:\n");
    printVector(white, whiteCount);

    printf("Vettore neri:\n");
    printVector(black, blackCount);

    /* Deallocation*/
    free(white);
    free(black);
    free2d(mat, nr);

    return 0;
}

int **readMatrix(char *filename, int *nr, int *nc) {
    FILE *fin = fopen(filename, "r");
    int **mat;

    if (fin == NULL) {
        printf("File not found\n");
        return NULL;
    }

    fscanf(fin, "%d %d", nr, nc);

    mat = malloc2dR(*nr, *nc);
    if (mat == NULL) {
        fclose(fin);
        return NULL;
    }

    for (int i = 0; i < *nr; i++) {
        for (int j = 0; j < *nc; j++) {
            fscanf(fin, "%d", &mat[i][j]);
        }
    }

    fclose(fin);
    return mat;
}

int **malloc2dR(int nr, int nc) {
    int **m = malloc(nr * sizeof(int *));
    if (m == NULL) {
        return NULL;
    }

    for (int i = 0; i < nr; i++) {
        m[i] = malloc(nc * sizeof(int));
        if (m[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(m[k]);
            }
            free(m);
            return NULL;
        }
    }

    return m;
}

void free2d(int **m, int nr) {
    for (int i = 0; i < nr; i++) {
        free(m[i]);
    }
    free(m);
}

void printMatrix(int **m, int nr, int nc) {
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void separa(int **m, int nr, int nc, int **white, int **black, int *whiteCount, int *blackCount) {
    int i, j;
    int whiteIndex = 0, blackIndex = 0;

    *whiteCount = 0;
    *blackCount = 0;


    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            if ((i + j) % 2 == 0)
                (*whiteCount)++;
            else
                (*blackCount)++;
        }
    }

    *white = malloc((*whiteCount) * sizeof(int));
    *black = malloc((*blackCount) * sizeof(int));

    if (*white == NULL || *black == NULL) {
        free(*white);
        free(*black);
        *white = NULL;
        *black = NULL;
        *whiteCount = 0;
        *blackCount = 0;
        return;
    }

    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            if ((i + j) % 2 == 0) {
                (*white)[whiteIndex] = m[i][j];
                whiteIndex++;
            } else {
                (*black)[blackIndex] = m[i][j];
                blackIndex++;
            }
        }
    }
}

void printVector(int *v, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}