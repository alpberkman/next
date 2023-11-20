

#include <stdio.h>

#include "next.h"
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
    byte opcode = BYTE_VAL(vm->spu.ip);
    INCIP;
    return opcode;
}
void exec(VM *vm, byte opcode) {
    const fun prims[] = {
        _nop, _halt, _lit,
        _next, _nest, _unnest,
        _jmp, _jz, _exe,
        _dup, _drop, _swap,
        _push, _pop,
        _pick, _rick,
        _ldp, _ldr,
        _eq, _neq, _gt, _lt,
        _and, _or, _xor,
        _shr, _shl,
        _tru, _fls,
        _add, _sub, _mul,
        _div, _mod,
        _ldc, _strc,
        _ldb, _strb,
        _cell, _byte,
        _mem,
        _key, _emit,
    };
    printf("opcode: %i\n", opcode);
    prims[opcode](vm);
    stacks(vm);
}
void tick(VM *vm) {
    printf("ip: %i\n", vm->spu.ip);
    printf("wp: %i\n", vm->spu.wp);
    exec(vm, fetch(vm));
}
void run(VM *vm) {
    for(vm->spu.p = ON; vm->spu.p == ON; tick(vm));
}

void _nop(VM *vm) {
    (void) vm;
}
void _halt(VM *vm) {
    vm->spu.p = OFF;
}
void _lit(VM *vm) {
    cell val = CELL_VAL(vm->spu.wp);
    INCWP;
    PPUSH = val;
}
void _next(VM *vm) {
    MACRO_NEXT;
}
void _nest(VM *vm) {
    RPUSH = vm->spu.wp;
    vm->spu.wp = vm->spu.ip;
    MACRO_NEXT;
}
void _unnest(VM *vm) {
    vm->spu.wp = RPOP;
    MACRO_NEXT;
}
void _jmp(VM *vm) {
    cell addr = PPOP;
    vm->spu.wp = addr;
}
void _jz(VM *vm) {
    cell addr = PPOP;
    cell flag = PPOP;
    if(flag == ((cell) FALSE))
        vm->spu.wp = addr;
}
void _exe(VM *vm) {
    cell addr = CELL_VAL(PPOP);
    INCWP;
    vm->spu.ip = addr;
}
void _dup(VM *vm) {
    cell val = PPOP;
    PPUSH = val;
    PPUSH = val;
}
void _drop(VM *vm) {
    --vm->spu.psp;
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
    n = vm->spu.psp - n;
    PPUSH = vm->spu.ps[n];
}
void _rick(VM *vm) {
    byte n = PPOP + 1;
    n = vm->spu.rsp - n;
    PPUSH = vm->spu.rs[n];
}
void _ldp(VM *vm) {
    byte val = vm->spu.psp;
    PPUSH = val;
}
void _ldr(VM *vm) {
    byte val = vm->spu.rsp;
    PPUSH = val;
}
void _eq(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b == a ? TRUE : FALSE;
}
void _neq(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b != a ? TRUE : FALSE;
}
void _gt(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b > a ? TRUE : FALSE;
}
void _lt(VM *vm) {
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b < a ? TRUE : FALSE;
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




















