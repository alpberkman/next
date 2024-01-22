#include <stdio.h>
#include <stdlib.h>

#define streq(X, Y) (strcmp((X), (Y)) == 0)
#define pint(X) printf("%li\n", X)

#include "csrc/fth.h"
#include "csrc/next.h"



int main(/*int argc, char *argv[]*/) {

    setvbuf(stdout, NULL, _IONBF, 0);

    VM vm;
    init(&vm, NULL);
    dict(&vm);
    debug(&vm);

    runf(&vm, 0x21);
    stacks(&vm);

    return 0;
}
