#ifndef FEBBRAIO25_EDITORI_H
#define FEBBRAIO25_EDITORI_H

struct libro {
    int anno;
};

typedef struct editori *editori_adt;

/* Funzioni del punto c */
editori_adt EditoriDup(editori_adt e);
void EditoriFree(editori_adt e);

/* Funzioni solo per creare/testare l'ADT */
editori_adt EditoreNew(const char *nome, int anno);
void EditoriStampa(editori_adt e, const char *label);
void EditoriTest(const char *nome, int anno);


#endif //FEBBRAIO25_EDITORI_H