#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static uint8_t *_mem_space;

#define MEM_SPACE   sizeof(uint64_t) * 1024 * 1000 * 64

void pain64_open_mem(void) {
    _mem_space = malloc(MEM_SPACE);
    return;
}

uint64_t *pain64_resolve_addr(uint64_t address) {
    if (address >= MEM_SPACE || address == 0) {
        fprintf(stderr, "pain64.mmu: Invalid addresss 0x%x\n", address);
        return 0;
    }
    return (uint64_t *)(_mem_space + address);
}

void pain64_close_mem(void) {
    free(_mem_space);
    return;
}

void pain64_load_program(uint64_t offset, uint8_t *code, size_t code_size) {
    memcpy((char *)(_mem_space + offset), code, code_size);
    return;
}