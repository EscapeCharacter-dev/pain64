# Pain64
A 64-bit little-endian ISA written in C.
## Syntax
The PAIN64 syntax goes like so:  
```
INSTRUCTION     DEST, SOURCE
```  
For example, MOV64RA:  
```
MOV64RA         R0, [0x7C50]
```
## Instructions
| Instruction Name |Instruction Opcode(hex)| Purpose                                                            |
| :--------------- | :-------------------: | :----------------------------------------------------------------- |
| NOP              | 0                     | (None)                                                             |
| HALT             | 1                     | Stops the emulator/board.                                          |
| MOV64RR          | 2                     | Moves an unsigned 64-bit value from a register to another.         |
| MOV64RV          | 3                     | Moves an unsigned 64-bit value to a register.                      |
| MOV64RA          | 4                     | Moves an unsigned 64-bit value stored in memory to a register.     |
| MOV64AR          | 5                     | Moves an unsigned 64-bit value from a register to memory.          |
| MOV64AV          | 6                     | Moves an unsigned 64-bit value to memory.                          |
| MOV32RR          | 7                     | Moves an unsigned 32-bit value from a register to another.         |
| MOV32RV          | 8                     | Moves an unsigned 32-bit value to a register.                      |
| MOV32RA          | 9                     | Moves an unsigned 32-bit value stored in memory to a register.     |
| MOV32AR          | A                     | Moves an unsigned 32-bit value from a register to memory.          |
| MOV32AV          | B                    | Moves an unsigned 32-bit value to memory.                           |
| MOV16RR          | C                     | Moves an unsigned 16-bit value from a register to another.         |
| MOV16RV          | D                     | Moves an unsigned 16-bit value to a register.                      |
| MOV16RA          | E                     | Moves an unsigned 16-bit value stored in memory to a register.     |
| MOV16AR          | F                     | Moves an unsigned 16-bit value from a register to memory.          |
| MOV16AV          | 10                    | Moves an unsigned 16-bit value to memory.                          |
| MOV8RR           | 11                    | Moves an unsigned 8-bit value from a register to another.          |
| MOV8RV           | 12                    | Moves an unsigned 8-bit value to a register.                       |
| MOV8RA           | 13                    | Moves an unsigned 8-bit value stored in memory to a register.      |
| MOV8AR           | 14                    | Moves an unsigned 8-bit value from a register to memory.           |
| MOV8AV           | 15                    | Moves an unsigned 8-bit value to memory.                           |
| FMOV64RR         | 16                    | Moves a floating 64-bit value from a register to another.          |
| FMOV64RV         | 17                    | Moves a floating 64-bit value to a register.                       |
| FMOV64RA         | 18                    | Moves a floating 64-bit value stored in memory to a register.      |
| FMOV64AR         | 19                    | Moves a floating 64-bit value from a register to memory.           |
| FMOV64AV         | 1A                    | Moves a floating 64-bit value to memory.                           |
| FMOV32RR         | 1B                    | Moves a floating 32-bit value from a register to another.          |
| FMOV32RV         | 1C                    | Moves a floating 32-bit value to a register.                       |
| FMOV32RA         | 1D                    | Moves a floating 32-bit value stored in memory to a register.      |
| FMOV32AR         | 1E                    | Moves a floating 32-bit value from a register to memory.           |
| FMOV32AV         | 1F                    | Moves a floating 32-bit value to memory.                           |
| ADDRR            | 20                    | Adds two registers together.                                       |
| ADDRV            | 21                    | Adds a register and an unsigned 64-bit value.                      |
| SUBRR            | 22                    | Subtracts two registers together.                                  |
| SUBRV            | 23                    | Subtracts a register and an unsigned 64-bit value.                 |
| MULRR            | 24                    | Multiplies two registers together.                                 |
| MULRV            | 25                    | Multiplies a register and an unsigned 64-bit value.                |
| DIVRR            | 26                    | Divides two registers together.                                    |
| DIVRV            | 27                    | Divides a register and an unsigned 64-bit value. (remainder)       |
| MODRR            | 28                    | Divides two registers together. (remainder)                        |
| MODRV            | 29                    | Divides a register and an unsigned 64-bit value.                   |
| ANDRR            | 2A                    | Performs an AND gate to two registers.                             |
| ANDRV            | 2B                    | Performs an AND gate to a register and an unsigned 64-bit value.   |
| ORRR             | 2C                    | Performs an OR gate to two registers.                              |
| ORRV             | 2D                    | Performs an OR gate to a register and an unsigned 64-bit value.    |
| XORRR            | 2E                    | Performs a XOR gate to two registers.                              |
| XORRV            | 2F                    | Performs a XOR gate to a register and an unsigned 64-bit value.    |
| LSHRR            | 30                    | Performs a binary left shift with two registers.                   |
| LSHRV            | 31                    | Performs a binary left shift with a register and an unsigned 64-bit value. |
| RSHRR            | 32                    | Performs a binary right shift with two registers.                  |
| RSHRV            | 33                    | Performs a binary right shift with a register and an unsigned 64-bit value. |
| NOT              | 34                    | Performs a binary not on a register.                               |
| CMPRR            | 35                    | Compares two registers. If A < B then 1, if A == B then 2, else 0. |
| CMPRV            | 36                    | Compares a register and a value. Check table entry for CMPRR.      |
| JMPR             | 37                    | Jumps at an address in a register.                                 |
| JMPA             | 38                    | Jumps to an address.                                               |
| JER              | 39                    | Jumps at an address in a register if R0 == 0.                      |
| JEA              | 3A                    | Jumps to an address if R0 == 0.                                    |
| JNER             | 3B                    | Jumps at an address in a register if R0 != 0.                      |
| JNEA             | 3C                    | Jumps to an address if R0 != 0.                                    |
| PUSHR            | 3D                    | Push a value in a register to the stack.                           |
| PUSHV            | 3E                    | Push a value to the stack.                                         |
| PUSHA            | 3F                    | Push a value in memory to the stack.                               |
| POPR             | 40                    | Pops a value from the stack into a register.                       |
| POPA             | 41                    | Pops a value from the stack into memory.                           |
| CALLR            | 42                    | Pushes the address for the next instruction, then jumps into the address stored in a register. |
| CALLA            | 43                    | Same as CALLR, but the address is fed as an instruction operand.   |
| RET              | 44                    | Pops the address on the stack, then jumps to this address.         |
| BREAKPOINT       | 45                    | Causes a breakpoint, displays registers and waits for user input.  |
| OUT              | 46                    | Sends data to a device port.                                       |
| IN               | 47                    | Polls data from a device port.                                     |
| INC              | 48                    | Increments a register.                                             |
| DEC              | 49                    | Decrements a register.                                             |
| FADDRR           | 4A                    | Adds two registers together.                                       |
| FADDRV           | 4B                    | Adds a register and a floating 64-bit value.                       |
| FSUBRR           | 4C                    | Subtracts two registers together.                                  |
| FSUBRV           | 4D                    | Subtracts a register and a floating 64-bit value.                  |
| FMULRR           | 4E                    | Multiplies two registers together.                                 |
| FMULRV           | 4F                    | Multiplies a register and a floating 64-bit value.                 |
| FDIVRR           | 50                    | Divides two registers together.                                    |
| FDIVRV           | 51                    | Divides a register and a floating 64-bit value.                    |