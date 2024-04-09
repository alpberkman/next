
#include <stdio.h>


#include "csrc/next.h"
#include "csrc/debug.h"
#include "csrc/prims.h"


int main(/*int argc, char *argv[]*/) {

    setvbuf(stdout, NULL, _IONBF, 0);

    VM vm;
    setup(&vm);

    info(&vm);
    puts("");

    hexdump(&vm, 16, 32);
    puts("");
    puts("");
    puts("");


    return 0;
}