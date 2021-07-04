# Pain64
A 64-bit ISA written in C.
## Instructions
| Instruction Name    |Instruction Opcode(hex)| Purpose                                                        |
| :------------------ | :-------------------: | -------------------------------------------------------------: |
| NOP                 | 0                     | (None)                                                         |
| HALT                | 1                     | Stops the emulator/board.                                      |
| MOVU64RR            | 2                     | Moves an unsigned 64-bit value from a register to another.     |
| MOVU64RV            | 3                     | Moves an unsigned 64-bit value to a register.                  |
| MOVU64RA            | 4                     | Moves an unsigned 64-bit value stored in memory to a register. |
| MOVU64AR            | 5                     | Moves an unsigned 64-bit value from a register to memory.      |
| MOVU64AV            | 6                     | Moves an unsigned 64-bit value to memory.                      |
| MOVI64RR            | 7                     | Moves an signed 64-bit value from a register to another.       |
| MOVI64RV            | 8                     | Moves an signed 64-bit value to a register.                    |
| MOVI64RA            | 9                     | Moves an signed 64-bit value stored in memory to a register.   |
| MOVI64AR            | A                     | Moves an signed 64-bit value from a register to memory.        |
| MOVI64AV            | B                     | Moves an signed 64-bit value to memory.                        |
| MOVU32RR            | C                     | Moves an unsigned 32-bit value from a register to another.     |
| MOVU32RV            | D                     | Moves an unsigned 32-bit value to a register.                  |
| MOVU32RA            | E                     | Moves an unsigned 32-bit value stored in memory to a register. |
| MOVU32AR            | F                     | Moves an unsigned 32-bit value from a register to memory.      |
| MOVU32AV            | 10                    | Moves an unsigned 32-bit value to memory.                      |
| MOVI32RR            | 11                    | Moves an signed 32-bit value from a register to another.       |
| MOVI32RV            | 12                    | Moves an signed 32-bit value to a register.                    |
| MOVI32RA            | 13                    | Moves an signed 32-bit value stored in memory to a register.   |
| MOVI32AR            | 14                    | Moves an signed 32-bit value from a register to memory.        |
| MOVI32AV            | 15                    | Moves an signed 32-bit value to memory.                        |
| MOVU16RR            | 16                    | Moves an unsigned 16-bit value from a register to another.     |
| MOVU16RV            | 17                    | Moves an unsigned 16-bit value to a register.                  |
| MOVU16RA            | 18                    | Moves an unsigned 16-bit value stored in memory to a register. |
| MOVU16AR            | 19                    | Moves an unsigned 16-bit value from a register to memory.      |
| MOVU16AV            | 1A                    | Moves an unsigned 16-bit value to memory.                      |
| MOVI16RR            | 1B                    | Moves an signed 16-bit value from a register to another.       |
| MOVI16RV            | 1C                    | Moves an signed 16-bit value to a register.                    |
| MOVI16RA            | 1D                    | Moves an signed 16-bit value stored in memory to a register.   |
| MOVI16AR            | 1E                    | Moves an signed 16-bit value from a register to memory.        |
| MOVI16AV            | 1F                    | Moves an signed 16-bit value to memory.                        |
| MOVU8RR             | 20                    | Moves an unsigned 8-bit value from a register to another.      |
| MOVU8RV             | 21                    | Moves an unsigned 8-bit value to a register.                   |
| MOVU8RA             | 22                    | Moves an unsigned 8-bit value stored in memory to a register.  |
| MOVU8AR             | 23                    | Moves an unsigned 8-bit value from a register to memory.       |
| MOVU8AV             | 24                    | Moves an unsigned 8-bit value to memory.                       |
| MOVI8RR             | 25                    | Moves an signed 8-bit value from a register to another.        |
| MOVI8RV             | 26                    | Moves an signed 8-bit value to a register.                     |
| MOVI8RA             | 27                    | Moves an signed 8-bit value stored in memory to a register.    |
| MOVI8AR             | 28                    | Moves an signed 8-bit value from a register to memory.         |
| MOVI8AV             | 29                    | Moves an signed 8-bit value to memory.                         |