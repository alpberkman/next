
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
    cell val = PPOP;
    PPUSH = val;
    PPUSH = val;
}
FTH(_drop) {
    (void) PPOP;
}
FTH(_swap) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = a;
    PPUSH = b;
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
FTH(_eq) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b == a);
}
FTH(_neq) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b != a);
}
FTH(_gt) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b > a);
}
FTH(_lt) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b < a);
}
FTH(_and) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b & a;
}
FTH(_or) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b | a;
}
FTH(_xor) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b ^ a;
}
FTH(_shr) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b >> a;
}
FTH(_shl) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b << a;
}
FTH(_add) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b + a;
}
FTH(_sub) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b - a;
}
FTH(_mul) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b * a;
}
FTH(_div) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b / a;
}
FTH(_mod) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b % a;
}
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
