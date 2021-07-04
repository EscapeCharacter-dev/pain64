#include <stdio.h>
#include <stdint.h>
#include "pain64.h"

int main(void) {
    char program[] = {
        MOVU8RV,
        0,
        0x34,
        MOVU8RV,
        1,
        0x34,
        ADDRR,
        0,
        1,
        BREAKPOINT,
        HALT,
    };
    pain64_start(program, sizeof(program));
    return 0;
}