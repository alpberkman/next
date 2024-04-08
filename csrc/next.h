

#ifndef _NEXT_H
#define _NEXT_H

#include "vm.h"


#define PW(ADDR)                    print_word(vm, ADDR)
#define DEB()                       debug(vm)


void dict(VM *vm);

void debug(VM *vm);
void stacks(VM *vm);

#endif






