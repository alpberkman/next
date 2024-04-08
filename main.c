
#include <stdio.h>


#include "csrc/next.h"
#include "csrc/debug.h"
#include "csrc/prims.h"


int main(int argc, char *argv[]) {

    setvbuf(stdout, NULL, _IONBF, 0);

    VM vm;
    init(&vm, NULL);
    info(&vm);


    puts("");



    return 0;
}