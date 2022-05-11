// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

@R2 // set RAM[2] to zero.
M = 0

@R0
D = M
@R1
D = D - M //RAM[0] - RAM[1]

// selective jumping to save time.
@POSITIVE
D;JGE // if positive, jumps to add RAM[0] Ram[1] no of times.

@NEGATIVE
D;JLT // if negatve, jumps to add RAM[1] Ram[0] no of times.

// for example, for 2*5, its easier to add 5 two times rather than adding 2 five times

(POSITIVE)
@R1
D = M // D = RAM[1]
@temp
M = D // i = Ram[1]

// while(i > 0)
(LOOPP)
    @LOOP_END
    D;JLE // if i <= 0, end loop
    @R0
    D = M
    @R2
    M = M + D // RAM[2] = RAM[2] + RAM[0](D)
    @temp
    M = M - 1
    D = M // i -= 1
    @LOOPP
    0;JMP

(NEGATIVE)
@R0
D = M // D = RAM[1]
@temp
M = D // i = Ram[1]

// while(i > 0)
(LOOPN)
    @LOOP_END
    D;JLE // if i <= 0, end loop
    @R1
    D = M
    @R2
    M = M + D // RAM[2] = RAM[2] + RAM[1](D)
    @temp
    M = M - 1
    D = M // i -= 1
    @LOOPN
    0;JMP

(LOOP_END)
@LOOP_END
0;JMP