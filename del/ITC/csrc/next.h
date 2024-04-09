

#ifndef _NEXT_H
#define _NEXT_H

#include "fth.h"


#define PW(ADDR)                    print_word(vm, ADDR)
#define DEB()                       debug(vm)


void dict(VM *vm);

void debug(VM *vm);
void stacks(VM *vm);

#endif






