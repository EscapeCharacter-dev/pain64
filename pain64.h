#ifndef PAIN64_H
#define PAIN64_H

#include <stdint.h>

enum pain64_instruction {
    NOP,
    HALT,

    MOVRR,
    MOVRV,
    MOVRA,
    MOVAR,
    MOVAV,

    ADDRR,
    ADDRV,

    SUBRR,
    SUBRV,

    MULRR,
    MULRV,

    DIVRR,
    DIVRV,

    MODRR,
    MODRV,

    ANDRR,
    ANDRV,

    ORRR,
    ORRV,

    XORRR,
    XORRV,

    NOT,

    CMPRR,
    CMPRV,

    JMPR,
    JMPA,
    JER,
    JEA,
    JNER,
    JNEA,

    PUSHR,
    PUSHV,
    PUSHA,

    POPR,
    POPA,

    CALLR,
    CALLA,

    RET,
};

void pain64_open_mem(void);
void pain64_close_mem(void);
uint64_t *pain64_resolve_addr(uint64_t address);
void pain64_load_program(uint64_t offset, uint8_t *code, size_t code_size);
void pain64_start(char *program, size_t program_size);

#endif