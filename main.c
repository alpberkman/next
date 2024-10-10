

#include <stdio.h>

#include "csrc/mini.h"
//#include "csrc/debug.h"


int main(/*int argc, char *argv[]*/) {

        setvbuf(stdout, NULL, _IONBF, 0);

        FTH fth;
        init(&fth);
        dict(&fth);

        //info(&vm);
        //puts("");

        //hexdump(&vm, 16, 32);
        //puts("");
        //puts("");
        //puts("");

    return 0;
}
