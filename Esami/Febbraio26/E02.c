/*  È dato un tipo BST (ADT di prima classe), avente nodi estesi in modo tale da contenere puntatore al padre e
    dimensione del sottoalbero. Il tipo Item (quasi ADT) e le struct BSTnode (con puntatore link) e
    binarysearchtree sono definiti come segue

    typedef struct {
        char name[MAXC];
    } Item;
    typedef struct BSTnode* link;
    struct BSTnode {Item item; link p; link l; link r; int N; };
    struct binarysearchtree { link root; link z; };
    typedef struct binarysearchtree *BST;

    Si scriva una funzione che, dato un BST b, generi un duplicato (un BST con la stessa topologia, contenente un
    duplicato dei dati).

    La funzione abbia prototipo
    BST BSTdup(BST b);

    Se utile per la soluzione, si possono richiamare funzioni spiegate a lezione.
*/

