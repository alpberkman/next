

#include <stdio.h>

#include "csrc/next.h"
//#include "csrc/debug.h"


int main(/*int argc, char *argv[]*/) {

        setvbuf(stdout, NULL, _IONBF, 0);

        VM vm;
        init(&vm, NULL);
        dict(&vm);

        //info(&vm);
        //puts("");

        //hexdump(&vm, 16, 32);
        //puts("");
        //puts("");
        //puts("");

    return 0;
}
