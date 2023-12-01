

#include "next.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>


cell hp;
cell lp;


void runf(VM *vm, cell addr) {
    runc(&DTC, MEM, vm, addr);
}
void init(VM *vm) {

    hp = 0;
    lp = 0;

    FP = 0;
    TP = 0;

    PSP = 0;
    RSP = 0;

    XPRIMS(XXX, _next);

    XPRIMS(NOP, _next);
    XPRIMS(UNNEST, _unnest);
    XPRIMS(HALT, _halt);
    IMMEDIATE;
    XPRIMS(LIT, _lit, _next);
    XPRIMS(EXE, _exe);
    XPRIMS(t1, _tru, _tru, _next);

    XCOLON(t2, t1, t1, UNNEST);
    XCOLON(m, t2, LIT, 123, LIT, t1, EXE, t1, HALT);

    runf(vm, m);






    PF(LIT, IF ( HALT);

}

cell header(VM *vm, const char *name, int len) {
    *((cell *) &(MEM[hp])) = lp;
    lp = hp;
    hp += CELL_SIZE;

    *((byte *) &(MEM[hp])) = MASK_VIS | len;
    hp += BYTE_SIZE;

    for(int i = 0; i < len; ++i)
        ((byte *) &(MEM[hp]))[i] = (byte) toupper(name[i]);
    hp += len*BYTE_SIZE;

    return hp;
}
void cf(VM *vm, int len, ...) {
    va_list l;
    va_start(l, len);

    for(int i = 0; i < len; ++i)
        ((func *) &(MEM[hp]))[i] = (func) va_arg(l, func);
    hp += len*FUNC_SIZE;

    va_end(l);
}
void pf(VM *vm, int len, ...) {
    va_list l;
    va_start(l, len);

    for(int i = 0; i < len; ++i)
        ((cell *) &(MEM[hp]))[i] = (cell) va_arg(l, cell);
    hp += len*CELL_SIZE;

    va_end(l);
}

void debug(VM *vm) {
    printf("NAME        LEN VIS IMM\n");
    printf("-----------------------\n");
    for(cell addr = lp; addr != 0; addr = *((cell *) &(MEM[addr]))) {
        cell link = *((cell *) &(MEM[addr]));
        byte len = *((byte *) &(MEM[addr + CELL_SIZE])) & WORD_LEN;
        byte vis = *((byte *) &(MEM[addr + CELL_SIZE])) & MASK_VIS;
        byte imm = *((byte *) &(MEM[addr + CELL_SIZE])) & MASK_IMM;
        byte *name = ((byte *) &(MEM[addr + CELL_SIZE + BYTE_SIZE]));

        printf("0x%08llx %.*s %02i   %c   %c\n",
               link, len, name, len,
               vis ? '+' : '-',
               imm ? '+' : '-');
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











