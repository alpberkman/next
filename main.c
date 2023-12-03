#include <stdio.h>
#include <stdlib.h>

#define streq(X, Y) (strcmp((X), (Y)) == 0)
#define pint(X) printf("%li\n", X)

#include "csrc/next.h"
//#include "csrc/init.h"


void stacks(VM *vm) {
    printf("P<%i> ", vm->spu.psp);
    for(int i = 0; i < vm->spu.psp; ++i)
        printf("%i ", vm->spu.ps[i]);
    puts("");

    printf("R<%i> ", vm->spu.rsp);
    for(int i = 0; i < vm->spu.rsp; ++i)
        printf("%x ", vm->spu.rs[i]);
    puts("");
}

int main(/*int argc, char *argv[]*/) {

    VM vm;
    init(&vm);
    stacks(&vm);

    return 0;
}

