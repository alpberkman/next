

#ifndef _IMM_H
#define _IMM_H

#include "fth.h"

extern cell hp;
extern cell lp;


#define MASK_VIS (1<<7)
#define MASK_IMM (1<<6)
#define WORD_LEN (31)


#define HEADER(NAME)        header(vm, NAME, (sizeof(NAME)-1))
#define CF(...)             cf(vm, (sizeof((func[]){__VA_ARGS__})/sizeof(func)), __VA_ARGS__)
#define PF(...)             pf(vm, (sizeof((cell[]){__VA_ARGS__})/sizeof(cell)), __VA_ARGS__)

#define PRIMS(NAME, ...)    HEADER(NAME); CF(__VA_ARGS__)
#define COLON(NAME, ...)    HEADER(NAME); CF(_nest); PF(__VA_ARGS__)

#define XPRIMS(NAME, ...)           cell NAME = PRIMS(#NAME, __VA_ARGS__)
#define XCOLON(NAME, ...)           cell NAME = COLON(#NAME, __VA_ARGS__)
#define YPRIMS(NAME, ENTRY, ...)    cell NAME = PRIMS(ENTRY, __VA_ARGS__)
#define YCOLON(NAME, ENTRY, ...)    cell NAME = COLON(ENTRY, __VA_ARGS__)
#define IMMEDIATE                   BYTE_FETCH(MEM, lp+CELL_SIZE) |= MASK_IMM


#define XCONST(NAME, X)             XCOLON(NAME, LIT, X, UNNEST)
#define XVAR(NAME)                  XCOLON(NAME, LIT, hp+CELLS(3), UNNEST, 0)
#define YCONST(NAME, ENTRY, X)      YCOLON(NAME, ENTRY, LIT, X, UNNEST)
#define YVAR(NAME, ENTRY)           YCOLON(NAME, ENTRY, LIT, hp+CELLS(3), UNNEST, 0)
#define STR(S)                      PF(asdf); next_str(vm, s)
#define ALLOT(N)                    hp+=(N)

#define IF(...)             next_if(vm);        PF(__VA_ARGS__)
#define THEN(...)           next_then(vm);      PF(__VA_ARGS__)
#define ELSE(...)           next_else(vm);      PF(__VA_ARGS__)

#define BEGIN(...)          next_begin(vm);     PF(__VA_ARGS__)
#define AGAIN(...)          next_agin(vm);      PF(__VA_ARGS__)
#define UNTIL(...)          next_until(vm);     PF(__VA_ARGS__)
#define WHILE(...)          next_while(vm);     PF(__VA_ARGS__)
#define REPEAT(...)         next_repeat(vm);    PF(__VA_ARGS__)

#define DO(...)             next_do(vm);        PF(__VA_ARGS__)
#define LOOP(...)           next_loop(vm);      PF(__VA_ARGS__)
#define PLOOP(...)          next_ploop(vm);     PF(__VA_ARGS__)


#define FW(W)                       find_word(vm, #W)
#define FA(ADDR)                    find_addr(vm, ADDR)


cell header(VM *vm, const char *name, int len);
void cf(VM *vm, int len, ...);
void pf(VM *vm, int len, ...);


//void next_constant(VM *vm, cell c);
//void next_variable(VM *vm);
void next_str(VM *vm, char *c);

void next_if(VM *vm);
void next_then(VM *vm);
void next_else(VM *vm);

void next_begin(VM *vm);
void next_agin(VM *vm);
void next_until(VM *vm);
void next_while(VM *vm);
void next_repeat(VM *vm);

void next_do(VM *vm);
void next_loop(VM *vm);
void next_ploop(VM *vm);


cell find_word(VM *vm, char *c);
cell find_addr(VM *vm, cell cfa);
cell print_word(VM *vm, cell addr);

#endif






