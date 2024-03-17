#ifndef _OP_H
#define _OP_H

#include "vm.h"


#define FTH(NAME) \
    void NAME (VM *vm)

#define XENUM(E, F)  E,
#define XFUNC(E, F)   F,
#define XNENUMAME(E, F) #E,
#define XFUNCNAME(E, F) #F,
#define XFUNCSIG(E, F) void F (VM *vm);
#define XFUNCTAB(E, F) [E] = F,

#define TABLE(APPLY) \
    APPLY(NOP,  _nop) \
    APPLY(HALT, _halt) \
    APPLY(LIT,  _lit) \
    APPLY(NEXT, _next) \
    APPLY(NEST, _nest) \
    APPLY(UNNEST, _unnest) \
    APPLY(JMP,  _jmp) \
    APPLY(JZ,   _jz) \
    APPLY(EXE,  _exe) \
    APPLY(DUP,  _dup) \
    APPLY(DROP, _drop) \
    APPLY(SWAP, _swap) \
    APPLY(PUSH, _push) \
    APPLY(POP,  _pop) \
    APPLY(PICK, _pick) \
    APPLY(RICK, _rick) \
    APPLY(LDP,  _ldp) \
    APPLY(LDR,  _ldr) \
    APPLY(EQ,   _eq) \
    APPLY(NEQ,  _neq) \
    APPLY(GT,   _gt) \
    APPLY(LT,   _lt) \
    APPLY(AND,  _and) \
    APPLY(OR,   _or) \
    APPLY(XOR,  _xor) \
    APPLY(SHR,  _shr) \
    APPLY(SHL,  _shl) \
    APPLY(TRU,  _tru) \
    APPLY(FLS,  _fls) \
    APPLY(ADD,  _add) \
    APPLY(SUB,  _sub) \
    APPLY(MUL,  _mul) \
    APPLY(DIV,  _div) \
    APPLY(MOD,  _mod) \
    APPLY(LDC,  _ldc) \
    APPLY(STRC, _strc) \
    APPLY(LDB,  _ldb) \
    APPLY(STRB, _strb) \
    APPLY(FUNC, _func) \
    APPLY(CELL, _cell) \
    APPLY(BYTE, _byte) \
    APPLY(MEMS,  _mems) \
    APPLY(KEY,  _key) \
    APPLY(EMIT, _emit)


typedef enum OP OP;


enum OP {
    TABLE(XENUM)
};

func decode(byte op);
TABLE(XFUNCSIG)


#endif