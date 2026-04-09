#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define MAX_CORSE 1000
#define MAX_LENGTH 31

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
    r_fine,
    r_err
}comando_e;

/* Prototypes */
int leggiFile(char *filename, corsa_t **tabella);
void liberaTabella(corsa_t *tabella, int n);

comando_e leggiComando(void);
void selezionaDati(corsa_t *tabella, int n, comando_e cmd);

int confrontaDate(data_t d1, data_t d2);
int dataCompresa(data_t d, data_t inizio, data_t fine);

void stampaCorsa(corsa_t c);
void corsePerDate(corsa_t *tabella, int n, data_t d1, data_t d2);
void corsePerPartenza(corsa_t *tabella, int n, char *fermata);
void corsePerCapolinea(corsa_t *tabella, int n, char *fermata);
void corseInRitardo(corsa_t *tabella, int n, data_t d1, data_t d2);
void ritardoTotale(corsa_t *tabella, int n, char *codice);

int main(void) {
    corsa_t *tabella = NULL;
    int num_corse = leggiFile("../corse.txt", &tabella);
    fprintf(stdout, "Ci sono %d corse\n", num_corse);

    comando_e cmd;

    do {
        cmd = leggiComando();
        if (cmd != r_fine && cmd != r_err) {
            selezionaDati(tabella, num_corse, cmd);
        } else if (cmd == r_err) {
            printf("Comando non valido\n");
        }
    } while (cmd != r_fine);

    liberaTabella(tabella, num_corse);

    /* Used for debugging
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
    } */

    return 0;
}


int leggiFile(char *filename, corsa_t **tabella) {
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

    char codice_tratta[MAX_LENGTH], partenza[MAX_LENGTH], destinazione[MAX_LENGTH];

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

void liberaTabella(corsa_t *tabella, int n) {
    int i;
    for (i = 0; i < n; i++) {
        free(tabella[i].codice_tratta);
        free(tabella[i].partenza);
        free(tabella[i].destinazione);
    }
    free(tabella);
}

comando_e leggiComando(void) {
    char cmd[MAX_LENGTH];

    printf("\nInserisci comando (date / partenza / capolinea / ritardo / ritardo_tot / fine): ");
    scanf("%s", cmd);

    if (strcmp(cmd, "date") == 0) return r_date;
    if (strcmp(cmd, "partenza") == 0) return r_partenza;
    if (strcmp(cmd, "capolinea") == 0) return r_capolinea;
    if (strcmp(cmd, "ritardo") == 0) return r_ritardo;
    if (strcmp(cmd, "ritardo_tot") == 0) return r_ritardo_tot;
    if (strcmp(cmd, "fine") == 0) return r_fine;

    return r_err;
}
void selezionaDati(corsa_t *tabella, int n, comando_e cmd) {
    data_t d1, d2;
    char fermata[MAX_LENGTH];
    char codice[MAX_LENGTH];

    switch (cmd) {
        case r_date:
            printf("Inserisci data iniziale (aaaa/mm/gg): ");
            scanf("%d/%d/%d", &d1.a, &d1.m, &d1.g);

            printf("Inserisci data finale (aaaa/mm/gg): ");
            scanf("%d/%d/%d", &d2.a, &d2.m, &d2.g);

            corsePerDate(tabella, n, d1, d2);
            break;

        case r_partenza:
            printf("Inserisci fermata di partenza: ");
            scanf("%s", fermata);

            corsePerPartenza(tabella, n, fermata);
            break;

        case r_capolinea:
            printf("Inserisci fermata di capolinea: ");
            scanf("%s", fermata);

            corsePerCapolinea(tabella, n, fermata);
            break;

        case r_ritardo:
            printf("Inserisci data iniziale (aaaa/mm/gg): ");
            scanf("%d/%d/%d", &d1.a, &d1.m, &d1.g);

            printf("Inserisci data finale (aaaa/mm/gg): ");
            scanf("%d/%d/%d", &d2.a, &d2.m, &d2.g);

            corseInRitardo(tabella, n, d1, d2);
            break;

        case r_ritardo_tot:
            printf("Inserisci codice tratta: ");
            scanf("%s", codice);

            ritardoTotale(tabella, n, codice);
            break;

        default:
            break;
    }
}

int confrontaDate(data_t d1, data_t d2) {
    if (d1.a != d2.a) return d1.a - d2.a;
    if (d1.m != d2.m) return d1.m - d2.m;
    return d1.g - d2.g;
}

int dataCompresa(data_t d, data_t inizio, data_t fine) {
    return (confrontaDate(d, inizio) >= 0 && confrontaDate(d, fine) <= 0);
}

void stampaCorsa(corsa_t c) {
    printf("%s %s %s %04d/%02d/%02d %02d:%02d:%02d %02d:%02d:%02d %d",
           c.codice_tratta,
           c.partenza,
           c.destinazione,
           c.data.a, c.data.m, c.data.g,
           c.ora_p.h, c.ora_p.m, c.ora_p.s,
           c.ora_d.h, c.ora_d.m, c.ora_d.s,
           c.ritardo);
}

void corsePerDate(corsa_t *tabella, int n, data_t d1, data_t d2) {
    int i;

    printf("\nCorse partite nell'intervallo di date:\n");
    for (i = 0; i < n; i++) {
        if (dataCompresa(tabella[i].data, d1, d2)) {
            stampaCorsa(tabella[i]);
            printf("\n");
        }
    }
}

void corsePerPartenza(corsa_t *tabella, int n, char *fermata) {
    int i;

    printf("\nCorse partite da %s:\n", fermata);
    for (i = 0; i < n; i++) {
        if (strcmp(tabella[i].partenza, fermata) == 0) {
            stampaCorsa(tabella[i]);
            printf("\n");
        }
    }
}

void corsePerCapolinea(corsa_t *tabella, int n, char *fermata) {
    int i;

    printf("\nCorse con capolinea %s:\n", fermata);
    for (i = 0; i < n; i++) {
        if (strcmp(tabella[i].destinazione, fermata) == 0) {
            stampaCorsa(tabella[i]);
            printf("\n");
        }
    }
}

void corseInRitardo(corsa_t *tabella, int n, data_t d1, data_t d2) {
    int i;

    printf("\nCorse arrivate in ritardo nell'intervallo di date:\n");
    for (i = 0; i < n; i++) {
        if (dataCompresa(tabella[i].data, d1, d2) && tabella[i].ritardo > 0) {
            stampaCorsa(tabella[i]);
            printf("\n");
        }
    }
}

void ritardoTotale(corsa_t *tabella, int n, char *codice) {
    int i;
    int somma = 0;

    for (i = 0; i < n; i++) {
        if (strcmp(tabella[i].codice_tratta, codice) == 0) {
            somma += tabella[i].ritardo;
        }
    }

    printf("\nRitardo totale della tratta %s: %d\n", codice, somma);
}