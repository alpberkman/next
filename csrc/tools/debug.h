
#ifndef _DEBUG_H
#define _DEBUG_H

#include "../vm.h"
#include "trace.h"
#include "disasm.h"

#include <string.h>



extern cell hp;
extern cell lp;


#define NO 0
#define MINIMAL 1
#define MINIMAL_PLUS 2
#define VERBOSE 3
#define EXTREME 4


// If debug level is high enough then true else whatever B is
#define DEBUG_ENABLE(A, B) ((DEBUG_LEVEL >= (A)) || (B))  
// Same as DEBUG_ENABLE but use v or V instead
// Ex: DEBUG_ENABLE(vVv, flag)
#define DEBUG_VERBOSE(A, B) ((DEBUG_LEVEL >= (strspn(#A"", "vV"))) || (B))


// Dump all words
#define HEXDUMP hexdump(vm, 16, (hp | 0xf)/16 + 1);

// Wrapper for debug runs 
#define DR(X) reset(vm); trace(vm, (X)); stacks(vm); puts("")


// Prints a given stack
void pstack(cell *s, cell p, char *sname, char *fstr);
// Prints both stacks
void stacks(VM *vm);

// Prints enum and function name pairs
void penum2func(void);
// Returns a string that represents an enum's name
char *enum2s(mca p);
// Returns a string that represents a function's name
char *func2s(func f);

// Dumps the memory contents, both in hex and if printable using chars
// rlen: length of rows
// clen: length of columns
void hexdump(VM *vm, int rlen, int clen);


#endif

