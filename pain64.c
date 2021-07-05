#include <stdio.h>
#include <stdint.h>
#include "pain64.h"

int main(void) {
    char program[] = {
        MOVU8RV,
        0x07,
        0x04,
        MOVU8RV,
        0x05,
        0x00,
        MOVU8RV,
        0x04,
        0x50,
        OUT,
        HALT,
    };
    pain64_start(program, sizeof(program));
    return 0;
}