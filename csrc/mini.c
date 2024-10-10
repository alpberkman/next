
#include "imm.h"
#include "prims.h"

#include "mini.h"

#include "tools/debug.h"
#include <stdio.h>

void dict(FTH *fth) {
    //(void) fth;
    hp =  0;
    lp = -1;

    PRIMS("NEXT", NEXT);



    hexdump(fth, 16, (hp | 0xf)/16 + 1);
    puts("");
    disasmd(fth);
    puts("");
}