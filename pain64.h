#ifndef PAIN64_H
#define PAIN64_H

#include <stdint.h>

struct pain64_device {
    uint64_t    out;
    uint64_t    in;
};

enum pain64_instruction {
    NOP,
    HALT,

    MOV64RR,
    MOV64RV,
    MOV64RA,
    MOV64AR,
    MOV64AV,

    MOV32RR,
    MOV32RV,
    MOV32RA,
    MOV32AR,
    MOV32AV,

    MOV16RR,
    MOV16RV,
    MOV16RA,
    MOV16AR,
    MOV16AV,

    MOV8RR,
    MOV8RV,
    MOV8RA,
    MOV8AR,
    MOV8AV,

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

    OUT,
    IN,

    INC,
    DEC,
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
struct pain64_device *pain64_resolve_addr_DEVICE(uint64_t address);
void pain64_load_program(uint64_t offset, uint8_t *code, size_t code_size);
void pain64_start(char *program, size_t program_size);

#endif