/*
    È dato un tipo struct node (e il relativo puntatore link) adatti a rappresentare nodi e puntatori in lista concatenata.
    typedef struct node {
    char *val;
    struct node *next;
    } *link;
    Il campo val punta a una stringa di proprietà del nodo. È data una lista (realizzata con questo tipo di dato) di stringhe,
    non ordinata e contenete eventuali dati ripetuti (anche più volte e non necessariamente contigui). Si consideri quale
    esempio, la lista seguente
    ->”Roma”->”Milano”->”Palermo”->”Roma”->”Torino”->”Genova”->”Roma”->”Palermo”
    Si realizzi la funzione avente prototipo
    link removeDupl(link h);
    in grado di rimuovere dalla lista gli elementi duplicati. Di ogni stringa replicata più di una volta va mantenuta la
    prima istanza. I dati rimasti debbono conservare l’ordina originale. La lista precedentemente esemplificata,
    diventerebbe
    ->”Roma”->”Milano”->”Palermo”->”Torino”->”Genova”
    Attenzione: non va generata una nuova lista ma occorre ritornare il puntatore alla lista modificata.
*/

