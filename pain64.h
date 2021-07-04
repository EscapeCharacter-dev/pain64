#ifndef PAIN64_H
#define PAIN64_H

#include <stdint.h>

enum pain64_instruction {
    NOP,
    HALT,

    MOVU64RR,
    MOVU64RV,
    MOVU64RA,
    MOVU64AR,
    MOVU64AV,
    MOVI64RR,
    MOVI64RV,
    MOVI64RA,
    MOVI64AR,
    MOVI64AV,

    MOVU32RR,
    MOVU32RV,
    MOVU32RA,
    MOVU32AR,
    MOVU32AV,
    MOVI32RR,
    MOVI32RV,
    MOVI32RA,
    MOVI32AR,
    MOVI32AV,

    MOVU16RR,
    MOVU16RV,
    MOVU16RA,
    MOVU16AR,
    MOVU16AV,
    MOVI16RR,
    MOVI16RV,
    MOVI16RA,
    MOVI16AR,
    MOVI16AV,

    MOVU8RR,
    MOVU8RV,
    MOVU8RA,
    MOVU8AR,
    MOVU8AV,
    MOVI8RR,
    MOVI8RV,
    MOVI8RA,
    MOVI8AR,
    MOVI8AV,

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
    
    LSHRR,
    LSHRV,
    RSHRR,
    RSHRV,

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
    BREAKPOINT,
};

void pain64_open_mem(void);
void pain64_close_mem(void);
uint64_t *pain64_resolve_addr_U64(uint64_t address);
int64_t *pain64_resolve_addr_I64(uint64_t address);
uint32_t *pain64_resolve_addr_U32(uint64_t address);
int32_t *pain64_resolve_addr_I32(uint64_t address);
uint16_t *pain64_resolve_addr_U16(uint64_t address);
int16_t *pain64_resolve_addr_I16(uint64_t address);
uint8_t *pain64_resolve_addr_U8(uint64_t address);
int8_t *pain64_resolve_addr_I8(uint64_t address);
void pain64_load_program(uint64_t offset, uint8_t *code, size_t code_size);
void pain64_start(char *program, size_t program_size);

#endif