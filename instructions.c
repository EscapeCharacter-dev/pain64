#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "pain64.h"

// 16 registers ought to be enough
static uint64_t	registers[16];

// 8 64-bit floating point registers
static float64_t fregisters[8];

/* General purpose registers */
uint64_t *const R0 = &(registers[0]);
uint64_t *const R1 = &(registers[1]);
uint64_t *const R2 = &(registers[2]);
uint64_t *const R3 = &(registers[3]);
uint64_t *const R4 = &(registers[4]);
uint64_t *const R5 = &(registers[5]);
uint64_t *const R6 = &(registers[6]);
uint64_t *const R7 = &(registers[7]);
/* Pointer reigsters */
uint64_t *const IP = &(registers[8]);	// Instruction Pointer
uint64_t *const BP = &(registers[9]);   // Base Stack Pointer
uint64_t *const SP = &(registers[10]);  // Top Stack Pointer (gets incremented and decremented by PUSH and POP)
/* Misc */
uint64_t *const FG = &(registers[11]);  // Flag register

/* General purpose floating-point registers */
float64_t *const F0 = &(fregisters[0]);
float64_t *const F1 = &(fregisters[1]);
float64_t *const F2 = &(fregisters[2]);
float64_t *const F3 = &(fregisters[3]);
float64_t *const F4 = &(fregisters[4]);
float64_t *const F5 = &(fregisters[5]);
float64_t *const F6 = &(fregisters[6]);
float64_t *const F7 = &(fregisters[7]);

static int halted = 0;

#ifndef _FOLD_HLT

static inline void _halt(void) {
    halted = 1;
    return;
}

#endif

#ifndef _FOLD_NOP

static inline void _nop(void) {
    return;
}

#endif

#ifndef _FOLD_MOV

static inline void _mov_f64_r_v(float64_t *reg, float64_t val) {
    *reg = val;
    return;
}

static inline void _mov_f64_r_r(float64_t *dest, float64_t *src) {
    *dest = *src;
    return;
}

static inline void _mov_f64_r_a(float64_t *dest, uint64_t addr) {
    *dest = *pain64_resolve_addr_F64(addr);
    return;
}

static inline void _mov_f64_a_r(uint64_t dest, float64_t *reg) {
    *pain64_resolve_addr_F64(dest) = *reg;
    return;
}

static inline void _mov_f64_a_v(uint64_t dest, float64_t value) {
    *pain64_resolve_addr_F64(dest) = value;
}

static inline void _mov_f32_r_v(float64_t *reg, float32_t val) {
    *reg = val;
    return;
}

static inline void _mov_f32_r_r(float64_t *dest, float64_t *src) {
    *dest = *(float32_t *)src;
    return;
}

static inline void _mov_f32_r_a(float64_t *dest, uint64_t addr) {
    *dest = *pain64_resolve_addr_F32(addr);
    return;
}

static inline void _mov_f32_a_r(uint64_t dest, float64_t *reg) {
    *pain64_resolve_addr_F32(dest) = *reg;
    return;
}

static inline void _mov_f32_a_v(uint64_t dest, float32_t value) {
    *pain64_resolve_addr_F32(dest) = value;
}

static inline void _mov_u64_r_v(uint64_t *reg, uint64_t val) {
    *reg = val;
    return;
}

static inline void _mov_u64_r_r(uint64_t *dest, uint64_t *src) {
    *dest = *src;
    return;
}

static inline void _mov_u64_r_a(uint64_t *reg, uint64_t addr) {
    *reg = *pain64_resolve_addr_U64(addr);
    return;
}

static inline void _mov_u64_a_r(uint64_t dest_addr, uint64_t *reg) {
    *pain64_resolve_addr_U64(dest_addr) = *reg;
    return;
}

static inline void _mov_u64_a_v(uint64_t dest_addr, uint64_t val) {
    *pain64_resolve_addr_U64(dest_addr) = val;
    return;
}


static inline void _mov_u32_r_v(uint64_t *reg, uint32_t val) {
    *reg = val;
    return;
}

static inline void _mov_u32_r_r(uint64_t *dest, uint64_t *src) {
    *dest = *(uint32_t *)src;
    return;
}

static inline void _mov_u32_r_a(uint64_t *reg, uint64_t addr) {
    *reg = *pain64_resolve_addr_U32(addr);
    return;
}

static inline void _mov_u32_a_r(uint64_t dest_addr, uint64_t *reg) {
    *pain64_resolve_addr_U32(dest_addr) = *reg;
    return;
}

static inline void _mov_u32_a_v(uint64_t dest_addr, uint32_t val) {
    *pain64_resolve_addr_U32(dest_addr) = val;
    return;
}


static inline void _mov_u16_r_v(uint64_t *reg, uint16_t val) {
    *reg = val;
    return;
}

static inline void _mov_u16_r_r(uint64_t *dest, uint64_t *src) {
    *dest = *(uint16_t *)src;
    return;
}

static inline void _mov_u16_r_a(uint64_t *reg, uint64_t addr) {
    *reg = *pain64_resolve_addr_U16(addr);
    return;
}

static inline void _mov_u16_a_r(uint64_t dest_addr, uint64_t *reg) {
    *pain64_resolve_addr_U16(dest_addr) = *reg;
    return;
}

static inline void _mov_u16_a_v(uint64_t dest_addr, uint16_t val) {
    *pain64_resolve_addr_U16(dest_addr) = val;
    return;
}


static inline void _mov_u8_r_v(uint64_t *reg, uint8_t val) {
    *reg = val;
    return;
}

static inline void _mov_u8_r_r(uint64_t *dest, uint64_t *src) {
    *dest = *(uint8_t *)src;
    return;
}

static inline void _mov_u8_r_a(uint64_t *reg, uint64_t addr) {
    *reg = *pain64_resolve_addr_U8(addr);
    return;
}

static inline void _mov_u8_a_r(uint64_t dest_addr, uint64_t *reg) {
    *pain64_resolve_addr_U8(dest_addr) = *reg;
    return;
}

static inline void _mov_u8_a_v(uint64_t dest_addr, uint8_t val) {
    *pain64_resolve_addr_U8(dest_addr) = val;
    return;
}

#endif

#ifndef _FOLD_ADD

static inline void _add_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator += *base;
    return;
}

static inline void _add_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator += value;
    return;
}

static inline void _fadd_r_r(float64_t *accumulator, float64_t *base) {
    *accumulator += *base;
    return;
}

static inline void _fadd_r_v(float64_t *accumulator, float64_t value) {
    *accumulator += value;
    return;
}

#endif

#ifndef _FOLD_SUB

static inline void _sub_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator -= *base;
    return;
}

static inline void _sub_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator -= value;
    return;
}

static inline void _fsub_r_r(float64_t *accumulator, float64_t *base) {
    *accumulator -= *base;
    return;
}

static inline void _fsub_r_v(float64_t *accumulator, float64_t value) {
    *accumulator -= value;
    return;
}

#endif

#ifndef _FOLD_MUL

static inline void _mul_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator *= *base;
    return;
}

static inline void _mul_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator *= value;
    return;
}

static inline void _fmul_r_r(float64_t *accumulator, float64_t *base) {
    *accumulator *= *base;
    return;
}

static inline void _fmul_r_v(float64_t *accumulator, float64_t value) {
    *accumulator *= value;
    return;
}

#endif

#ifndef _FOLD_DIV

static inline void _div_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator /= *base;
    return;
}

static inline void _div_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator /= value;
    return;
}

static inline void _div_r_r(float64_t *accumulator, float64_t *base) {
    *accumulator /= *base;
    return;
}

static inline void _div_r_v(float64_t *accumulator, float64_t value) {
    *accumulator /= value;
    return;
}

#endif

#ifndef _FOLD_MOD

static inline void _mod_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator %= *base;
    return;
}

static inline void _mod_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator %= value;
    return;
}

#endif

#ifndef _FOLD_AND

static inline void _and_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator &= *base;
    return;
}

static inline void _and_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator &= value;
    return;
}

#endif

#ifndef _FOLD_OR

static inline void _or_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator |= *base;
    return;
}

static inline void _or_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator |= value;
    return;
}

#endif

#ifndef _FOLD_XOR

static inline void _xor_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator ^= *base;
    return;
}

static inline void _xor_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator ^= value;
    return;
}

#endif

#ifndef _FOLD_LSH

static inline void _lsh_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator <<= *base;
    return;
}

static inline void _lsh_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator <<= value;
    return;
}

#endif

#ifndef _FOLD_RSH

static inline void _rsh_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator >>= *base;
    return;
}

static inline void _rsh_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator >>= value;
    return;
}

#endif

#ifndef _FOLD_NOT

static inline void _not(uint64_t *accumulator) {
    *accumulator = ~(*accumulator);
    return;
}

#endif

#ifndef _FOLD_CMP

static inline void _cmp_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator = *accumulator == *base ? 0 : *accumulator < *base ? 1 : 2;
    return;
}

static inline void _cmp_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator = *accumulator == value ? 0 : *accumulator < value ? 1 : 2;
    return;
}

#endif

#ifndef _FOLD_JMP

static inline void _jmp_r(uint64_t *dest) {
    *IP = *dest;
    return;
}

static inline void _jmp_a(uint64_t *dest) {
    *IP = (uint64_t)dest;
    return;
}

#endif

#ifndef _FOLD_JE

static inline void _je_r(uint64_t *dest) {
    *IP = *R0 == 0 ? *dest : *IP;
    return;
}

static inline void _je_a(uint64_t *dest) {
    *IP = *R0 == 0 ? (uint64_t)dest : *IP;
    return;
}

#endif

#ifndef _FOLD_JNE

static inline void _jne_r(uint64_t *dest) {
    *IP = *R0 != 0 ? *dest : *IP;
    return;
}

static inline void _jne_a(uint64_t *dest) {
    *IP = *R0 != 0 ? (uint64_t)dest : *IP;
    return;
}

#endif

#ifndef _FOLD_PUSH

static inline void _push_r(uint64_t *reg) {
    *pain64_resolve_addr_U64(*SP) = *reg;
    *SP += 8;
    return;
}

static inline void _push_v(uint64_t value) {
    *pain64_resolve_addr_U64(*SP) = value;
    *SP += 8;
    return;
}

static inline void _push_a(uint64_t addr) {
    *pain64_resolve_addr_U64(*SP) = *pain64_resolve_addr_U64(addr);
    *SP += 8;
    return;
}

#endif

#ifndef _FOLD_POP

static inline void _pop_r(uint64_t *reg) {
    *reg = *pain64_resolve_addr_U64(*SP);
    *SP -= 8;
    return;
}

static inline void _pop_a(uint64_t addr) {
    *pain64_resolve_addr_U64(addr) = *pain64_resolve_addr_U64(*SP);
    *SP -= 8;
    return;
}

#endif

#ifndef _FOLD_CALL

static inline void _call_r(uint64_t *reg) {
    _push_r(IP);
    _jmp_r(reg);
    return;
}

static inline void _call_a(uint64_t addr) {
    _push_r(IP);
    _jmp_a(addr);
    return;
}

#endif

#ifndef _FOLD_RET

static inline void _ret(void) {
    _mov_u64_r_r(BP, SP);
    _pop_r(IP);
    return;
}

#endif

#ifndef _FOLD_BREAKPOINT

static inline void _breakpoint(void) {
    printf("--- Breakpoint Reached ---\n");
    printf("R0 = 0x%x\t\tR1 = 0x%x\n", *R0, *R1);
    printf("R2 = 0x%x\t\tR3 = 0x%x\n", *R2, *R3);
    printf("R4 = 0x%x\t\tR5 = 0x%x\n", *R4, *R5);
    printf("R6 = 0x%x\t\tR7 = 0x%x\n", *R6, *R7);
    printf("IP = 0x%x\t\tFG = 0x%x\n", *IP, *FG);
    printf("BP = 0x%x\t\tSP = 0x%x\n", *BP, *SP);
    printf("Press any key to continue execution\n");
    (void)getchar();
    return;
}

#endif

#ifndef _FOLD_OUT

static inline void _out(void) {
    struct pain64_device *device = pain64_resolve_addr_DEVICE(*R7);
    switch (*R7) {
    case 0: // D:NULL
        break; // READONLY
    case 1: // D:STDIO
        putchar(*(char *)R6);
        break;
    case 2: // D:RAND
        break; // READONLY
    case 3: // D:PUTS
        puts((const char *)*R6);
        break;
    default: // D:(custom)
        _call_a(device->out);
        break;
    }
}

#endif

#ifndef _FOLD_IN

static inline void _in(void) {
    struct pain64_device *device = pain64_resolve_addr_DEVICE(*R7);
    switch (*R7) {
    case 0: // D:NULL
        *R6 = 0;
        break;
    case 1: // D:STDIO
        *R6 = getchar();
        break;
    case 2: // D:RAND
        *R6 = rand();
        break;
    case 3: // D:PUTS
        *R6 = UINT64_MAX;
        break; // WRITEONLY
    default: // D:(custom)
        _call_a(device->in);
        break;
    }
}

#endif

#ifndef _FOLD_INC

static inline void _inc(uint64_t *reg) {
    (*reg)++;
    return;
}

#endif

#ifndef _FOLD_DEC

static inline void _dec(uint64_t *reg) {
    (*reg)--;
    return;
}

#endif

static int _junk_counter = 0;

static void _invoke(void) {
    char instruction = *pain64_resolve_addr_U8(*IP);
    (*IP)++;
    switch (instruction) {
    case NOP:
        _nop();
        break;
    case HALT:
        _halt();
        break;

    case FMOV64RR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_f64_r_r(&(fregisters[d0]), &(fregisters[d1]));
        break;
    }
    case FMOV64RV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const float64_t d1 = *pain64_resolve_addr_F64(*IP);
        (*IP) += 8;
        _mov_f64_r_v(&(fregisters[d0]), d1);
        break;
    }
    case FMOV64RA: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _mov_f64_r_a(&(fregisters[d0]), d1);
        break;
    }
    case FMOV64AR: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_f64_a_r(d0, &(fregisters[d1]));
        break;
    }
    case FMOV64AV: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        const float64_t d1 = *pain64_resolve_addr_F64(*IP);
        (*IP) += 8;
        _mov_f64_a_v(d0, d1);
        break;
    }
    case FMOV32RR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_f32_r_r(&(fregisters[d0]), &(fregisters[d1]));
        break;
    }
    case FMOV32RV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const float32_t d1 = *pain64_resolve_addr_F32(*IP);
        (*IP) += 4;
        _mov_f32_r_v(&(fregisters[d0]), d1);
        break;
    }
    case FMOV32RA: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _mov_f32_r_a(&(fregisters[d0]), d1);
        break;
    }
    case FMOV32AR: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_f32_a_r(d0, &(fregisters[d1]));
        break;
    }
    case FMOV32AV: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        const float32_t d1 = *pain64_resolve_addr_F32(*IP);
        (*IP) += 4;
        _mov_f32_a_v(d0, d1);
        break;
    }

    case MOV64RR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_u64_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case MOV64RV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _mov_u64_r_v(&(registers[d0]), d1);
        break;
    }
    case MOV64RA: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _mov_u64_r_a(&(registers[d0]), d1);
        break;
    }
    case MOV64AR: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_u64_a_r(d0, &(registers[d1]));
        break;
    }
    case MOV64AV: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _mov_u64_a_v(d0, d1);
        break;
    }
    case MOV32RR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_u32_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case MOV32RV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint32_t d1 = *pain64_resolve_addr_U32(*IP);
        (*IP) += 4;
        _mov_u32_r_v(&(registers[d0]), d1);
        break;
    }
    case MOV32RA: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _mov_u32_r_a(&(registers[d0]), d1);
        break;
    }
    case MOV32AR: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_u32_a_r(d0, &(registers[d1]));
        break;
    }
    case MOV32AV: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        const uint32_t d1 = *pain64_resolve_addr_U32(*IP);
        (*IP) += 4;
        _mov_u32_a_v(d0, d1);
        break;
    }
    case MOV16RR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_u16_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case MOV16RV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint16_t d1 = *pain64_resolve_addr_U16(*IP);
        (*IP) += 2;
        _mov_u16_r_v(&(registers[d0]), d1);
        break;
    }
    case MOV16RA: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _mov_u16_r_a(&(registers[d0]), d1);
        break;
    }
    case MOV16AR: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_u64_a_r(d0, &(registers[d1]));
        break;
    }
    case MOV16AV: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        const uint16_t d1 = *pain64_resolve_addr_U16(*IP);
        (*IP) += 2;
        _mov_u16_a_v(d0, d1);
        break;
    }
    case MOV8RR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_u8_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case MOV8RV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_u8_r_v(&(registers[d0]), d1);
        break;
    }
    case MOV8RA: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _mov_u8_r_a(&(registers[d0]), d1);
        break;
    }
    case MOV8AR: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_u8_a_r(d0, &(registers[d1]));
        break;
    }
    case MOV8AV: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mov_u8_a_v(d0, d1);
        break;
    }
    case ADDRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _add_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case ADDRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _add_r_v(&(registers[d0]), d1);
        break;
    }

    case FADDRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _fadd_r_r(&(fregisters[d0]), &(fregisters[d1]));
        break;
    }
    case FADDRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const float64_t d1 = *pain64_resolve_addr_F64(*IP);
        (*IP) += 8;
        _fadd_r_v(&(fregisters[d0]), d1);
        break;
    }
    case FSUBRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _fsub_r_r(&(fregisters[d0]), &(fregisters[d1]));
        break;
    }
    case FSUBRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const float64_t d1 = *pain64_resolve_addr_F64(*IP);
        (*IP) += 8;
        _fsub_r_v(&(fregisters[d0]), d1);
        break;
    }
    case FMULRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _fmul_r_r(&(fregisters[d0]), &(fregisters[d1]));
        break;
    }
    case FMULRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const float64_t d1 = *pain64_resolve_addr_F64(*IP);
        (*IP) += 8;
        _fmul_r_v(&(fregisters[d0]), d1);
        break;
    }
    case FDIVRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _fdiv_r_r(&(fregisters[d0]), &(fregisters[d1]));
        break;
    }
    case FDIVRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const float64_t d1 = *pain64_resolve_addr_F64(*IP);
        (*IP) += 8;
        _fdiv_r_v(&(fregisters[d0]), d1);
        break;
    }

    case SUBRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _sub_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case SUBRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _sub_r_v(&(registers[d0]), d1);
        break;
    }
    case MULRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mul_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case MULRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _mul_r_v(&(registers[d0]), d1);
        break;
    }
    case DIVRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _div_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case DIVRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _div_r_v(&(registers[d0]), d1);
        break;
    }
    case MODRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _mod_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case MODRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _mod_r_v(&(registers[d0]), d1);
        break;
    }
    case ANDRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _and_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case ANDRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _and_r_v(&(registers[d0]), d1);
        break;
    }
    case ORRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _or_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case ORRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _or_r_v(&(registers[d0]), d1);
        break;
    }
    case XORRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _xor_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case XORRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _xor_r_v(&(registers[d0]), d1);
        break;
    }
    case LSHRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _lsh_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case LSHRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        *(IP) += 8;
        _lsh_r_v(&(registers[d0]), d1);
        break;
    }
    case RSHRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _rsh_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case RSHRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        *(IP) += 8;
        _rsh_r_v(&(registers[d0]), d1);
        break;
    }
    case NOT: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _not(&(registers[d0]));
        break;
    }
    case CMPRR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint8_t d1 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _cmp_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case CMPRV: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _cmp_r_v(&(registers[d0]), d1);
        break;
    }
    case JMPR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _jmp_r(&(registers[d0]));
        break;
    }
    case JMPA: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _jmp_a(d0);
        break;
    }
    case JER: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _je_r(&(registers[d0]));
        break;
    }
    case JEA: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _je_a(d0);
        break;
    }
    case JNER: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _jne_r(&(registers[d0]));
        break;
    }
    case JNEA: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _jne_a(d0);
        break;
    }
    case PUSHR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _push_r(&(registers[d0]));
        break;
    }
    case PUSHV: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _push_v(d0);
        break;
    }
    case PUSHA: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _push_a(d0);
        break;
    }
    case POPR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _pop_r(&(registers[d0]));
        break;
    }
    case POPA: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _pop_a(d0);
        break;
    }
    case CALLR: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _call_r(&(registers[d0]));
        break;
    }
    case CALLA: {
        const uint64_t d0 = *pain64_resolve_addr_U64(*IP);
        (*IP) += 8;
        _call_a(d0);
        break;
    }
    case BREAKPOINT: {
        _breakpoint();
        break;
    }
    case OUT:
        _out();
        break;
    case IN:
        _in();
        break;
    case INC: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _inc(&(registers[d0]));
        break;
    }
    case DEC: {
        const uint8_t d0 = *pain64_resolve_addr_U8(*IP);
        (*IP)++;
        _dec(&(registers[d0]));
        break;
    }
    case RET:
        _ret();
        break;
    default:
        printf("Unknown junk instruction %d\n", instruction);
        _junk_counter++;
        if (_junk_counter == 3) {
            printf("Fatal number of junk instructions reached.\n");
            printf("Shutting down..\n");
            pain64_close_mem();
            exit(-1);
        }
        printf("Note: After three junk instructions executed, PAIN64 crashes.\n");
        break;
    }
}

void pain64_start(char *program, size_t program_size) {
    memset(registers, 0, sizeof(registers));
    pain64_open_mem();
    *IP = 0x7C00;
    *BP = 0x0040;
    *SP = 0x0040;
    pain64_load_program(0x7C00, program, program_size);
    while (!halted) {
        _invoke();
    }
    pain64_close_mem();
    return;
}