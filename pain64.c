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
        HALT,
    };
    pain64_start(program, sizeof(program));
    return 0;
}