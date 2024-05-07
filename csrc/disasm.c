

#include "disasm.h"
#include "prims.h"

#include <string.h>
#include <stdio.h>


void locate(VM *vm, cell addr, cell *start, cell *end) {
    *start = lp;
    *end = hp;
    while(*start > addr && *start != -1) {
        *end = *start;
        *start = CELL_FETCH(XMEM, *start);
    }
}

cell find_pfa(VM *vm, cell cfa) {
    cell pfa = cfa;
    while(BYTE_FETCH(XMEM, pfa) != NEXT && BYTE_FETCH(XMEM, pfa) != NEST && BYTE_FETCH(XMEM, pfa) != UNNEST)
        pfa += BYTE_SIZE;
    return pfa + BYTE_SIZE;
}

int wordeq(VM *vm, cell addr, char *target) {
    LOCATE_DISASM(addr);
    if(strlen(target) != len)
        return 0;
    return 0 == strncmp((char *) name, target, len);
}

void pword(VM *vm, cell addr) {
    LOCATE_DISASM(addr);
    printf("%.*s", len, (char*) name);
}
void pword2(VM *vm, cell *addr) {
    LOCATE_DISASM(CELL_FETCH(XMEM, *addr));
    printf("%.*s", len, (char*) name);

    if(STREQ(name, "LIT", len)) {
        *addr += CELL_SIZE;
        printf("(%x | %i) ", CELL_FETCH(XMEM, *addr), CELL_FETCH(XMEM, *addr));
    }
}
void pprim(VM *vm, byte prim) {
    (void) vm;
    printf("%s", (char *[]){TABLE(XENUMNAME)}[prim]);
}
void pheader(VM *vm, cell addr) {
    LOCATE_DISASM(addr);
    printf("0x%04x: 0x%04x %-10.*s %2i   %c   %c  0x%04x  0x%04x [%04x-%04x] ",
           start,
           link,
           len, name,
           len,
           vis ? '+' : '-',
           imm ? '+' : '-',
           cfa, pfa,
           start, end);
}

void disasm_cf(VM *vm, cell cfa, cell end) {
    int space = 3 - (end - cfa);
    while(cfa < end) {
        printf("%-7s", (char *[]){TABLE(XENUMNAME)}[BYTE_FETCH(XMEM, cfa)]);
        cfa += BYTE_SIZE;
    }
    for(int i = 0; i < space; ++i)
        printf("%7s", "");
}

void disasm_pf(VM *vm, cell pfa, cell end) {
    while(pfa < end) {
        pword(vm, CELL_FETCH(XMEM, pfa));
        printf(" ");
        pfa += CELL_SIZE;
    }
}
void disasm_pf2(VM *vm, cell pfa, cell end) {
    while(pfa < end) {
        pword2(vm, &pfa);
        printf(" ");
        pfa += CELL_SIZE;
    }
}


void disasmw(VM *vm, cell addr) {
    LOCATE_DISASM(addr);
    pheader(vm, start);
    printf("<|> ");
    disasm_cf(vm, cfa, pfa);
    printf("<|> ");
    disasm_pf2(vm, pfa, end);
    puts("");
}

void disasmd(VM *vm) {
    for(cell addr = lp; addr != -1; addr = CELL_FETCH(XMEM, addr)) 
        disasmw(vm, addr);
}