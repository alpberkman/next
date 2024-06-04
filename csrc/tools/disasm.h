

#ifndef _DISASM_H
#define _DISASM_H

#include "../vm.h"

extern cell hp;
extern cell lp;


#define STREQ(X, Y, N) (strlen((char*)(Y)) == (N) && 0 == strncmp((char*)(X), (char*)(Y), (N)))

// Given the address of a link field, disassembles a words's fields
#define HEADER_DISASM(ADDR) \
    cell link = CELL_FETCH(XMEM, ADDR); \
    byte len = BYTE_FETCH(XMEM, ADDR + CELL_SIZE) & WORD_LEN; \
    byte vis = BYTE_FETCH(XMEM, ADDR + CELL_SIZE) & MASK_VIS; \
    byte imm = BYTE_FETCH(XMEM, ADDR + CELL_SIZE) & MASK_IMM; \
    byte *name = &(BYTE_FETCH(XMEM, ADDR + CELL_SIZE + BYTE_SIZE)); \
    cell cfa = ADDR + CELL_SIZE + BYTE_SIZE + len; \
    cell pfa = find_pfa(vm, cfa)

#define LOCATE(ADDR) \
    cell start, end; \
    locate(vm, (ADDR), &start, &end)

#define LOCATE_DISASM(ADDR) \
    cell start, end; \
    locate(vm, (ADDR), &start, &end); \
    HEADER_DISASM(start)

// Locates the word where the addr belongs to
// Sets start to address of the link field
// and end to the previous link field
void locate(VM *vm, cell addr, cell *start, cell *end);

// Given cfa of a word, returns the pfa
// Assumes all cfs end with NEXT, NEST or UNNEST
// Assumes they only come up once
cell find_pfa(VM *vm, cell cfa);

// Checks whether addr points to the word which has the name target
int wordeq(VM *vm, cell addr, char *target);

// Prints a primitive/word, returns it's length, changes the value of addr
// depending on how much was read
int pword(VM *vm, cell *addr);
int pprim(VM *vm, cell *addr);
// Prints every section in the header
void pheader(VM *vm, cell addr);

// Prints primitives/words starting from cfa/pfa until the end
void disasm_cf(VM *vm, cell cfa, cell end);
void disasm_pf(VM *vm, cell pfa, cell end);
// Disassembles a word including header, cf and pf
void disasmw(VM *vm, cell addr);
// Disassembles every word in the dictionary
void disasmd(VM *vm);

// Tries to recreate source code in reverse order
void regen(VM *vm, cell addr);

#endif



