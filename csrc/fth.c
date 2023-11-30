

#include "fth.h"

#include <stdio.h>


void _nop(VM *vm) {
    (void) vm;
}
void _halt(VM *vm) {
    P = OFF;
}
void _lit(VM *vm) {
    PPUSH = *(TP++);
}
void _next(VM *vm) {
    MEXT(DTC);
}
void _nest(VM *vm) {
    RPUSH = (cell) TP;
    TP = FP;
    MEXT(DTC);
}
void _unnest(VM *vm) {
    TP = (cell *) RPOP;
    MEXT(DTC);
}
void _jmp(VM *vm) {
    cell addr = PPOP;
    TP = (cell *) addr;
}
void _jz(VM *vm) {
    cell addr = PPOP;
    cell flag = PPOP;
    if(flag == FALSE)
        TP = (cell *) addr;
}
void _exe(VM *vm) {
    cell addr = PPOP;
    FP = (func *) addr;
}

void _dup(VM *vm) {
    cell val = PPOP;
    PPUSH = val;
    PPUSH = val;
}
void _drop(VM *vm) {
    (void) PPOP;
}
void _swap(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = a;
    PPUSH = b;
}
void _push(VM *vm) {
    RPUSH = PPOP;
}
void _pop(VM *vm) {
    PPUSH = RPOP;
}
void _pick(VM *vm) {
    byte n = PPOP + 1;
    n = PSP - n;
    PPUSH = PS[n];
}
void _rick(VM *vm) {
    byte n = PPOP + 1;
    n = RSP - n;
    PPUSH = RS[n];
}
void _ldp(VM *vm) {
    byte val = PSP;
    PPUSH = val;
}
void _ldr(VM *vm) {
    byte val = RSP;
    PPUSH = val;
}
void _eq(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b == a);
}
void _neq(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b != a);
}
void _gt(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b > a);
}
void _lt(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b < a);
}
void _and(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b & a;
}
void _or(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b | a;
}
void _xor(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b ^ a;
}
void _shr(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b >> a;
}
void _shl(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b << a;
}
void _tru(VM *vm) {
    PPUSH = TRUE;
}
void _fls(VM *vm) {
    PPUSH = FALSE;
}
void _add(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b + a;
}
void _sub(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b - a;
}
void _mul(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b * a;
}
void _div(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b / a;
}
void _mod(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b % a;
}
void _ldc(VM *vm) {
    cell addr = PPOP;
    cell val = *((cell *) addr);
    PPUSH = val;
}
void _strc(VM *vm) {
    cell addr = PPOP;
    cell val = PPOP;
    *((cell *) addr) = val;
}
void _ldb(VM *vm) {
    cell addr = PPOP;
    byte val = *((byte *) addr);
    PPUSH = val;
}
void _strb(VM *vm) {
    cell addr = PPOP;
    byte val = PPOP;
    *((byte *) addr) = val;
}
void _cell(VM *vm) {
    PPUSH = CELL_SIZE;
}
void _byte(VM *vm) {
    PPUSH = BYTE_SIZE;
}
void _mem(VM *vm) {
    PPUSH = MEM_SIZE;
}
void _key(VM *vm) {
    byte c = getchar();
    PPUSH = c;
}
void _emit(VM *vm) {
    byte c = PPOP;
    putchar(c);
}

