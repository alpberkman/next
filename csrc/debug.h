
#ifndef _DEBUG_H
#define _DEBUG_H

#include "vm.h"


void pstack(cell *s, cell p, char *sname, char *fstr);
void stacks(VM *vm);
void info(VM *vm);
void stat(VM *vm);

char *enum2s(byte p);
char *func2s(func f);

void penum2func(void);

#endif

