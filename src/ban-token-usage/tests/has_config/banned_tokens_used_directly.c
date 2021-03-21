#include "include_file.h"

/* FAKE */

#define ADD_A_VARIABLE(_x) int _x

int AVOID(void) {
    ADD_A_VARIABLE(foo);
    int EVIL = 0;
    return 0;
}

void EVIL(int AVOID, int BAD) {
    (void)AVOID;
    (void)BAD;
    return;
}