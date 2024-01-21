
#include "next.h"

#include <stdlib.h>


void runf(VM *vm, cell addr) {
    runc(&ITC, MEM, vm, addr);
}
void init(VM *vm) {
    hp = 0;
    lp = 0;

    // Setup ITC
    IP = 0;
    WP = 0;
    // Setup SPU
    PSP = 0;
    RSP = 0;
    //Setup RAM
    MEM = malloc(MEM_SIZE);
    if(MEM == NULL)
        return;

    XPRIMS(NOP, _nop, _next);
    XPRIMS(HALT, _halt, _next);
    XPRIMS(LIT, _lit, _next);
    XPRIMS(NEXT, _next);
    XPRIMS(NEST, _nest);
    XPRIMS(UNNEST, _unnest, _next);
    XPRIMS(JMP, _jmp, _next);
    XPRIMS(JZ, _jz, _next);
    XPRIMS(EXE, _exe, _next);

    XPRIMS(DUP, _dup, _next);
    XPRIMS(DROP, _drop, _next);
    XPRIMS(SWAP, _swap, _next);
    YPRIMS(PUSH, ">R", _push, _next);
    YPRIMS(POP, "R>", _pop, _next);
    XPRIMS(PICK, _pick, _next);
    XPRIMS(RICK, _rick, _next);
    YPRIMS(LDP, "DEPTH", _ldp, _next);
    YPRIMS(LDR, "RDEPTH", _ldr, _next);
    YPRIMS(EQ, "=",_eq, _next);
    YPRIMS(NEQ, "<>", _neq, _next);
    YPRIMS(GT, ">", _gt, _next);
    YPRIMS(LT, "<", _lt, _next);
    XPRIMS(AND, _and, _next);
    XPRIMS(OR, _or, _next);
    XPRIMS(XOR, _xor, _next);
    YPRIMS(SHR, "RSHIFT", _shr, _next);
    YPRIMS(SHL, "LSHIFT", _shl, _next);
    YPRIMS(TRU, "TRUE", _tru, _next);
    YPRIMS(FLS, "FALSE", _fls, _next);
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


    cell _hp = hp;
    cell _lp = lp;
    XCOLON(X, LIT, _hp, HP, STRC, LIT, _lp, LP, STRC, HALT);
    runf(vm, X);
    debug(vm);

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
