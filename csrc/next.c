

#include "next.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


cell hp;
cell lp;


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
    XPRIMS(NEXT, _next, _next);
    XPRIMS(NEST, _nest, _next);
    XPRIMS(UNNEST, _unnest, _next);
    XPRIMS(JMP, _jmp, _next);
    XPRIMS(JZ, _jz, _next);
    XPRIMS(EXE, _exe, _next);

    XPRIMS(DUP, _dup, _next);
    XPRIMS(DROP, _drop, _next);
    XPRIMS(SWAP, _swap, _next);
    XPRIMS(PUSH, _push, _next);
    XPRIMS(POP, _pop, _next);
    XPRIMS(PICK, _pick, _next);
    XPRIMS(RICK, _rick, _next);
    XPRIMS(LDP, _ldp, _next);
    XPRIMS(LDR, _ldr, _next);
    XPRIMS(EQ, _eq, _next);
    XPRIMS(NEQ, _neq, _next);
    XPRIMS(GT, _gt, _next);
    XPRIMS(LT, _lt, _next);
    XPRIMS(AND, _and, _next);
    XPRIMS(OR, _or, _next);
    XPRIMS(XOR, _xor, _next);
    XPRIMS(SHR, _shr, _next);
    XPRIMS(SHL, _shl, _next);
    XPRIMS(TRU, _tru, _next);
    XPRIMS(FLS, _fls, _next);
    XPRIMS(ADD, _add, _next);
    XPRIMS(SUB, _sub, _next);
    XPRIMS(MUL, _mul, _next);
    XPRIMS(DIV, _div, _next);
    XPRIMS(MOD, _mod, _next);
    XPRIMS(LDC, _ldc, _next);
    XPRIMS(STRC, _strc, _next);
    XPRIMS(LDB, _ldb, _next);
    XPRIMS(STRB, _strb, _next);
    XPRIMS(FUNC, _func, _next);
    XPRIMS(CELL, _cell, _next);
    XPRIMS(BYTE, _byte, _next);
    XPRIMS(XMEM, _mem, _next);
    XPRIMS(KEY, _key, _next);
    XPRIMS(EMIT, _emit, _next);

    //XPRIMS(XXX, _next);
/*
    XPRIMS(NOP, _next);
    XPRIMS(UNNEST, _unnest);
    XPRIMS(HALT, _halt);
    //IMMEDIATE;
    XPRIMS(LIT, _lit, _next);
    XPRIMS(EXE, _exe);
    */



    XPRIMS(t1, _tru, _tru, _next);

    XCOLON(t2, t1, t1, UNNEST);
    XCOLON(m, t2, LIT, 123, LIT, t1, EXE, t1, HALT);
    XCOLON(m2, LIT, 123, DUP, ADD, TRU, MUL, FLS, m);

    debug(vm);
    runf(vm, m2);
}

cell header(VM *vm, const char *name, int len) {
    CELL_FETCH(MEM, hp) = lp;
    lp = hp;
    hp += CELL_SIZE;

    BYTE_FETCH(MEM, hp) = MASK_VIS | len;
    hp += BYTE_SIZE;

    for(int i = 0; i < len; ++i)
        BYTE_FETCH(MEM, hp+BYTES(i)) = (byte) toupper(name[i]);
    hp += BYTES(len);

    return hp;
}
void cf(VM *vm, int len, ...) {
    va_list l;
    va_start(l, len);

    for(int i = 0; i < len; ++i)
        FUNC_FETCH(MEM, hp+FUNCS(i)) = (func) va_arg(l, func);
    hp += FUNCS(len);

    va_end(l);
}
void pf(VM *vm, int len, ...) {
    va_list l;
    va_start(l, len);

    for(int i = 0; i < len; ++i)
        CELL_FETCH(MEM, hp+CELLS(i)) = (cell) va_arg(l, cell);
    hp += CELLS(len);

    va_end(l);
}

void debug(VM *vm) {
    printf("LP: 0x%06x  HP: 0x%08x  MEM_SIZE: 0x%08x\n", lp, hp, MEM_SIZE);
    printf("NAME\t\t\tLEN VIS IMM  CFA\n");
    printf("-----------------------------------------------\n");
    for(cell addr = lp; addr != 0; addr = *((cell *) &(MEM[addr]))) {
        cell link = CELL_FETCH(MEM, addr);
        byte len = BYTE_FETCH(MEM, addr + CELL_SIZE) & WORD_LEN;
        byte vis = BYTE_FETCH(MEM, addr + CELL_SIZE) & MASK_VIS;
        byte imm = BYTE_FETCH(MEM, addr + CELL_SIZE) & MASK_IMM;
        byte *name = &(MEM[addr + CELL_SIZE + BYTE_SIZE]);
        cell cfa = addr + CELL_SIZE + BYTE_SIZE + len;
        //cfa += cfa % FUNC_SIZE ? FUNC_SIZE - (cfa % FUNC_SIZE) : 0;

        printf("0x%06x %.*s\t\t%02i   %c   %c   0x%06x\n",
               link, len, name, len,
               vis ? '+' : '-',
               imm ? '+' : '-',
               cfa);
    }
}

void nif(VM *vm){(void) vm;}
void nelse(VM *vm){(void) vm;}
void nthen(VM *vm){(void) vm;}

void nbegin(VM *vm){(void) vm;}
void nagin(VM *vm){(void) vm;}
void nuntil(VM *vm){(void) vm;}
void nwhile(VM *vm){(void) vm;}
void nrepeat(VM *vm){(void) vm;}

void ndo(VM *vm){(void) vm;}
void nloop(VM *vm){(void) vm;}
void nploop(VM *vm){(void) vm;}











