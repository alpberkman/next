#include <stdio.h>
#include <stdlib.h>

#define streq(X, Y) (strcmp((X), (Y)) == 0)
#define pint(X) printf("%li\n", X)

#include "csrc/next.h"
#include "csrc/init.h"
int main(/*int argc, char *argv[]*/) {

    VM x;
    x.spu.psp = 0;
    x.spu.rsp = 0;
    byte mem[] = {
        NEST, 11, 0, 5, 0,
        HALT,//5
        UNNEST,//6
        LIT, NEXT,//7
        ADD, NEXT,//9
        NEST,
            7, 0, 3, 0,
            7, 0, 1, 0,
            9, 0,
        6, 0,

        TRU, FLS, MEM, HALT,
        NEST, 8, 24, 40,
        TRU, TRU, NOP, NEXT,
        HALT, NOP, NOP, NOP,
        TRU, NEST, 8, 32,
        UNNEST, NOP, NOP , NOP,
        TRU, TRU, HALT,
    };
    x.ram = (byte *) mem;
    run(&x);

    int arr[32] = {[12] = 123,};

    pint(sizeof(LUT)/sizeof(fun));
    return 0;
}
