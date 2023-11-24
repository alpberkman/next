

#include "next.h"


#define MASK_VIS (1<<7)
#define MASK_IMM (1<<6)
#define WORD_LEN (31)


#define MLIT(NUM) LIT, NUM

#define MIF
#define MELSE
#define MTHEN

//printf("%i\n", (sizeof((int[]){1,2,(3,x(),4),5,6})/sizeof(int)));
// When jumping back first one just marks the spot jump
// pushes the here but then how to handle the first words?


#define HEADER(NAME) header(vm, NAME, (sizeof(NAME)-1))
#define CODE(...) code(vm, (sizeof((int[]){__VA_ARGS__})/sizeof(int)), __VA_ARGS__)
#define COLON(...) CODE(NEXT); colon(vm, (sizeof((int[]){__VA_ARGS__})/sizeof(int)), __VA_ARGS__)
#define IMMEDIATE immediate(vm)

#define BRANCH
#define BRANCH0

#define SELF
#define RECURSE

#define IF(...)     nif(vm);    colon(vm, (sizeof((int[]){__VA_ARGS__})/sizeof(int)), __VA_ARGS__)
#define ELSE(...)   nelse(vm);  colon(vm, (sizeof((int[]){__VA_ARGS__})/sizeof(int)), __VA_ARGS__)
#define THEN(...)   nthen(vm);  colon(vm, (sizeof((int[]){__VA_ARGS__})/sizeof(int)), __VA_ARGS__)

#define BEGIN
#define AGAIN
#define UNTIL
#define WHILE
#define REPEAT

#define DO
#define LOOP
#define PLOOP
#define UNLOOP // Not immediate
#define LEAVE  // Can be implemented as a regular word since the immediate version just compiles itself

#define INIT(VM) init(vm)


int header(VM *vm, const char *name, int len);
void code(VM *vm, int len, ...);
void colon(VM *vm, int len, ...);
void immediate(VM *vm);

void nif(VM *vm);
void nelse(VM *vm);
void nthen(VM *vm);

//void (VM *vm, int len, ...);
//void (VM *vm, int len, ...);




void init(VM *vm);
