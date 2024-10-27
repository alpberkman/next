

#include "disasm.h"
#include "../prims.h"

#include <string.h>
#include <stdio.h>


void locate(FTH *fth, cell addr, cell *start, cell *end) {
    *start = lp;
    *end = hp;
    while(*start > addr && *start != -1) {
        *end = *start;
        *start = CELL_FETCH(XMEM, *start);
    }
}

cell find_pfa(FTH *fth, cell cfa) {
    cell pfa = cfa;
    while(MCA_FETCH(XMEM, pfa) != NEXT && MCA_FETCH(XMEM, pfa) != NEST && MCA_FETCH(XMEM, pfa) != UNNEST)
        pfa += MCA_SIZE;
    return pfa + MCA_SIZE;
}

int wordeq(FTH *fth, cell addr, char *target) {
    LOCATE_DISASM(addr);
    if(strlen(target) != len)
        return 0;
    return 0 == strncmp((char *) name, target, len);
}

int pword(FTH *fth, cell *addr) {
    LOCATE_DISASM(CELL_FETCH(XMEM, *addr));
    printf("%.*s", len, (char*) name);
    *addr += CELL_SIZE;

    if(STREQ(name, "LIT", len) || STREQ(name, "DOVAR", len) || STREQ(name, "DOCON", len)) {
        printf("(0x%x | %i)", CELL_FETCH(XMEM, *addr), CELL_FETCH(XMEM, *addr));
        *addr += CELL_SIZE;
    } else if(STREQ(name, "IRJMP", len) || STREQ(name, "IRJZ", len)) {
        printf("(0x%x)", CELL_FETCH(XMEM, *addr));
        *addr += CELL_SIZE;
    } else if(STREQ(name, "(IF)", len) || STREQ(name, "(ELSE)", len)) {
        printf("(0x%x)", CELL_FETCH(XMEM, *addr));
        *addr += CELL_SIZE;
    } else if(STREQ(name, "(BEGIN)", len) || STREQ(name, "(AGAIN)", len)) {
        printf("(0x%x)", CELL_FETCH(XMEM, *addr));
        *addr += CELL_SIZE;
    } else if(STREQ(name, "(UNTIL)", len)) {
        printf("(0x%x)", CELL_FETCH(XMEM, *addr));
        *addr += CELL_SIZE;
    } else if(STREQ(name, "(WHILE)", len) || STREQ(name, "(REPEAT)", len)) {
        printf("(0x%x)", CELL_FETCH(XMEM, *addr));
        *addr += CELL_SIZE;
    } else if(STREQ(name, "(DO)", len) || STREQ(name, "(+LOOP)", len)) {
        printf("(0x%x)", CELL_FETCH(XMEM, *addr));
        *addr += CELL_SIZE;
    } else if(STREQ(name, "DOSTR", len)) {
        int slen = CELL_FETCH(XMEM, *addr);
        *addr += CELL_SIZE;
        char *str = (char *) &BYTE_FETCH(XMEM, *addr);
        *addr += slen;
        printf("(%i: \"%.*s\")", slen, slen, str);
    } else if(STREQ(name, "CALL", len)) {
        printf("(%p)", FUNC_FETCH(XMEM, XWP));
        *addr += FUNC_SIZE;
    }

    return len;
}
int pprim(FTH *fth, cell *addr) {
    char *name = (char *[]){TABLE(XENUMNAME)}[BYTE_FETCH(XMEM, *addr)];
    *addr += MCA_SIZE;
    printf("%s", name);

    return strlen(name);
}
void pheader(FTH *fth, cell addr) {
    LOCATE_DISASM(addr);
    printf("0x%04x: 0x%04x %-10.*s %2i   %c   %c  0x%04x  0x%04x [%04x-%04x] ",
           start,
           link & 0xffff,
           len, name,
           len,
           vis ? '+' : '-',
           imm ? '+' : '-',
           cfa, pfa,
           start, end);
}

void disasm_cf(FTH *fth, cell cfa, cell end) {
    int space = 3 - (end - cfa);
    while(cfa < end) {
        int slen = pprim(fth, &cfa);
        printf("%.*s", 7-slen, "         ");
    }
    for(int i = 0; i < space; ++i)
        printf("%7s", "");
}

void disasm_pf(FTH *fth, cell pfa, cell end) {
    while(pfa < end) {
        pword(fth, &pfa);
        printf(" ");
    }
}



void disasmw(FTH *fth, cell addr) {
    LOCATE_DISASM(addr);
    pheader(fth, start);
    printf("<|> ");
    disasm_cf(fth, cfa, pfa);
    printf("<|> ");
    disasm_pf(fth, pfa, end);
    puts("");
}

void disasmd(FTH *fth) {
        printf("%-8s%-7s%-11s%-4s%-4s%-4s%-8s%-7s%-11s <|> %-20s <|> %s\n",
           "ADDR",
           "LINK",
           "NAME",
           "LEN",
           "VIS",
           "IMM",
           "CFA",
           "PFA",
           "[SPACE)",
           "CF",
           "PF"
          );
          printf("%.*s+%.*s+%.*s\n", 
            66, "------------------------------------------------------------------", 
            24, "------------------------",
            36, "------------------------------------");
    for(cell addr = lp; addr != -1; addr = CELL_FETCH(XMEM, addr)) 
        disasmw(fth, addr);
}