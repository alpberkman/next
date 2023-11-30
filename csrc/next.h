

#ifndef _NEXT_H
#define _NEXT_H

#include "fth.h"


// #define IF );nif(vm);fun(

#define MASK_VIS (1<<7)
#define MASK_IMM (1<<6)
#define WORD_LEN (31)


//#define LIT(NUM) LLIT, NUM

#define BRANCH(ADDR)    LIT(ADDR), JMP
#define BRANCH0(ADDR)   LIT(ADDR), JZ


//printf("%i\n", (sizeof((int[]){1,2,(3,x(),4),5,6})/sizeof(int)));
// When jumping back first one just marks the spot jump
// pushes the here but then how to handle the first words?


#define HEADER(NAME)    header(vm, NAME, (sizeof(NAME)-1))
#define CF(...)         cf(vm, (sizeof((func[]){__VA_ARGS__})/sizeof(func)), __VA_ARGS__)
#define PF(...)         pf(vm, (sizeof((cell[]){__VA_ARGS__})/sizeof(cell)), __VA_ARGS__)

#define PRIMS(NAME, ...)    HEADER(NAME); CF(__VA_ARGS__)
#define COLON(NAME, ...)    HEADER(NAME); CF(_nest); PF(__VA_ARGS__)

#define XPRIMS(NAME, ...)   cell NAME = PRIMS(#NAME, __VA_ARGS__)
#define XCOLON(NAME, ...)   cell NAME = COLON(#NAME, __VA_ARGS__)

//#define TOKENS(...)     tokens(vm, (sizeof((cell[]){__VA_ARGS__})/sizeof(cell)), __VA_ARGS__)



//#define CODE(...)   CF(__VA_ARGS__)
//#define COLON(...)  CF(NEXT); PF(__VA_ARGS__)
#define IMMEDIATE   BYTE_VAL(lp+CELL_SIZE) |= MASK_IMM;


#define SELF    BRANCH((lp+CELL_SIZE+BYTE_SIZE+(BYTE_VAL(lp+CELL_SIZE)&WORD_LEN)))
#define RECURSE (lp+CELL_SIZE+BYTE_SIZE+(BYTE_VAL(lp+CELL_SIZE)&WORD_LEN))

#define IF(...)     PPUSH = hp+CELL_SIZE;   PF(BRANCH0(0), __VA_ARGS__)
#define THEN(...)   CELL_VAL(PPOP) = hp;    PF(__VA_ARGS__)
#define ELSE(...)   CELL_VAL(PPOP) = hp+CELLS(3); \
                    PPUSH = hp+CELL_SIZE; \
                    PF(BRANCH(0), __VA_ARGS__)

#define BEGIN(...)  PPUSH = hp; PF(__VA_ARGS__)
#define AGAIN(...)  PF(BRANCH(PPOP), __VA_ARGS__)
#define UNTIL(...)  PF(BRANCH0(PPOP), __VA_ARGS__)
#define WHILE(...)  PPUSH = hp+CELL_SIZE; PF(BRANCH0(0), __VA_ARGS__)
#define REPEAT(...) CELL_VAL(PPOP) = hp+CELLS(3); \
                    PF(BRANCH(PPOP), __VA_ARGS__)

#define DO(...)     PPUSH = hp+CELL_SIZE; PPUSH = hp+CELLS(3); PF(LIT(0), DOI, __VA_ARGS__) // first one is leave , the second one is jumpback
#define LOOP(...)   _swap(vm); CELL_VAL(PPOP) = hp+CELLS(3); PF(LIT(PPOP), LOOPI, __VA_ARGS__)
#define PLOOP(...)  _swap(vm); CELL_VAL(PPOP) = hp+CELLS(3); PF(LIT(PPOP), PLOOPI, __VA_ARGS__)
#define UNLOOP // Not immediate
#define LEAVE  // Can be implemented as a regular word since the immediate version just compiles itself


#define INIT(VM) init(vm)


cell header(VM *vm, const char *name, int len);
void cf(VM *vm, int len, ...);
void pf(VM *vm, int len, ...);


/*
void nif(VM *vm, cell lit_addr, cell jmp_addr, cell jz);
void nelse(VM *vm);
void nthen(VM *vm);

void nbegin(VM *vm);
void nagin(VM *vm);
void nuntil(VM *vm);
void nwhile(VM *vm);
void nrepeat(VM *vm);

void ndo(VM *vm);
void nloop(VM *vm);
void nploop(VM *vm);
*/
void init(VM *vm);
void runf(VM *vm, func *fp);

#endif









