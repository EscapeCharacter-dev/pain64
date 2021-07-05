# Pain64
A 64-bit little-endian ISA written in C.
## Syntax
The PAIN64 syntax goes like so:  
```
INSTRUCTION     DEST, SOURCE
```  
For example, MOVU64RA:  
```
MOVU64RA        R0, [0x7C50]
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
| MOV32AV          | B                    | Moves an unsigned 32-bit value to memory.                          |
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
| ADDRR            | 16                    | Adds two registers together.                                       |
| ADDRV            | 17                    | Adds a register and an unsigned 64-bit value.                      |
| SUBRR            | 18                    | Subtracts two registers together.                                  |
| SUBRV            | 19                    | Subtracts a register and an unsigned 64-bit value.                 |
| MULRR            | 1A                    | Multiplies two registers together.                                 |
| MULRV            | 1B                    | Multiplies a register and an unsigned 64-bit value.                |
| DIVRR            | 1C                    | Divides two registers together.                                    |
| DIVRV            | 1D                    | Divides a register and an unsigned 64-bit value. (remainder)       |
| MODRR            | 1E                    | Divides two registers together. (remainder)                        |
| MODRV            | 1F                    | Divides a register and an unsigned 64-bit value. (remainder)       |
| ANDRR            | 20                    | Performs an AND gate to two registers.                             |
| ANDRV            | 21                    | Performs an AND gate to a register and an unsigned 64-bit value.   |
| ORRR             | 22                    | Performs an OR gate to two registers.                              |
| ORRV             | 23                    | Performs an OR gate to a register and an unsigned 64-bit value.    |
| XORRR            | 24                    | Performs a XOR gate to two registers.                              |
| XORRV            | 25                    | Performs a XOR gate to a register and an unsigned 64-bit value.    |
| LSHRR            | 26                    | Performs a binary left shift with two registers.                   |
| LSHRV            | 27                    | Performs a binary left shift with a register and an unsigned 64-bit value. |
| RSHRR            | 28                    | Performs a binary right shift with two registers.                  |
| RSHRV            | 29                    | Performs a binary right shift with a register and an unsigned 64-bit value. |
| NOT              | 2A                    | Performs a binary not on a register.                               |
| CMPRR            | 2B                    | Compares two registers. If A < B then 1, if A == B then 2, else 0. |
| CMPRV            | 2C                    | Compares a register and a value. Check table entry for CMPRR.      |
| JMPR             | 2D                    | Jumps at an address in a register.                                 |
| JMPA             | 2E                    | Jumps to an address.                                               |
| JER              | 2F                    | Jumps at an address in a register if R0 == 0.                      |
| JEA              | 30                    | Jumps to an address if R0 == 0.                                    |
| JNER             | 31                    | Jumps at an address in a register if R0 != 0.                      |
| JNEA             | 32                    | Jumps to an address if R0 != 0.                                    |
| PUSHR            | 33                    | Push a value in a register to the stack.                           |
| PUSHV            | 34                    | Push a value to the stack.                                         |
| PUSHA            | 35                    | Push a value in memory to the stack.                               |
| POPR             | 36                    | Pops a value from the stack into a register.                       |
| POPA             | 37                    | Pops a value from the stack into memory.                           |
| CALLR            | 38                    | Pushes the address for the next instruction, then jumps into the address stored in a register. |
| CALLA            | 39                    | Same as CALLR, but the address is fed as an instruction operand.   |
| RET              | 3A                    | Pops the address on the stack, then jumps to this address.         |
| BREAKPOINT       | 3B                    | Causes a breakpoint, displays registers and waits for user input.  |
| OUT              | 3C                    | Sends data to a device port.                                       |
| IN               | 3D                    | Polls data from a device port.                                     |
| INC              | 3E                    | Increments a register.                                             |
| DEC              | 3F                    | Decrements a register.                                             |