#ifndef FEBBRAIO25_EDITORI_H
#define FEBBRAIO25_EDITORI_H


typedef struct editori *editori_adt;


editori_adt EditoriDup(editori_adt e);
void EditoriFree(editori_adt e);

#endif //FEBBRAIO25_EDITORI_H
