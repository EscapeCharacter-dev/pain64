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
| MOVU64RR         | 2                     | Moves an unsigned 64-bit value from a register to another.         |
| MOVU64RV         | 3                     | Moves an unsigned 64-bit value to a register.                      |
| MOVU64RA         | 4                     | Moves an unsigned 64-bit value stored in memory to a register.     |
| MOVU64AR         | 5                     | Moves an unsigned 64-bit value from a register to memory.          |
| MOVU64AV         | 6                     | Moves an unsigned 64-bit value to memory.                          |
| MOVI64RR         | 7                     | Moves an signed 64-bit value from a register to another.           |
| MOVI64RV         | 8                     | Moves an signed 64-bit value to a register.                        |
| MOVI64RA         | 9                     | Moves an signed 64-bit value stored in memory to a register.       |
| MOVI64AR         | A                     | Moves an signed 64-bit value from a register to memory.            |
| MOVI64AV         | B                     | Moves an signed 64-bit value to memory.                            |
| MOVU32RR         | C                     | Moves an unsigned 32-bit value from a register to another.         |
| MOVU32RV         | D                     | Moves an unsigned 32-bit value to a register.                      |
| MOVU32RA         | E                     | Moves an unsigned 32-bit value stored in memory to a register.     |
| MOVU32AR         | F                     | Moves an unsigned 32-bit value from a register to memory.          |
| MOVU32AV         | 10                    | Moves an unsigned 32-bit value to memory.                          |
| MOVI32RR         | 11                    | Moves an signed 32-bit value from a register to another.           |
| MOVI32RV         | 12                    | Moves an signed 32-bit value to a register.                        |
| MOVI32RA         | 13                    | Moves an signed 32-bit value stored in memory to a register.       |
| MOVI32AR         | 14                    | Moves an signed 32-bit value from a register to memory.            |
| MOVI32AV         | 15                    | Moves an signed 32-bit value to memory.                            |
| MOVU16RR         | 16                    | Moves an unsigned 16-bit value from a register to another.         |
| MOVU16RV         | 17                    | Moves an unsigned 16-bit value to a register.                      |
| MOVU16RA         | 18                    | Moves an unsigned 16-bit value stored in memory to a register.     |
| MOVU16AR         | 19                    | Moves an unsigned 16-bit value from a register to memory.          |
| MOVU16AV         | 1A                    | Moves an unsigned 16-bit value to memory.                          |
| MOVI16RR         | 1B                    | Moves an signed 16-bit value from a register to another.           |
| MOVI16RV         | 1C                    | Moves an signed 16-bit value to a register.                        |
| MOVI16RA         | 1D                    | Moves an signed 16-bit value stored in memory to a register.       |
| MOVI16AR         | 1E                    | Moves an signed 16-bit value from a register to memory.            |
| MOVI16AV         | 1F                    | Moves an signed 16-bit value to memory.                            |
| MOVU8RR          | 20                    | Moves an unsigned 8-bit value from a register to another.          |
| MOVU8RV          | 21                    | Moves an unsigned 8-bit value to a register.                       |
| MOVU8RA          | 22                    | Moves an unsigned 8-bit value stored in memory to a register.      |
| MOVU8AR          | 23                    | Moves an unsigned 8-bit value from a register to memory.           |
| MOVU8AV          | 24                    | Moves an unsigned 8-bit value to memory.                           |
| MOVI8RR          | 25                    | Moves an signed 8-bit value from a register to another.            |
| MOVI8RV          | 26                    | Moves an signed 8-bit value to a register.                         |
| MOVI8RA          | 27                    | Moves an signed 8-bit value stored in memory to a register.        |
| MOVI8AR          | 28                    | Moves an signed 8-bit value from a register to memory.             |
| MOVI8AV          | 29                    | Moves an signed 8-bit value to memory.                             |
| ADDRR            | 2A                    | Adds two registers together.                                       |
| ADDRV            | 2B                    | Adds a register and an unsigned 64-bit value.                      |
| SUBRR            | 2C                    | Subtracts two registers together.                                  |
| SUBRV            | 2D                    | Subtracts a register and an unsigned 64-bit value.                 |
| MULRR            | 2E                    | Multiplies two registers together.                                 |
| MULRV            | 2F                    | Multiplies a register and an unsigned 64-bit value.                |
| DIVRR            | 30                    | Divides two registers together.                                    |
| DIVRV            | 31                    | Divides a register and an unsigned 64-bit value. (remainder)       |
| MODRR            | 32                    | Divides two registers together. (remainder)                        |
| MODRV            | 33                    | Divides a register and an unsigned 64-bit value. (remainder)       |
| ANDRR            | 34                    | Performs an AND gate to two registers.                             |
| ANDRV            | 35                    | Performs an AND gate to a register and an unsigned 64-bit value.   |
| ORRR             | 36                    | Performs an OR gate to two registers.                              |
| ORRV             | 37                    | Performs an OR gate to a register and an unsigned 64-bit value.    |
| XORRR            | 38                    | Performs a XOR gate to two registers.                              |
| XORRV            | 39                    | Performs a XOR gate to a register and an unsigned 64-bit value.    |
| LSHRR            | 34                    | Performs a binary left shift with two registers.                   |
| LSHRV            | 35                    | Performs a binary left shift with a register and an unsigned 64-bit value. |
| RSHRR            | 36                    | Performs a binary right shift with two registers.                  |
| RSHRV            | 37                    | Performs a binary right shift with a register and an unsigned 64-bit value. |
| NOT              | 38                    | Performs a binary not on a register.                               |
| CMPRR            | 39                    | Compares two registers. If A < B then 1, if A == B then 2, else 0. |
| CMPRV            | 3A                    | Compares a register and a value. Check table entry for CMPRR.      |
| JMPR             | 3B                    | Jumps at an address in a register.                                 |
| JMPA             | 3C                    | Jumps to an address.                                               |
| JER              | 3D                    | Jumps at an address in a register if R0 == 0.                      |
| JEA              | 3E                    | Jumps to an address if R0 == 0.                                    |
| JNER             | 3F                    | Jumps at an address in a register if R0 != 0.                      |
| JNEA             | 40                    | Jumps to an address if R0 != 0.                                    |
| PUSHR            | 41                    | Push a value in a register to the stack.                           |
| PUSHV            | 42                    | Push a value to the stack.                                         |
| PUSHA            | 43                    | Push a value in memory to the stack.                               |
| POPR             | 44                    | Pops a value from the stack into a register.                       |
| POPA             | 45                    | Pops a value from the stack into memory.                           |
| CALLR            | 3B                    | Pushes the address for the next instruction, then jumps into the address stored in a register. |
| CALLA            | 3C                    | Same as CALLR, but the address is fed as an instruction operand.   |
| RET              | 3D                    | Pops the address on the stack, then jumps to this address.         |
| BREAKPOINT       | 3E                    | Causes a breakpoint, displays registers and waits for user input.  |
| OUT              | 3F                    | Sends data to a device port.                                       |
| IN               | 40                    | Polls data from a device port.                                     |
| INC              | 41                    | Increments a register.                                             |
| DEC              | 42                    | Decrements a register.                                             |