
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
    cell link = CELL_FETCH(XMEM, addr);
    byte len = BYTE_FETCH(XMEM, addr + CELL_SIZE) & WORD_LEN;
    byte vis = BYTE_FETCH(XMEM, addr + CELL_SIZE) & MASK_VIS;
    byte imm = BYTE_FETCH(XMEM, addr + CELL_SIZE) & MASK_IMM;
    byte *name = &(BYTE_FETCH(XMEM, addr + CELL_SIZE + BYTE_SIZE));
    cell cfa = addr + CELL_SIZE + BYTE_SIZE + len;

    printf("%.*s ", len, name);

}

void pheader(VM *vm, cell addr) {
    cell link = CELL_FETCH(XMEM, addr);
    byte len = BYTE_FETCH(XMEM, addr + CELL_SIZE) & WORD_LEN;
    byte vis = BYTE_FETCH(XMEM, addr + CELL_SIZE) & MASK_VIS;
    byte imm = BYTE_FETCH(XMEM, addr + CELL_SIZE) & MASK_IMM;
    byte *name = &(BYTE_FETCH(XMEM, addr + CELL_SIZE + BYTE_SIZE));
    cell cfa = addr + CELL_SIZE + BYTE_SIZE + len;

    printf("0x%06x %.*s%*s %02i   %c   %c   0x%06x | ",
               link, 
               len, name, 
               16-len, "",
               len,
               vis ? '+' : '-',
               imm ? '+' : '-',
               cfa);
}
