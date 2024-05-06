
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

    // Begining of primitive words
    // ITC words
    XPRIMS(nop,     NOP, NEXT);
    XPRIMS(halt,    HALT, NEXT);
    XPRIMS(lit,     LIT, NEXT);
    XPRIMS(next,    NEXT);
    XPRIMS(nest,    NEST);
    XPRIMS(unnest,  UNNEST);
    XPRIMS(jmp,     JMP, NEXT);
    XPRIMS(jz,      JZ, NEXT);
    XPRIMS(execute, EXE, NEXT);
    XPRIMS(rjmp,    RJMP, NEXT);
    XPRIMS(rjz,     RJZ, NEXT);
    
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

    // C function calls
    XPRIMS(call, CALL, NEXT);

    // IO operators
    XPRIMS(key,     KEY, NEXT);
    XPRIMS(emit,    EMIT, NEXT);


    // Begining of higher primitive words
    // Flow control
    XPRIMS(ijmp,        LIT, JMP, NEXT);
    XPRIMS(ijz,         LIT, JZ, NEXT);
    XPRIMS(iexecute,    LIT, EXE, NEXT);
    XPRIMS(irjmp,       LIT, RJMP, NEXT);
    XPRIMS(irjz,        LIT, RJZ, NEXT);


    // Begining of colon words
    // CREATE ... DOES> like words
    XCOLON(dovar,   pop, unnest);
    XCOLON(docon,   pop, ldc, unnest);

    // Logical values
    XCON(true, TRUE);
    XCON(false, FALSE);

    // Size values
    YCON(xfunc, "func", FUNC_SIZE);
    YCON(xcell, "cell", CELL_SIZE);
    YCON(xbyte, "byte", BYTE_SIZE);
    XCON(mems, MEM_SIZE);
    YCOLON(cellp,   "CELL+", xcell, add, unnest);
    YCOLON(bytep,   "BYTE+", xbyte, add, unnest);
    XCOLON(cells,   xcell, mul, unnest);
    XCOLON(bytes,   xbyte, mul, unnest);

    // Important variables
    YVAR(xhp, "hp");
    YVAR(xlp, "lp");
    XVAR(state);

    // Stack words
    XCOLON(over,    lit, 1, pick, unnest);
    XCOLON(nip,     swap, drop, unnest);
    YCOLON(rat,     "R@", lit, 1, rick, unnest);
    XCOLON(rot,     push, swap, pop, swap, unnest);
    YCOLON(mrot,    "-rot", rot, rot, unnest);

    // Other CREATE ... DOES> like words
    XCOLON(dostr,
        rat, cellp, 
        rat, ldc,
        pop, over, add, cellp, jmp);


    // Start
    COLD(lit, new_hp, xhp, strc, lit, new_lp, xlp, strc, false, state, strc, halt);


    // For debugging
    printf("%i %i\n", hp, lp);


#define ON true, swap, strc
#define OFF false, swap, strc
#define TOGGLE lit, 0, eq
XCOLON(XXXXX, lit, MEM_SIZE, unnest);

    penum2func();
    puts("");
    pwords(vm);
    puts("");
    hexdump(vm, 16, (hp | 0xf)/16 + 1);
    puts("");

    XCON(test1, 123);
    XCOLON(test2, test1, halt);
    DR(test2);

    XVAR(test3);
    XCOLON(test4, lit, 546, test3, strc, test3, ldc, halt);
    DR(test4);
   
   XCOLON(test5, xbyte, mems, false, halt);
   DR(test5);



   XCOLON(test6, false);
   IF(true, true, true, true);
   ELSE(false, false, false, false);
   THEN(lit, 134, halt);
   DR(test6);

    XCOLON(test7, lit, 123);
    STR("Hello World!");
    PF(lit, 456, halt);
    pwords(vm);
    puts("");
    hexdump(vm, 16, (hp | 0xf)/16 + 1);
    puts("");

    DR(test7);


    XCOLON(test8, lit, 123);
    CCALL(stacks);
    PF(lit, 456, halt);


    pwords(vm);
    puts("");
    hexdump(vm, 16, (hp | 0xf)/16 + 1);
    puts("");

    DR(test8);


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
;;;;;
}

