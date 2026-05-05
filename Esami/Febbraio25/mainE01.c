#include "editori.h"

int main(void) {
    EditoriTest("Anno zero", 0);
    EditoriTest("Anno uno", 1);
    EditoriTest("Fine Novecento", 1999);
    EditoriTest("Anno duemila", 2000);
    EditoriTest("Anno corrente", 2024);
    EditoriTest("Anno futuro", 2100);
    EditoriTest("Anno negativo", -1);

    return 0;
}
