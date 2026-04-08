#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CORSE 1000
#define MAX_LENGHT 31

typedef struct {
    int a;
    int m;
    int g;
}data_t;


typedef struct {
    int h;
    int m;
    int s;
}ora_t;

typedef struct {
    char *codice_tratta;
    char *partenza;
    char *destinazione;
    data_t data;
    ora_t ora_p;
    ora_t ora_d;
    int ritardo;
}corsa_t;

typedef enum {
    r_date,
    r_partenza,
    r_capolinea,
    r_ritardo,
    r_ritardo_tot,
    r_fine
}comando_e;


int readFile(char *filename, corsa_t **tabella);

int main(void) {
    corsa_t *tabella = NULL;
    int num_corse = readFile("../corse.txt", &tabella);
    fprintf(stdout, "%d\n", num_corse);

    for (int i = 0; i < num_corse; i++) {
        printf("Corsa %d:\n", i);

        printf("  Codice tratta: %s\n", tabella[i].codice_tratta);
        printf("  Partenza: %s\n", tabella[i].partenza);
        printf("  Destinazione: %s\n", tabella[i].destinazione);

        printf("  Data: %02d/%02d/%04d\n",
               tabella[i].data.g,
               tabella[i].data.m,
               tabella[i].data.a);

        printf("  Ora partenza: %02d:%02d:%02d\n",
               tabella[i].ora_p.h,
               tabella[i].ora_p.m,
               tabella[i].ora_p.s);

        printf("  Ora arrivo: %02d:%02d:%02d\n",
               tabella[i].ora_d.h,
               tabella[i].ora_d.m,
               tabella[i].ora_d.s);

        printf("  Ritardo: %d minuti\n", tabella[i].ritardo);

        printf("-----------------------------\n");
    }

    return 0;
}


int readFile(char *filename, corsa_t **tabella) {
    FILE *fin = fopen(filename, "r");
    int num_corse;
    int i;

    if (fin == NULL) {
        printf("Errore apertura file\n");
        return -1;
    }

    fscanf(fin, "%d", &num_corse);

    *tabella = malloc(num_corse * sizeof(corsa_t));
    if (*tabella == NULL) {
        printf("Errore allocazione memoria\n");
        fclose(fin);
        return -1;
    }

    char codice_tratta[MAX_LENGHT], partenza[MAX_LENGHT], destinazione[MAX_LENGHT];

    for (i = 0; i < num_corse; i++) {
        fscanf(fin, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d",
               codice_tratta,
               partenza,
               destinazione,
               &(*tabella)[i].data.a,
               &(*tabella)[i].data.m,
               &(*tabella)[i].data.g,
               &(*tabella)[i].ora_p.h,
               &(*tabella)[i].ora_p.m,
               &(*tabella)[i].ora_p.s,
               &(*tabella)[i].ora_d.h,
               &(*tabella)[i].ora_d.m,
               &(*tabella)[i].ora_d.s,
               &(*tabella)[i].ritardo);

        (*tabella)[i].codice_tratta = strdup(codice_tratta);
        (*tabella)[i].partenza = strdup(partenza);
        (*tabella)[i].destinazione = strdup(destinazione);
    }

    fclose(fin);
    return num_corse;
}
