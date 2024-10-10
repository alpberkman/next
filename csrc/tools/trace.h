

#ifndef _TRACE_H
#define _TRACE_H

#include "../core.h"

// Inspect p
void tword(FTH *fth, cell p);
// Print trace
void ptrace(FTH *fth);
// Run the FTH with ptrace starting from addr
void trace(FTH *fth, cell addr);


#endif