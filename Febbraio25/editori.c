#include <stdio.h>
#include <stdlib.h>
#include "editori.h"

typedef struct {
    char *nome;
    struct libro **libri;
    int n_libri;
}editore_t;

struct editori {
    editore_t *editori;
    int n_editori;
};


editori_adt EditoriDup(editori_adt e) {



}


void EditoriFree(editori_adt e) {

    for (int i = 0; i<e->n_editori; i++) {
        editore_t editore = e->editori[i];
        free(editore.nome);
        for (int j = 0; j<editore.n_libri; j++) {
            free(editore.libri[j]);
        }
        free(editore.libri);
    }
    free(e->editori);

}