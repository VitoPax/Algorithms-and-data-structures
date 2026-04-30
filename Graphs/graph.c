#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct graph {
    int V;
    int E;
    int *ladj;
};