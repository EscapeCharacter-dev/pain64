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

static inline int _check_addr(uint64_t address) {
    return address >= MEM_SPACE || address == 0;
}

uint64_t *pain64_resolve_addr_U64(uint64_t address) {
    if (_check_addr(address)) {
        fprintf(stderr, "pain64.mmu(U64): Invalid addresss 0x%x\n", address);
        return 0;
    }
    return (uint64_t *)(_mem_space + address);
}

int64_t *pain64_resolve_addr_I64(uint64_t address) {
    if (_check_addr(address)) {
        fprintf(stderr, "pain64.mmu(I64): Invalid addresss 0x%x\n", address);
        return 0;
    }
    return (int64_t *)(_mem_space + address);
}

uint32_t *pain64_resolve_addr_U32(uint64_t address) {
    if (_check_addr(address)) {
        fprintf(stderr, "pain64.mmu(U32): Invalid addresss 0x%x\n", address);
        return 0;
    }
    return (uint32_t *)(_mem_space + address);
}

int32_t *pain64_resolve_addr_I32(uint64_t address) {
    if (_check_addr(address)) {
        fprintf(stderr, "pain64.mmu(I32): Invalid addresss 0x%x\n", address);
        return 0;
    }
    return (int32_t *)(_mem_space + address);
}

uint16_t *pain64_resolve_addr_U16(uint64_t address) {
    if (_check_addr(address)) {
        fprintf(stderr, "pain64.mmu(U16): Invalid addresss 0x%x\n", address);
        return 0;
    }
    return (uint16_t *)(_mem_space + address);
}

int16_t *pain64_resolve_addr_I16(uint64_t address) {
    if (_check_addr(address)) {
        fprintf(stderr, "pain64.mmu(I16): Invalid addresss 0x%x\n", address);
        return 0;
    }
    return (int16_t *)(_mem_space + address);
}

uint8_t *pain64_resolve_addr_U8(uint64_t address) {
    if (_check_addr(address)) {
        fprintf(stderr, "pain64.mmu(U8): Invalid addresss 0x%x\n", address);
        return 0;
    }
    return (uint8_t *)(_mem_space + address);
}

int8_t *pain64_resolve_addr_I8(uint64_t address) {
    if (_check_addr(address)) {
        fprintf(stderr, "pain64.mmu(I8): Invalid addresss 0x%x\n", address);
        return 0;
    }
    return (int8_t *)(_mem_space + address);
}

struct pain64_device *pain64_resolve_addr_DEVICE(uint64_t address) {
    if (_check_addr(address)) {
        fprintf(stderr, "pain64.mmu(D): Invalid addresss 0x%x\n", address);
        return 0;
    }
    return (struct pain64_device *)(_mem_space + address);
}

void pain64_close_mem(void) {
    free(_mem_space);
    return;
}

void pain64_load_program(uint64_t offset, uint8_t *code, size_t code_size) {
    memcpy((char *)(_mem_space + offset), code, code_size);
    return;
}