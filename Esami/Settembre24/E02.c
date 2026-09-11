/*
 *
È dato un BST avente come valori delle stringhe, che fungono anche da chiave di ricerca.
Si scriva una funzione che determini la foglia a profondità massima MAXF (in caso di uguaglianza, si selezioni la foglia con chiave maggiore).
La funzione stampi a ritroso (quindi da foglia a radice) le chiavi sul cammino che connette la foglia MAXF alla radice.
Il prototipo della funzione deve essere:

void BSTprintDeepest(BST b);

Si richiede, oltre alla funzione, la definizione del tipo BST (ADT di prima classe) e del tipo usato per il nodo.

*/


typedef struct BSTnode *link;

struct BSTnode {
    char *key;
};

typedef struct bst *BST;

struct bst {
    link root;
};
