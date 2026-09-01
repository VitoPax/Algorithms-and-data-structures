#include <stdio.h>

typedef int vet;

void insertionSort(vet *A, int n){
    int key, j;

    for(int i = 1; i < n; i++){
        key = A[i];

        j = i - 1;

        while(j >= 0 && A[j] > key){
            A[j + 1] = A[j];
            j = j - 1;
        }

        A[j + 1] = key;
    }
}

int main(){

    vet A[] = {5, 3, 8, 1, 4, 2};

    int n = sizeof(A) / sizeof(A[0]);

    printf("Vettore prima dell'ordinamento:\n");

    for(int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }

    insertionSort(A, n);

    printf("\n\nVettore dopo l'ordinamento:\n");

    for(int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }

    printf("\n");

    return 0;
}