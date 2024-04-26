

#ifndef _NEXT_H
#define _NEXT_H

#include "vm.h"


byte *falloc(void);
// Allocate MEM_SIZE bytes of memory

void dict(VM *vm);
// Initialize the vm's memory

byte *setup(VM *vm);
// Allocate memory for the vm, initialize it and return a pointer to the allocated memory

#endif






