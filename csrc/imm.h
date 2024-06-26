

#ifndef _IMM_H
#define _IMM_H

#include "vm.h"


extern cell hp;
extern cell lp;

// Macros to add primitive and colon words 
#define HEADER(NAME)                header(vm, NAME, (sizeof(NAME)-1))
#define CF(...)                     cf(vm, (sizeof((mca[]){__VA_ARGS__})/sizeof(mca)), (mca[]){__VA_ARGS__})
#define PF(...)                     pf(vm, (sizeof((cell[]){__VA_ARGS__})/sizeof(cell)), (cell[]){__VA_ARGS__})

#define PRIMS(NAME, ...)            HEADER(NAME); CF(__VA_ARGS__)
#define COLON(NAME, ...)            HEADER(NAME); CF(NEST); PF(__VA_ARGS__)

#define XPRIMS(NAME, ...)           cell NAME = PRIMS(#NAME, __VA_ARGS__)
#define XCOLON(NAME, ...)           cell NAME = COLON(#NAME, __VA_ARGS__)
#define YPRIMS(NAME, ENTRY, ...)    cell NAME = PRIMS(ENTRY, __VA_ARGS__)
#define YCOLON(NAME, ENTRY, ...)    cell NAME = COLON(ENTRY, __VA_ARGS__)
#define ZPRIMS(NAME, ...)           cell P_##NAME = PRIMS(#NAME, __VA_ARGS__)
#define ZCOLON(NAME, ...)           cell P_##NAME = COLON(#NAME, __VA_ARGS__)
#define IMMEDIATE                   BYTE_FETCH(XMEM, lp+CELL_SIZE) |= MASK_IMM


// Variable and constant macros
#define XVAR(NAME)                  XCOLON(NAME, dovar, 0)
#define XCON(NAME, VAL)             XCOLON(NAME, docon, (VAL))
#define YVAR(NAME, ENTRY)           YCOLON(NAME, ENTRY, dovar, 0)
#define YCON(NAME, ENTRY, VAL)      YCOLON(NAME, ENTRY, docon, (VAL))


// Creates a word called cold to reset the vm
#define COLD(...)   \
    { \
        int old_hp, old_lp; \
        int new_hp, new_lp; \
        new_hp = 0; \
        new_lp = 0; \
        old_hp = hp; \
        old_lp = lp; \
        XCOLON(c0ld, __VA_ARGS__); \
        runc(vm, c0ld); \
        new_hp = hp; \
        new_lp = lp; \
        hp = old_hp; \
        lp = old_lp; \
        XCOLON(cold, __VA_ARGS__); \
        runc(vm, cold); \
    }

// Macros for words that might be used in interpreter mode while compiling other words
#define ALLOT(N)                    hp+=(N)
#define STR(X)                      PF(dostr, sizeof(X)-1); str(vm, sizeof(X)-1, (byte *) X)
#define CCALL(X)                    PF(call); FUNC_FETCH(XMEM, hp) = (X); hp += FUNC_SIZE
//#define RECURSE {WORD_DISASM(lp);  PF(ijmp, cfa+1);}
#define RECURSE                     PF(ijmp, lp + CELL_SIZE + BYTE_SIZE + (BYTE_FETCH(XMEM, lp + CELL_SIZE) & WORD_LEN) + MCA_SIZE)
#define POSTPONE(XT)                PF(lit, XT, comma)
#define POSTPONEI(XT)               PF(XT)

#define ON true, swap, strc
#define OFF false, swap, strc
#define TOGGLE lit, 0, eq

// Control flow macros
#define IF(...)             PF(pif);    next_if(vm);    PF(__VA_ARGS__)
#define THEN(...)           PF(pthen);  next_then(vm);  PF(__VA_ARGS__)
#define ELSE(...)           PF(pelse);  next_else(vm);  PF(__VA_ARGS__)

#define BEGIN(...)          PF(pbegin); next_begin(vm); PF(__VA_ARGS__)
#define AGAIN(...)          PF(pagain); next_agin(vm);  PF(__VA_ARGS__)
#define UNTIL(...)          PF(puntil); next_until(vm); PF(__VA_ARGS__)
#define WHILE(...)          PF(pwhile); next_while(vm); PF(__VA_ARGS__)
#define REPEAT(...)         PF(prepeat); next_repeat(vm); PF(__VA_ARGS__)

#define DO(...)             PF(pdo);    next_do(vm);    PF(__VA_ARGS__)
#define LOOP(...)           PF(lit, 1); PLOOP(__VA_ARGS__)
#define PLOOP(...)          PF(pploop); next_ploop(vm); PF(__VA_ARGS__)


// Utility macros
#define PSWAP \
    { \
        cell tmp1 = PPOP; \
        cell tmp2 = PPOP; \
        PPUSH = tmp1; \
        PPUSH = tmp2; \
    }

#define HERE            PPUSH=hp
#define CELL_ALLOT      hp+=CELL_SIZE
#define HERE_CELL_ALLOT HERE; CELL_ALLOT
#define HERE_SWAP_STORE CELL_FETCH(XMEM, PPOP) = hp
#define APPEND(X)       CELL_FETCH(XMEM, hp) = (X); hp += CELL_SIZE;


cell header(VM *vm, const char *name, int len);
void cf(VM *vm, int len, mca *args);
void pf(VM *vm, int len, cell *args);


void next_if(VM *vm);
void next_then(VM *vm);
void next_else(VM *vm);

void next_begin(VM *vm);
void next_agin(VM *vm);
void next_until(VM *vm);
void next_while(VM *vm);
void next_repeat(VM *vm);

void next_do(VM *vm);
void next_ploop(VM *vm);


void str(VM *vm, int len, byte *args);

//cell find_word(VM *vm, char *c);
//cell find_addr(VM *vm, cell cfa);
//cell print_word(VM *vm, cell addr);

#endif






