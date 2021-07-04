#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "pain64.h"

// 16 registers ought to be enough
static uint64_t	registers[16];

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


static int halted = 0;

#ifndef _FOLD_HLT

static void _halt(void) {
    halted = 1;
    return;
}

#endif

#ifndef _FOLD_NOP

static void _nop(void) {
    return;
}

#endif

#ifndef _FOLD_MOV

static void _mov_r_v(uint64_t *reg, uint64_t val) {
    *reg = val;
    return;
}

static void _mov_r_r(uint64_t *dest, uint64_t *src) {
    *dest = *src;
    return;
}

static void _mov_r_a(uint64_t *reg, uint64_t addr) {
    *reg = *pain64_resolve_addr(addr);
    return;
}

static void _mov_a_r(uint64_t *dest_addr, uint64_t *reg) {
    *pain64_resolve_addr(dest_addr) = *reg;
    return;
}

static void _mov_a_v(uint64_t *dest_addr, uint64_t val) {
    *pain64_resolve_addr(dest_addr) = val;
    return;
}

#endif

#ifndef _FOLD_ADD

static void _add_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator += *base;
    return;
}

static void _add_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator += value;
    return;
}

#endif

#ifndef _FOLD_SUB

static void _sub_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator -= *base;
    return;
}

static void _sub_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator -= value;
    return;
}

#endif

#ifndef _FOLD_MUL

static void _mul_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator *= *base;
    return;
}

static void _mul_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator *= value;
    return;
}

#endif

#ifndef _FOLD_DIV

static void _div_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator /= *base;
    return;
}

static void _div_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator /= value;
    return;
}

#endif

#ifndef _FOLD_MOD

static void _mod_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator %= *base;
    return;
}

static void _mod_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator %= value;
    return;
}

#endif

#ifndef _FOLD_AND

static void _and_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator &= *base;
    return;
}

static void _and_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator &= value;
    return;
}

#endif

#ifndef _FOLD_OR

static void _or_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator |= *base;
    return;
}

static void _or_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator |= value;
    return;
}

#endif

#ifndef _FOLD_XOR

static void _xor_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator ^= *base;
    return;
}

static void _xor_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator ^= value;
    return;
}

#endif

#ifndef _FOLD_NOT

static void _not(uint64_t *accumulator) {
    *accumulator = ~(*accumulator);
    return;
}

#endif

#ifndef _FOLD_CMP

static void _cmp_r_r(uint64_t *accumulator, uint64_t *base) {
    *accumulator = *accumulator == *base ? 0 : *accumulator < *base ? 1 : 2;
    return;
}

static void _cmp_r_v(uint64_t *accumulator, uint64_t value) {
    *accumulator = *accumulator == value ? 0 : *accumulator < value ? 1 : 2;
    return;
}

#endif

#ifndef _FOLD_JMP

static void _jmp_r(uint64_t *dest) {
    *IP = *dest;
    return;
}

static void _jmp_a(uint64_t *dest) {
    *IP = (uint64_t)dest;
    return;
}

#endif

#ifndef _FOLD_JE

static void _je_r(uint64_t *dest) {
    *IP = *R0 == 0 ? *dest : *IP;
    return;
}

static void _je_a(uint64_t *dest) {
    *IP = *R0 == 0 ? (uint64_t)dest : *IP;
    return;
}

#endif

#ifndef _FOLD_JNE

static void _jne_r(uint64_t *dest) {
    *IP = *R0 != 0 ? *dest : *IP;
    return;
}

static void _jne_a(uint64_t *dest) {
    *IP = *R0 != 0 ? (uint64_t)dest : *IP;
    return;
}

#endif

#ifndef _FOLD_PUSH

static void _push_r(uint64_t *reg) {
    *pain64_resolve_addr(*SP) = *reg;
    *SP += 8;
    return;
}

static void _push_v(uint64_t value) {
    *pain64_resolve_addr(*SP) = value;
    *SP += 8;
    return;
}

static void _push_a(uint64_t addr) {
    *pain64_resolve_addr(*SP) = *pain64_resolve_addr(addr);
    *SP += 8;
    return;
}

#endif

#ifndef _FOLD_POP

static void _pop_r(uint64_t *reg) {
    *reg = *pain64_resolve_addr(*SP);
    *SP -= 8;
    return;
}

static void _pop_a(uint64_t addr) {
    *pain64_resolve_addr(addr) = *pain64_resolve_addr(*SP);
    *SP -= 8;
    return;
}

#endif

#ifndef _FOLD_CALL

static void _call_r(uint64_t *reg) {
    _push_r(IP);
    _jmp_r(reg);
    return;
}

static void _call_a(uint64_t addr) {
    _push_r(IP);
    _jmp_a(addr);
    return;
}

#endif

#ifndef _FOLD_RET

static void _ret(void) {
    _pop_r(IP);
    _mov_r_r(BP, SP);
    return;
}

#endif

static void _invoke(void) {
    char instruction = *(char *)pain64_resolve_addr(*IP);
    (*IP)++;
    printf("Instruction: %d\n", instruction);
    switch (instruction) {
    case NOP:
        _nop();
        break;
    case HALT:
        _halt();
        break;
    case MOVRR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint8_t d1 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _mov_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case MOVRV: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _mov_r_v(&(registers[d0]), d1);
        break;
    }
    case MOVRA: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _mov_r_a(&(registers[d0]), d1);
        break;
    }
    case MOVAR: {
        const uint64_t d0 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        const uint8_t d1 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _mov_a_r(d0, &(registers[d1]));
        break;
    }
    case MOVAV: {
        const uint64_t d0 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        const uint64_t d1 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _mov_a_v(d0, d1);
        break;
    }
    case ADDRR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint8_t d1 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _add_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case ADDRV: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _add_r_v(&(registers[d0]), d1);
        break;
    }
    case SUBRR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint8_t d1 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _sub_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case SUBRV: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _sub_r_v(&(registers[d0]), d1);
        break;
    }
    case MULRR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint8_t d1 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _mul_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case MULRV: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _mul_r_v(&(registers[d0]), d1);
        break;
    }
    case DIVRR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint8_t d1 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _div_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case DIVRV: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _div_r_v(&(registers[d0]), d1);
        break;
    }
    case MODRR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint8_t d1 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _mod_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case MODRV: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _mod_r_v(&(registers[d0]), d1);
        break;
    }
    case ANDRR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint8_t d1 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _and_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case ANDRV: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _and_r_v(&(registers[d0]), d1);
        break;
    }
    case ORRR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint8_t d1 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _or_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case ORRV: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _or_r_v(&(registers[d0]), d1);
        break;
    }
    case XORRR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint8_t d1 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _xor_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case XORRV: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _xor_r_v(&(registers[d0]), d1);
        break;
    }
    case NOT: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _not(&(registers[d0]));
        break;
    }
    case CMPRR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint8_t d1 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _cmp_r_r(&(registers[d0]), &(registers[d1]));
        break;
    }
    case CMPRV: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        const uint64_t d1 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _cmp_r_v(&(registers[d0]), d1);
        break;
    }
    case JMPR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _jmp_r(&(registers[d0]));
        break;
    }
    case JMPA: {
        const uint64_t d0 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _jmp_a(d0);
        break;
    }
    case JER: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _je_r(&(registers[d0]));
        break;
    }
    case JEA: {
        const uint64_t d0 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _je_a(d0);
        break;
    }
    case JNER: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _jne_r(&(registers[d0]));
        break;
    }
    case JNEA: {
        const uint64_t d0 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _jne_a(d0);
        break;
    }
    case PUSHR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _push_r(&(registers[d0]));
        break;
    }
    case PUSHV: {
        const uint64_t d0 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _push_v(d0);
        break;
    }
    case PUSHA: {
        const uint64_t d0 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _push_a(d0);
        break;
    }
    case POPR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _pop_r(&(registers[d0]));
        break;
    }
    case POPA: {
        const uint64_t d0 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _pop_a(d0);
        break;
    }
    case CALLR: {
        const uint8_t d0 = *(char *)pain64_resolve_addr(*IP);
        (*IP)++;
        _call_r(&(registers[d0]));
        break;
    }
    case CALLA: {
        const uint64_t d0 = *pain64_resolve_addr(*IP);
        (*IP) += 8;
        _call_a(d0);
        break;
    }
    case RET:
        _ret();
        break;
    }
}

static void _on_instruction(void) {
    printf("R0 = 0x%x\t\tR1 = 0x%x\n", *R0, *R1);
    printf("R2 = 0x%x\t\tR3 = 0x%x\n", *R2, *R3);
    printf("R4 = 0x%x\t\tR5 = 0x%x\n", *R4, *R5);
    printf("R6 = 0x%x\t\tR7 = 0x%x\n", *R6, *R7);
    printf("IP = 0x%x\t\tFG = 0x%x\n", *IP, *FG);
    printf("BP = 0x%x\t\tSP = 0x%x\n", *BP, *SP);
    _invoke();
    getchar();
    return;
}

void pain64_start(char *program, size_t program_size) {
    memset(registers, 0, sizeof(registers));
    pain64_open_mem();
    *IP = 0x7C00;
    pain64_load_program(0x7C00, program, program_size);
    while (!halted) _on_instruction();
    pain64_close_mem();
    return;
}