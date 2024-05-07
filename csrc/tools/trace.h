

#ifndef _TRACE_H
#define _TRACE_H

#include "../vm.h"

// Inspect p
void tword(VM *vm, cell p);
// Print trace
void ptrace(VM *vm);
// Run the VM with ptrace starting from addr
void trace(VM *vm, cell addr);


#endif