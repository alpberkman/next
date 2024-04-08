
#include <stdio.h>


#include "csrc/next.h"
#include "csrc/debug.h"
#include "csrc/prims.h"


int main(/*int argc, char *argv[]*/) {

    setvbuf(stdout, NULL, _IONBF, 0);

    VM vm;
    byte mem[MEM_SIZE];
    init(&vm, mem);

    info(&vm);
    puts("");

    hexdump(&vm, 8, 16);
    puts("");
    puts("");
    puts("");


    pheader(&vm, 0);

    return 0;
}