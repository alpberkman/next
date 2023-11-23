

#include "next.h"


#define MASK_VIS (1<<7)
#define MASK_IMM (1<<6)
#define WORD_LEN (31)


#define HEADER(NAME) header(vm, NAME, (sizeof(NAME)-1))
#define CODE(...) code(vm, (sizeof((int[]){__VA_ARGS__})/sizeof(int)), __VA_ARGS__)
#define COLON(...) colon(vm, (sizeof((int[]){__VA_ARGS__})/sizeof(int)), __VA_ARGS__)
#define IMMEDIATE immediate(vm)

#define INIT(VM) init(vm)


int header(VM *vm, const char *name, int len);
void code(VM *vm, int len, ...);
void colon(VM *vm, int len, ...);
void immediate(VM *vm);


void init(VM *vm);
