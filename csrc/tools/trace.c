

#include "trace.h"
#include "disasm.h"
#include "debug.h"
#include "../prims.h"

#include <stdio.h>


void tword(FTH *fth, cell p) {
    LOCATE_DISASM(p);
    printf("%.*s", len, name);

    if(p == XIP) {
        if(MCA_FETCH(XMEM, XIP) == LIT || STREQ(name, "DOVAR", len) || STREQ(name, "DOCON", len)) {
            printf(" (0x%x | %i)", CELL_FETCH(XMEM, XWP), CELL_FETCH(XMEM, XWP));
        } else if(STREQ(name, "IRJMP", len) || STREQ(name, "IRJZ", len)) {
            printf(" (0x%x)", CELL_FETCH(XMEM, XWP));
        } else if(STREQ(name, "[IF]", len) || STREQ(name, "[ELSE]", len)) {
            printf(" (0x%x)", CELL_FETCH(XMEM, XWP));
        } else if(STREQ(name, "[BEGIN]", len) || STREQ(name, "[AGAIN]", len)) {
            printf(" (0x%x)", CELL_FETCH(XMEM, XWP));
        } else if(STREQ(name, "UNTIL", len)) {
            printf(" (0x%x)", CELL_FETCH(XMEM, XWP));
        } else if(STREQ(name, "[WHILE]", len) || STREQ(name, "[REPEAT]", len)) {
            printf(" (0x%x)", CELL_FETCH(XMEM, XWP));
        } else if(STREQ(name, "[DO]", len) || STREQ(name, "[+LOOP]", len)) {
            printf(" (0x%x)", CELL_FETCH(XMEM, XWP));
        } else if(STREQ(name, "DOSTR", len)) {
            printf(" (%i: \"%.*s\")", CELL_FETCH(XMEM, XWP), CELL_FETCH(XMEM, XWP), &BYTE_FETCH(XMEM, XWP+CELL_SIZE));
        } else if(STREQ(name, "CALL", len)) {
            printf(" %p", FUNC_FETCH(XMEM, XWP));
        }
    }
}

void ptrace(FTH *fth) {
    if(DEBUG_ENABLE(2, DEBUG_ENABLE(1, XWP != 0) && MCA_FETCH(XMEM, XIP) != NEXT)) {

        if(DEBUG_ENABLE(4, 0)) {
            for(int i = 0; i < XRSP*2-1+20; ++i)
                printf(" ");
            pstack(XPS, XPSP, "P-Stack", "%i ");
            puts("");
            for(int i = 0; i < XRSP*2-1+20; ++i)
                printf(" ");
            pstack(XRS, XRSP, "R-Stack", "%i ");
            puts("");
        }

        printf("%4x %4x | %-7s: ", XIP, XWP, enum2s(MCA_FETCH(XMEM, XIP)));
        for(int i = 0; i < XRSP-1; ++i) printf("  ");

        tword(fth, XWP);
        printf(": ");
        tword(fth, XIP);

        puts("");
    }
}
void trace(FTH *fth, cell addr) {
    rund(fth, addr, ptrace);
}