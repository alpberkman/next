
#include "debug.h"
#include "prims.h"

#include <ctype.h>
#include <stdio.h>



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

void info(VM *vm) {
    printf("VM info: 0x%p\n", vm);
    puts("");

    penum2func();
    puts("");

    stat(vm);
    puts("");

    pwords(vm);
    puts("");

    stacks(vm);
    puts("");
}

void stat(VM *vm) {
    printf("ITC:\n");
    printf("p: %s\n", XP == FALSE ? "off" : "on");
    printf("ip: 0x%08x\n", XIP);
    printf("wp: 0x%08x\n", XWP);

    puts("");

    printf("MEM:\n");
    if(XMEM == NULL)
        printf("mem: NULL\n");
    else
        printf("mem: 0x%p\n", XMEM);
}


char *enum2s(byte p) {
    char *names[] = {TABLE(XENUMNAME)};
    byte keys[] = {TABLE(XENUM)};
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
    byte keys[] = {TABLE(XENUM)};

    for(unsigned int i = 0; i < sizeof(keys)/sizeof(keys[0]); ++i)
        printf("0x%02x: %-6s <---> %7s\n", keys[i], enames[i], fnames[i]);
}

void hexdump(VM *vm, int rlen, int clen) {
    for(int i = 0; i < clen; ++i) {
        printf("0x%04x: ", i*rlen);
        for(int j = 0; j < rlen; ++j)
            printf("%02x ", BYTE_FETCH(XMEM, i*rlen + j));
        for(int j = 0; j < rlen; ++j) {
            char c = BYTE_FETCH(XMEM, i*rlen + j);
            printf("%c", isprint(c) ? c : '.');
        }
        puts("");
    
    }
}

void pword(VM *vm, cell addr) {
    WORD_DISASM(addr);
    printf("%.*s ", len, name);

}

void pheader(VM *vm, cell addr) {
    WORD_DISASM(addr);
    printf("0x%06x: 0x%06x %.*s%*s %02i   %c   %c   0x%06x | ",
        addr,
        link, 
        len, name, 
        16-len, "",
        len,
        vis ? '+' : '-',
        imm ? '+' : '-',
        cfa);
}

void pwords(VM *vm) {
    cell start = lp;
    cell end = hp;
    for(;;) {
        pheader(vm, start);
        printf("from 0x%06x to 0x%06x ", start, end);
        disasm(vm, start);
        puts("");
        if(start == 0)
            break;
        end = start;
        start = CELL_FETCH(XMEM, start);
    }
}

void disasm(VM *vm, cell addr) {
    WORD_DISASM(addr);
    for(;;) {
        printf("%s ", enum2s(BYTE_FETCH(XMEM, cfa)));
        if(BYTE_FETCH(XMEM, cfa) == NEXT || BYTE_FETCH(XMEM, cfa) == NEST)
            break;
        cfa += BYTE_SIZE;
    }
}