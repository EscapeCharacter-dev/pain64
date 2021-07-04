#include <stdio.h>
#include <stdint.h>
#include "pain64.h"

#define PRINT  MOVU8RV, 0x06

int main(void) {
    char program[] = {
        MOVU32RV,
        0x02,
        0x16,
        0x54,
        0x32,
        0x00,

        MOVU16RV,
        0x04,
        0x06,
        0x7C,
        MOVU64RR,
        0x00,
        0x01,
        CMPRR,
        0x00,
        0x02,
        INC,
        0x01,
        JNER,
        0x04,
        HALT,
    };
    pain64_start(program, sizeof(program));
    return 0;
}