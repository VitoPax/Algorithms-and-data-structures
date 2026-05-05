#include "editori.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nome;
    struct libro **libri;
    int n_libri;
} editore_t;

struct editori {
    editore_t *editori;
    int n_editori;
};


/* =========================
   FUNZIONI RICHIESTE ALL'ESAME
   ========================= */

editori_adt EditoriDup(editori_adt e) {
    editori_adt copia = malloc(sizeof(*copia));

    copia->n_editori = e->n_editori;
    copia->editori = malloc(e->n_editori * sizeof(editore_t));

    for (int i = 0; i < copia->n_editori; i++) {
        copia->editori[i].n_libri = e->editori[i].n_libri;
        copia->editori[i].nome = strdup(e->editori[i].nome);

        copia->editori[i].libri = malloc(copia->editori[i].n_libri * sizeof(struct libro *));

        for (int j = 0; j < copia->editori[i].n_libri; j++) {
            copia->editori[i].libri[j] = e->editori[i].libri[j];
        }
    }

    return copia;
}

void EditoriFree(editori_adt e) {
    if (e == NULL) {
        return;
    }

    for (int i = 0; i < e->n_editori; i++) {
        free(e->editori[i].nome);

        for (int j = 0; j < e->editori[i].n_libri; j++) {
            free(e->editori[i].libri[j]);
        }

        free(e->editori[i].libri);
    }

    free(e->editori);
    free(e);
}


/* =========================
   FUNZIONI DI SUPPORTO TEST
   ========================= */

editori_adt EditoreNew(const char *nome, int anno) {
    editori_adt e = malloc(sizeof(*e));

    e->n_editori = 1;
    e->editori = malloc(sizeof(editore_t));

    e->editori[0].nome = strdup(nome);
    e->editori[0].n_libri = 1;
    e->editori[0].libri = malloc(sizeof(struct libro *));

    e->editori[0].libri[0] = malloc(sizeof(struct libro));
    e->editori[0].libri[0]->anno = anno;

    return e;
}

void EditoriStampa(editori_adt e, const char *label) {
    printf("\n%s\n", label);
    printf("n_editori = %d\n", e->n_editori);

    for (int i = 0; i < e->n_editori; i++) {
        printf("editore[%d].nome = %s\n", i, e->editori[i].nome);
        printf("editore[%d].n_libri = %d\n", i, e->editori[i].n_libri);

        for (int j = 0; j < e->editori[i].n_libri; j++) {
            printf("libri[%d] address = %p\n",
                   j,
                   (void *) e->editori[i].libri[j]);

            if (e->editori[i].libri[j] != NULL) {
                printf("libri[%d]->anno = %d\n",
                       j,
                       e->editori[i].libri[j]->anno);
            }
        }
    }
}

void EditoriTest(const char *nome, int anno) {
    printf("\n==============================\n");
    printf("TEST: nome = \"%s\", anno = %d\n", nome, anno);
    printf("==============================\n");

    editori_adt e = EditoreNew(nome, anno);
    editori_adt copia = EditoriDup(e);

    EditoriStampa(e, "ORIGINALE");
    EditoriStampa(copia, "COPIA");

    printf("\nControlli:\n");

    if (e != copia) {
        printf("OK: struct editori duplicata\n");
    } else {
        printf("ERRORE: stessa struct editori\n");
    }

    if (e->editori != copia->editori) {
        printf("OK: vettore editori duplicato\n");
    } else {
        printf("ERRORE: vettore editori condiviso\n");
    }

    if (e->editori[0].nome != copia->editori[0].nome) {
        printf("OK: nome duplicato\n");
    } else {
        printf("ERRORE: nome condiviso\n");
    }

    if (strcmp(e->editori[0].nome, copia->editori[0].nome) == 0) {
        printf("OK: contenuto nome uguale\n");
    } else {
        printf("ERRORE: contenuto nome diverso\n");
    }

    if (e->editori[0].libri != copia->editori[0].libri) {
        printf("OK: vettore libri duplicato\n");
    } else {
        printf("ERRORE: vettore libri condiviso\n");
    }

    if (e->editori[0].libri[0] == copia->editori[0].libri[0]) {
        printf("OK per la tua versione: puntatore al libro condiviso\n");
    } else {
        printf("ERRORE per la tua versione: libro duplicato\n");
    }

    if (e->editori[0].libri[0]->anno == copia->editori[0].libri[0]->anno) {
        printf("OK: anno uguale\n");
    } else {
        printf("ERRORE: anno diverso\n");
    }

    /*
       Necessario perché la tua EditoriDup condivide il puntatore al libro,
       mentre la tua EditoriFree libera anche i libri.
       Quindi, senza questa riga, liberando sia copia sia originale,
       avresti double free.
    */
    EditoriFree(copia);

    e->editori[0].libri[0] = NULL;
    EditoriFree(e);

    printf("TEST COMPLETATO\n");
}