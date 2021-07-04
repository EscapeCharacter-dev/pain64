#include <stdio.h>
#include <stdint.h>
#include "pain64.h"

int main(void) {
    char program[] = {
        MOVRV,
        0,
        0x34,
        0x24,
        0x54,
        0x32,
        0x34,
        0x24,
        0x54,
        0x32,
        MOVRV,
        1,
        0x34,
        0x24,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        ADDRR,
        0,
        1,
        BREAKPOINT,
        HALT,
    };
    pain64_start(program, sizeof(program));
    return 0;
}