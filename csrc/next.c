
#include "next.h"
#include "imm.h"
#include "prims.h"

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
    hp = 0;
    lp = 0;

    PRIMS("", NEXT);

    ZPRIMS(NOP,     NOP, NEXT);
    ZPRIMS(HALT,    HALT, NEXT);
    ZPRIMS(LIT,     LIT, NEXT);
    ZPRIMS(NEXT,    NEXT);
    ZPRIMS(NEST,    NEST);
    ZPRIMS(UNNEST,  UNNEST, NEXT);
    ZPRIMS(JMP,     JMP, NEXT);
    ZPRIMS(JZ,      JZ, NEXT);
    ZPRIMS(EXE,     EXE, NEXT);
    
    ZPRIMS(DUP,     DUP, NEXT);
    ZPRIMS(DROP,    DROP, NEXT);
    ZPRIMS(SWAP,    SWAP, NEXT);
    YPRIMS(XPUSH,   ">R",   PUSH, NEXT);
    YPRIMS(XPOP,    "R>",   POP, NEXT);
    ZPRIMS(PICK,    PICK, NEXT);
    ZPRIMS(RICK,    RICK, NEXT);
    XPRIMS(DEPTH,   LDP, NEXT);
    XPRIMS(RDEPTH,  LDR, NEXT);
 
    YPRIMS(XEQ,      "=",    EQ, NEXT);
    YPRIMS(XNEQ,     "<>",   NEQ, NEXT);
    YPRIMS(XGT,      ">",    GT, NEXT);
    YPRIMS(XLT,      "<",    LT, NEXT);
   
    ZPRIMS(AND,     AND, NEXT);
    YPRIMS(YOR,     "OR",   OR, NEXT);
    ZPRIMS(XOR,     XOR, NEXT);
    XPRIMS(RSHIFT,  SHR, NEXT);
    XPRIMS(LSHIFT,  SHL, NEXT);
    YPRIMS(XTRUE,   "TRUE",     TRU, NEXT);
    YPRIMS(XFALSE,  "FALSE",    FLS, NEXT);

    XCOLON(ASDF, XTRUE, XDUP, XSWAP, XUNNEST);

/*

    YPRIMS(ADD, "+", _add, _next);
    YPRIMS(SUB, "-", _sub, _next);
    YPRIMS(MUL, "*", _mul, _next);
    YPRIMS(DIV, "/", _div, _next);
    XPRIMS(MOD, _mod, _next);
    YPRIMS(LDC, "@", _ldc, _next);
    YPRIMS(STRC, "!", _strc, _next);
    YPRIMS(LDB, "C@", _ldb, _next);
    YPRIMS(STRB, "C!", _strb, _next);
    XPRIMS(FUNC, _func, _next);
    XPRIMS(CELL, _cell, _next);
    XPRIMS(BYTE, _byte, _next);
    YPRIMS(XMEM, "MEM", _mem, _next);
    XPRIMS(KEY, _key, _next);
    XPRIMS(EMIT, _emit, _next);


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

