
#ifndef _DEBUG_H
#define _DEBUG_H

#include "vm.h"

extern cell hp;
extern cell lp;

#define WORD_DISASM(ADDR) \
    cell link = CELL_FETCH(XMEM, ADDR); \
    byte len = BYTE_FETCH(XMEM, ADDR + CELL_SIZE) & WORD_LEN; \
    byte vis = BYTE_FETCH(XMEM, ADDR + CELL_SIZE) & MASK_VIS; \
    byte imm = BYTE_FETCH(XMEM, ADDR + CELL_SIZE) & MASK_IMM; \
    byte *name = &(BYTE_FETCH(XMEM, ADDR + CELL_SIZE + BYTE_SIZE)); \
    cell cfa = ADDR + CELL_SIZE + BYTE_SIZE + len;

void pstack(cell *s, cell p, char *sname, char *fstr);
void stacks(VM *vm);
void info(VM *vm);
void stat(VM *vm);

char *enum2s(byte p);
char *func2s(func f);

void penum2func(void);

void hexdump(VM *vm, int rlen, int clen);

void pword(VM *vm, cell addr);
void pheader(VM *vm, cell addr);
void pwords(VM *vm);
void disasm(VM *vm, cell addr, cell limit);

#endif

