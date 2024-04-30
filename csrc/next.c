
#include "next.h"
#include "imm.h"
#include "prims.h"

#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


byte *falloc(void) {
    return malloc(MEM_SIZE);
}

byte *setup(VM *vm) {
    byte *mem = falloc();
    if(mem != NULL) {
        init(vm, mem);
        dict(vm);
    }
        
    return mem;
}
void dict(VM *vm) {
    //(void) vm;
    hp =  0;
    lp = -1;

    PRIMS("NEXT", NEXT);

    // X -> unique name
    // Y -> manual
    // Z -> add P_

    // Begining of primitives words
    // ITC words
    XPRIMS(nop,     NOP, NEXT);
    XPRIMS(halt,    HALT, NEXT);
    XPRIMS(lit,     LIT, NEXT);
    //XPRIMS(next,    NEXT);
    //XPRIMS(nest,    NEST);
    XPRIMS(unnest,  UNNEST, NEXT);
    XPRIMS(jmp,     JMP, NEXT);
    XPRIMS(jz,      JZ, NEXT);
    XPRIMS(execute, EXE, NEXT);
    XPRIMS(rjmp,     RJMP, NEXT);
    XPRIMS(rjz,      RJZ, NEXT);
    
    // Stack manipulation and status words
    XPRIMS(dup,     DUP, NEXT);
    XPRIMS(drop,    DROP, NEXT);
    XPRIMS(swap,    SWAP, NEXT);
    YPRIMS(push,    ">R", PUSH, NEXT);
    YPRIMS(pop,     "R>", POP, NEXT);
    XPRIMS(pick,    PICK, NEXT);
    XPRIMS(rick,    RICK, NEXT);
    XPRIMS(depth,   LDP, NEXT);
    XPRIMS(rdepth,  LDR, NEXT);
 
    // Logic operators
    YPRIMS(eq,      "=", EQ, NEXT);
    YPRIMS(neq,     "<>", NEQ, NEXT);
    YPRIMS(gt,      ">", GT, NEXT);
    YPRIMS(lt,      "<", LT, NEXT);
   
    // Bitweise operators
    XPRIMS(and,     AND, NEXT);
    XPRIMS(or,      OR, NEXT);
    XPRIMS(xor,     XOR, NEXT);
    XPRIMS(rshift,  SHR, NEXT);
    XPRIMS(lshift,  SHL, NEXT);

    // Math operators
    YPRIMS(add,     "+", ADD, NEXT);
    YPRIMS(sub,     "-", SUB, NEXT);
    YPRIMS(mul,     "*", MUL, NEXT);
    YPRIMS(div,     "/", DIV, NEXT);
    XPRIMS(mod,     MOD, NEXT);

    // Memory read and write operators
    YPRIMS(ldc,     "@", LDC, NEXT);
    YPRIMS(strc,    "!", STRC, NEXT);
    YPRIMS(ldb,     "C@", LDB, NEXT);
    YPRIMS(strb,    "C!", STRB, NEXT);

    // IO operators
    XPRIMS(key,     KEY, NEXT);
    XPRIMS(emit,    EMIT, NEXT);


    // Begining of higher primitives words
    // Flow control
    XPRIMS(ijmp,     LIT, JMP, NEXT);
    XPRIMS(ijz,      LIT, JZ, NEXT);
    XPRIMS(iexecute, LIT, EXE, NEXT);
    XPRIMS(irjmp,    LIT, RJMP, NEXT);
    XPRIMS(irjz,     LIT, RJZ, NEXT);


    // Begining of colon words
    // Logical values
    XCOLON(true, lit, TRUE, unnest);
    XCOLON(false, lit, FALSE, unnest);

    // Size values
    YCOLON(xfunc, "func", lit, FUNC_SIZE, unnest);
    YCOLON(xcell, "cell", lit, CELL_SIZE, unnest);
    YCOLON(xbyte, "byte", lit, BYTE_SIZE, unnest);
    XCOLON(mems, lit, MEM_SIZE, unnest);


    // Begining of tests


    XCOLON(ASDF,true, dup, swap, add, halt, unnest);
    XCOLON(qwer,ASDF, dup, swap, add, halt, unnest); IMMEDIATE;
    XCOLON(test1, lit, 1, false, dup, xfunc, unnest);
    XCOLON(test2, lit, 2, test1, lit, 22, halt);
    XCOLON(test3, lit, test1, execute, halt);


    XCOLON(r1, lit, 1, unnest);
    XCOLON(r2, r1, dup, lit, 1, add, unnest);
    XCOLON(r3, r2, dup, lit, 1, add, unnest);
    XCOLON(test4, r3, r3, iexecute, r2, dup, add, halt, halt);

    XCOLON(test5, r3, r3, irjmp, 8, xbyte, xcell, xfunc, lit, 0, halt);
    XCOLON(test6, r3, r3, ijmp, test2+1, halt);

    XCOLON(test8, lit, 1, dup, lit, 5, sub, xbyte, dup, xcell, xfunc, lit, 123, halt);
    XCOLON(test7, lit, 1, add, dup, lit, 5, sub, irjz, CELL_SIZE, test7, halt, halt);


    penum2func();
    puts("");
    pwords(vm);
    puts("");
    hexdump(vm, 16, (hp | 0xf)/16 + 1);
    puts("");

    DR(test8);

    DR(test3);

    DR(test3);

    DR(test4);

    DR(test5);

   //DR(test7);
    
/*
    XVAR(HP);
    XVAR(LP);


    // COLD: resets the dictionary
    cell _hp = hp;
    cell _lp = lp;
    XCOLON(COLD, LIT, _hp, HP, STRC, LIT, _lp, LP, STRC, HALT);
    runf(vm, COLD);
    */

    /*

        XPRIMS(t1, _tru, _tru, _next);

        XCOLON(t2, t1, t1, UNNEST);
        XCOLON(m, t2, LIT, 123, LIT, t1, EXE, t1, HALT);
        XCOLON(m2, LIT, 123, DUP, ADD, TRU, MUL, FLS, m);
        XCOLON(m3, NOP);
        BEGIN(KEY, DUP, LIT, 65, EQ);
        IF(HALT);
        ELSE(FLS);
        THEN(LIT, 777);
        AGAIN(HALT);

        XCOLON(echo, NOP);
        BEGIN(KEY, DUP, EMIT, LIT, 'q', EQ);
        UNTIL(HALT);

        XCOLON(e2, NOP);
        BEGIN(KEY, DUP, LIT, 'q', NEQ);
        WHILE(DUP, EMIT);
        REPEAT(LIT, 1234, HALT);

        CONST(X1, 123);
        VAR(Z1);
        VAR(Z2);
        XCOLON(t3, Z1, LDB, X1, Z1, STRB, TRU, Z1, LDB, HALT);

        runf(vm, t3);
        */
}

