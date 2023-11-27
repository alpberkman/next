

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
    RPUSH.cp = TP;
    TP = FP;
    MEXT(DTC);
}
void _unnest(VM *vm) {
    TP = RPOP.cp;
    MEXT(DTC);
}
void _jmp(VM *vm) {
    cell addr = PPOP;
    TP = addr.cp;
}
void _jz(VM *vm) {
    cell addr = PPOP;
    cell flag = PPOP;
    if(flag.i == FALSE)
        TP = addr.cp;
}
void _exe(VM *vm) {
    cell addr = PPOP;
    TP++;
    FP = addr.cp;
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
    byte n = PPOP.i + 1;
    n = PSP - n;
    PPUSH = PS[n];
}
void _rick(VM *vm) {
    byte n = PPOP.i + 1;
    n = RSP - n;
    PPUSH = RS[n];
}
void _ldp(VM *vm) {
    PPUSH = ((cell) {.i = PSP});
}
void _ldr(VM *vm) {
    PPUSH = ((cell) {.i = RSP});
}
void _eq(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = LOGICAL(b.i == a.i)});
}
void _neq(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = LOGICAL(b.i != a.i)});
}
void _gt(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = LOGICAL(b.i > a.i)});
}
void _lt(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = LOGICAL(b.i < a.i)});
}
void _and(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = LOGICAL(b.i & a.i)});
}
void _or(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = LOGICAL(b.i | a.i)});
}
void _xor(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = LOGICAL(b.i ^ a.i)});
}
void _shr(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = (b.i >> a.i)});
}
void _shl(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = (b.i << a.i)});
}
void _tru(VM *vm) {
    PPUSH = ((cell) {.i = TRUE});
}
void _fls(VM *vm) {
    PPUSH = ((cell) {.i = FALSE});
}
void _add(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = (b.i + a.i)});
}
void _sub(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = (b.i - a.i)});
}
void _mul(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = (b.i * a.i)});
}
void _div(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = (b.i / a.i)});
}
void _mod(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = ((cell) {.i = (b.i % a.i)});
}
void _ldc(VM *vm) {
    cell addr = PPOP;
    cell val = *(addr.cp);
    PPUSH = val;
}
void _strc(VM *vm) {
    cell addr = PPOP;
    cell val = PPOP;
    *(addr.cp) = val;
}
void _ldb(VM *vm) {
    cell addr = PPOP;
    byte val = *(addr.bp);
    PPUSH = ((cell) {.i = val});
}
void _strb(VM *vm) {
    cell addr = PPOP;
    cell val = PPOP;
    *(addr.bp) = val.i;
}
void _cell(VM *vm) {
    PPUSH = sizeof(cell);
}
void _byte(VM *vm) {
    PPUSH = sizeof(byte);
}
void _mem(VM *vm) {
    PPUSH = ((cell) {.i = MEM_SIZE});
}
void _key(VM *vm) {
    byte c = getchar();
    PPUSH = c;
}
void _emit(VM *vm) {
    byte c = PPOP;
    putchar(c);
}

