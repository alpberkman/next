

#include "next.h"

#include <stdio.h>


void stacks(VM *vm) {
    printf("IP<%i>\n", vm->spu.ip);
    printf("WP<%i>\n", vm->spu.wp);
    printf("P<%i> ", vm->spu.psp);
    for(int i = 0; i < vm->spu.psp; ++i)
        printf("%i ", vm->spu.ps[i]);
    puts("");

    printf("R<%i> ", vm->spu.rsp);
    for(int i = 0; i < vm->spu.rsp; ++i)
        printf("%i ", vm->spu.rs[i]);
    puts("\n");
}

byte fetch(VM *vm) {
    byte opcode = BYTE_VAL(IP);
    INCIP;
    return opcode;
}
void exec(VM *vm, byte opcode) {
    printf("opcode: %i\n", opcode);
    PRIMS[opcode](vm);
    stacks(vm);
}
void tick(VM *vm) {
    printf("ip: %i\n", vm->spu.ip);
    printf("wp: %i\n", vm->spu.wp);
    exec(vm, fetch(vm));
}
void run(VM *vm) {
    for(P = ON; P == ON; tick(vm));
}

void _nop(VM *vm) {
    (void) vm;
}
void _halt(VM *vm) {
    P = OFF;
}
void _lit(VM *vm) {
    cell val = CELL_VAL(WP);
    INCWP;
    PPUSH = val;
}
void _next(VM *vm) {
    MEXT(WP);
}
void _nest(VM *vm) {
    RPUSH = WP;
    WP = IP;
    MEXT(WP);
}
void _unnest(VM *vm) {
    WP = RPOP;
    MEXT(WP);
}
void _jmp(VM *vm) {
    cell addr = PPOP;
    WP = addr;
}
void _jz(VM *vm) {
    cell addr = PPOP;
    cell flag = PPOP;
    if(flag == ((cell) FALSE))
        WP = addr;
}
void _exe(VM *vm) {
    MEXT(PPOP);
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
    cell val = CELL_VAL(addr);
    PPUSH = val;
}
void _strc(VM *vm) {
    cell addr = PPOP;
    cell val = PPOP;
    CELL_VAL(addr) = val;
}
void _ldb(VM *vm) {
    cell addr = PPOP;
    byte val = BYTE_VAL(addr);
    PPUSH = val;
}
void _strb(VM *vm) {
    cell addr = PPOP;
    byte val = PPOP;
    BYTE_VAL(addr) = val;
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




















