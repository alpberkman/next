
#ifndef _PRIMS_H
#define _PRIMS_H

#include "core.h"


#define FTH(NAME) \
    void NAME (FTH *fth)

#define XENUM(E, F)  E,
#define XFUNC(E, F)   F,
#define XENUMNAME(E, F) #E,
#define XFUNCNAME(E, F) #F,
#define XENUM2FUNC(E, F) #E, #F
#define XFUNCSIG(E, F) void F (FTH *fth);
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
    APPLY(ADD,  _add) \
    APPLY(SUB,  _sub) \
    APPLY(MUL,  _mul) \
    APPLY(DIV,  _div) \
    APPLY(MOD,  _mod) \
    APPLY(LDC,  _ldc) \
    APPLY(STRC, _strc) \
    APPLY(LDB,  _ldb) \
    APPLY(STRB, _strb) \
    APPLY(CALL, _call) \
    APPLY(KEY,  _key) \
    APPLY(EMIT, _emit)


TABLE(XFUNCSIG);


#define LUT(ADDR) ((func [256]) { TABLE(XFUNCTAB) })[ADDR]


typedef enum PRIM PRIM;
enum PRIM {
    TABLE(XENUM)
};


#define BINOP(FUNC, MOD) \
    cell tos = PPOP; \
    cell nos = PPOP; \
    PPUSH = MOD(nos FUNC tos);

#define EMPTY

#define MBINOP(FUNC) \
    BINOP(FUNC, EMPTY)

#define LBINOP(FUNC) \
    BINOP(FUNC, LOGICAL)

#endif
