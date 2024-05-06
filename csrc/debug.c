
#include "debug.h"
#include "prims.h"

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

void info(VM *vm) {
    printf("VM info: 0x%p\n", vm);
    puts("");

    penum2func();
    puts("");

    stat(vm);
    puts("");

    hexdump(vm, 16, (hp | 0xf)/16 + 1);
    puts("");

    pwords(vm);
    puts("");

    stacks(vm);
    puts("");
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
        for(int j = 0; j < rlen; ++j) {
            if(j%8 == 0 && j != 0)
                printf(" ");
            printf("%02x ", BYTE_FETCH(XMEM, i*rlen + j));
        }
        for(int j = 0; j < rlen; ++j) {
            char c = BYTE_FETCH(XMEM, i*rlen + j);
            if(j%8 == 0 && j != 0)
                printf(" ");
            printf("%c", isprint(c) ? c : '.');
        }
        puts("");
    }
}

void pword(VM *vm, cell addr) {
    WORD_DISASM(addr);
    printf("%.*s", len, name);

}

void pheader(VM *vm, cell addr) {
    WORD_DISASM(addr);
    printf("0x%06x: 0x%08x %.*s%*s %2i   %c   %c  0x%06x ",
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
    printf("%-10s%-11s%-17s%-4s%-4s%-4s%-9s%-24s%-26s%s\n",
           "addr",
           "link",
           "name",
           "len",
           "vis",
           "imm",
           "cfa",
           "space",
           "cf",
           "pf"
          );
    cell start = lp;
    cell end = hp;
    for(;;) {
        pheader(vm, start);
        printf("[ 0x%06x - 0x%06x ] ", start, end);
        disasm(vm, start, end);
        puts("");
        end = start;
        start = CELL_FETCH(XMEM, start);
        if(start == -1)
            break;
    }
}

void disasm(VM *vm, cell addr, cell limit) {
    WORD_DISASM(addr);
    int ctr = 0;
    for(;;) {
        printf("%-7s", enum2s(BYTE_FETCH(XMEM, cfa)));
        ctr += 1;
        if(BYTE_FETCH(XMEM, cfa) == NEXT || BYTE_FETCH(XMEM, cfa) == NEST || BYTE_FETCH(XMEM, cfa) == UNNEST)
            break;
        cfa += BYTE_SIZE;
    }
    for(; ctr < 3; ++ctr)
        printf("%7s", "");
    
    printf(" <|> ");

    int pfa = cfa + BYTE_SIZE;
    while(pfa < limit) {
        cell waddr = locate(vm, CELL_FETCH(XMEM, pfa));
        pword(vm, waddr);
        printf(" ");
        if(wname(vm, waddr, "LIT") || wname(vm, waddr, "DOCON") || wname(vm, waddr, "DOVAR") || wname(vm, waddr, "IRJMP") || wname(vm, waddr, "IRJZ")) {
            pfa += CELL_SIZE;
            printf("(0x%x | %i) ", CELL_FETCH(XMEM, pfa), CELL_FETCH(XMEM, pfa));
        } else if(wname(vm, waddr, "DOSTR")) {
            pfa += CELL_SIZE;
            int strlen = CELL_FETCH(XMEM, pfa);
            printf("(%i: \"%.*s\") ", strlen, strlen, &BYTE_FETCH(XMEM, pfa+CELL_SIZE));
            pfa += strlen;
        }
        pfa += CELL_SIZE;
    }
}

int locate(VM *vm, cell addr) {
    cell llp = lp;
    while(llp > addr && llp != -1)
        llp = CELL_FETCH(XMEM, llp);

    return llp;
}

int wname(VM *vm, cell addr, char *target) {
    WORD_DISASM(addr);
    if(strlen(target) != len)
        return 0;
    return 0 == strncmp((char *) name, target, len);
}

void disasm_instr(VM *vm) {
    cell addr;
    if(DEBUG_ENABLE(2, DEBUG_ENABLE(1, XWP != 0) && BYTE_FETCH(XMEM, XIP) != NEXT)) {
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
        printf("%4x %4x | %-7s: ", XIP, XWP, enum2s(BYTE_FETCH(XMEM, XIP)));

        for(int i = 0; i < XRSP-1; ++i)
            printf("  ");

        addr = locate(vm, XWP);
        pword(vm, addr);
        printf(": ");

        addr = locate(vm, XIP);
        pword(vm, addr);
        if(BYTE_FETCH(XMEM, XIP) == LIT || wname(vm, locate(vm, XIP), "DOCON") || wname(vm, locate(vm, XIP), "DOVAR")) {
            printf(" (0x%x | %i)", CELL_FETCH(XMEM, XWP), CELL_FETCH(XMEM, XWP));
        } else if (wname(vm, locate(vm, XIP), "CALL")) {
            printf(" %p", FUNC_FETCH(XMEM, XWP));
        } else if (wname(vm, locate(vm, XIP), "DOSTR")) {
            printf(" (%i: \"%.*s\")", CELL_FETCH(XMEM, XWP), CELL_FETCH(XMEM, XWP), &BYTE_FETCH(XMEM, XWP+CELL_SIZE));
        }
        puts("");
    }
}

void rund(VM *vm, cell addr) {
    XIP = addr;

    printf("Tracing: ");
    pword(vm, locate(vm, XIP));
    puts("");

    printf("%4s %4s | %-7s: %s\n", "IP", "WP", "Prims", "Instructions");
    for(XP = ON; XP == ON; tick(vm))
        disasm_instr(vm);
    XRSP -= 1;
}