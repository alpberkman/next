
#include "debug.h"
#include "../prims.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>


void pstack(cell *s, cell p, char *sname, char *fstr) {
    printf("%s<%i> ", sname, p);
    for(int i = 0; i < p; ++i)
        printf(fstr, s[i]);
}
void stacks(VM *vm) {
    printf("SPU:\n");
    pstack(XPS, XPSP, "PS", "%i ");
    puts("");
    pstack(XRS, XRSP, "RS", "%i ");
    puts("");
}

char *enum2s(mca p) {
    char *names[] = {TABLE(XENUMNAME)};
    mca keys[] = {TABLE(XENUM)};
    for(unsigned int i = 0; i < sizeof(keys)/sizeof(keys[0]); ++i)
        if(p == keys[i])
            return names[i];
    return NULL;
}
char *func2s(func f) {
    char *names[] = {TABLE(XFUNCNAME)};
    func keys[] = {TABLE(XFUNC)};
    for(unsigned int i = 0; i < sizeof(keys)/sizeof(keys[0]); ++i)
        if(f == keys[i])
            return names[i];
    return NULL;
}
void penum2func(void) {
    char *enames[] = {TABLE(XENUMNAME)};
    char *fnames[] = {TABLE(XFUNCNAME)};
    mca keys[] = {TABLE(XENUM)};

    for(unsigned int i = 0; i < sizeof(keys)/sizeof(keys[0]); ++i)
        printf("0x%02x: %-6s <---> %7s\n", keys[i], enames[i], fnames[i]);
}

void hexdump(VM *vm, int rlen, int clen) {
    for(int i = 0; i < clen; ++i) {
        printf("0x%04x: ", i*rlen);
        for(int j = 0; j < rlen; ++j) {
            if(j%8 == 0 && j != 0)
                printf(" ");
            printf("%02x ", BYTE_FETCH(XMEM, i*rlen + j));
        }
        printf(" ");
        for(int j = 0; j < rlen; ++j) {
            char c = BYTE_FETCH(XMEM, i*rlen + j);
            if(j%8 == 0 && j != 0)
                printf(" ");
            printf("%c", isprint(c) ? c : '.');
        }
        puts("");
    }
}

