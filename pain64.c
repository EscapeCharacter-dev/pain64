#include <stdio.h>
#include <stdint.h>
#include "pain64.h"

int main(void) {
    char program[] = {
        HALT,
    };
    pain64_start(program, sizeof(program));
    return 0;
}