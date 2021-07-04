#include <stdio.h>
#include <stdint.h>
#include "pain64.h"

int main(void) {
    char program[] = {
        BREAKPOINT,
        MOVU16RV,
        0x00,
        0x00,
        0x7C,
        JMPR,
        0x00,
        HALT,
    };
    pain64_start(program, sizeof(program));
    return 0;
}