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
    x.ram = mem;
    init(vm);

    stacks(vm);

    XPRIMS(UNNEST, _unnest);
    XPRIMS(HALT, _halt);
    XPRIMS(LIT, _lit, _next);
    XPRIMS(EXE, _exe);
    XPRIMS(t1, (cell)_tru, (cell)_tru, (cell)_next);

    XCOLON(t2, t1, t1, UNNEST);
    XCOLON(m, t2, LIT, 123, LIT, t1, EXE, t1, HALT);

    for(unsigned long int i = 0; i < sizeof(mem)/sizeof(cell); ++i)
        printf("0x%016llx\n", ((cell *) RAM)[i]);

    runf(vm, (func *)m);
    stacks(vm);

    return 0;
}

