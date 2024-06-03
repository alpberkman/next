
#include "prims.h"

#include <stdio.h>


void exec(VM *vm, mca addr) {
    func f = LUT(addr);
    f(vm);
}

FTH(_nop) {
    (void) vm;
}
FTH(_halt) {
    XP = OFF;
}
FTH(_lit) {
    PPUSH = MLIT;
}
FTH(_next) {
    MEXT;
}
FTH(_nest) {
    RPUSH = MNEST;
    MEXT;
}
FTH(_unnest) {
    MUNNEST = RPOP;
    MEXT;
}
FTH(_jmp) {
    cell addr = PPOP;
    MJMP = addr;
}
FTH(_jz) {
    cell addr = PPOP;
    cell flag = PPOP;
    if(flag == FALSE)
        MJMP = addr;
}
FTH(_exe) {
    cell addr = PPOP;
    MEXE = addr;
}
FTH(_rjmp) {
    cell addr = PPOP;
    MJMP += addr;
}
FTH(_rjz) {
    cell addr = PPOP;
    cell flag = PPOP;
    if(flag == FALSE)
        MJMP += addr;
}
FTH(_dup) {
    cell val = TOS;
    PPUSH = val;
}
FTH(_drop) {
    (void) PPOP;
}
FTH(_swap) {
    cell tmp = NOS;
    NOS = TOS;
    TOS = tmp;
}
FTH(_push) {
    RPUSH = PPOP;
}
FTH(_pop) {
    PPUSH = RPOP;
}
FTH(_pick) {
    byte n = PPOP + 1;
    n = XPSP - n;
    PPUSH = XPS[n];
}
FTH(_rick) {
    byte n = PPOP + 1;
    n = XRSP - n;
    PPUSH = XRS[n];
}
FTH(_ldp) {
    byte val = XPSP;
    PPUSH = val;
}
FTH(_ldr) {
    byte val = XRSP;
    PPUSH = val;
}
FTH(_eq)  { LBINOP(==); }
FTH(_neq) { LBINOP(!=); }
FTH(_gt)  { LBINOP(>); }
FTH(_lt)  { LBINOP(<); }
FTH(_and) { MBINOP(&); }
FTH(_or)  { MBINOP(|); }
FTH(_xor) { MBINOP(^); }
FTH(_shr) { MBINOP(>>); }
FTH(_shl) { MBINOP(<<); }
FTH(_add) { MBINOP(+); }
FTH(_sub) { MBINOP(-); }
FTH(_mul) { MBINOP(*); }
FTH(_div) { MBINOP(/); }
FTH(_mod) { MBINOP(%); }
FTH(_ldc) {
    cell addr = PPOP;
    cell val = CELL_FETCH(XMEM, addr);
    PPUSH = val;
}
FTH(_strc) {
    cell addr = PPOP;
    cell val = PPOP;
    CELL_FETCH(XMEM, addr) = val;
}
FTH(_ldb) {
    cell addr = PPOP;
    byte val = BYTE_FETCH(XMEM, addr);
    PPUSH = val;
}
FTH(_strb) {
    cell addr = PPOP;
    byte val = PPOP;
    BYTE_FETCH(XMEM, addr) = val;
}
FTH(_call) {
    func f = MCALL;
    f(vm);
}
FTH(_key) {
    byte c = getchar();
    PPUSH = c;
}
FTH(_emit) {
    byte c = PPOP;
    putchar(c);
}
