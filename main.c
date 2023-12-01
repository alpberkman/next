#include <stdio.h>
#include <stdlib.h>

#define streq(X, Y) (strcmp((X), (Y)) == 0)
#define pint(X) printf("%li\n", X)

#include "csrc/next.h"
//#include "csrc/init.h"


void stacks(VM *vm) {
    printf("P<%i> ", vm->spu.psp);
    for(int i = 0; i < vm->spu.psp; ++i)
        printf("%lli ", vm->spu.ps[i]);
    puts("");

    printf("R<%i> ", vm->spu.rsp);
    for(int i = 0; i < vm->spu.rsp; ++i)
        printf("%llx ", vm->spu.rs[i]);
    puts("");
}

int main(/*int argc, char *argv[]*/) {

    VM x;
    VM *vm = &x;
    byte mem[1024] = {0};
    x.mem = mem;
    init(vm);

    stacks(vm);




    for(unsigned long int i = 0; i < sizeof(mem)/sizeof(cell); ++i)
        printf("0x%016llx\n", ((cell *) mem)[i]);

    stacks(vm);
    debug(vm);

    return 0;
}

