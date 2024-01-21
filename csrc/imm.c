
#include "next.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


cell hp;
cell lp;

cell header(VM *vm, const char *name, int len) {
    CELL_FETCH(MEM, hp) = lp;
    lp = hp;
    hp += CELL_SIZE;

    BYTE_FETCH(MEM, hp) = MASK_VIS | len;
    hp += BYTE_SIZE;

    for(int i = 0; i < len; ++i)
        BYTE_FETCH(MEM, hp+BYTES(i)) = (byte) toupper(name[i]);
    hp += BYTES(len);

    return hp;
}
void cf(VM *vm, int len, ...) {
    va_list l;
    va_start(l, len);

    for(int i = 0; i < len; ++i)
        FUNC_FETCH(MEM, hp+FUNCS(i)) = (func) va_arg(l, func);
    hp += FUNCS(len);

    va_end(l);
}
void pf(VM *vm, int len, ...) {
    va_list l;
    va_start(l, len);

    for(int i = 0; i < len; ++i)
        CELL_FETCH(MEM, hp+CELLS(i)) = (cell) va_arg(l, cell);
    hp += CELLS(len);

    va_end(l);
}

void debug(VM *vm) {
    printf("LP: 0x%06x  HP: 0x%06x  MEM_SIZE: 0x%06x\n", lp, hp, MEM_SIZE);
    printf("NAME\t\t\tLEN VIS IMM  CFA\n");
    printf("-----------------------------------------------\n");
    for(cell addr = lp, end = hp; addr != 0; end = addr, addr = *((cell *) &(MEM[addr]))) {
        cell link = CELL_FETCH(MEM, addr);
        byte len = BYTE_FETCH(MEM, addr + CELL_SIZE) & WORD_LEN;
        byte vis = BYTE_FETCH(MEM, addr + CELL_SIZE) & MASK_VIS;
        byte imm = BYTE_FETCH(MEM, addr + CELL_SIZE) & MASK_IMM;
        byte *name = &(MEM[addr + CELL_SIZE + BYTE_SIZE]);
        cell cfa = addr + CELL_SIZE + BYTE_SIZE + len;

        printf("0x%06x %.*s\t\t%02i   %c   %c   0x%06x | ",
               link, len, name, len,
               vis ? '+' : '-',
               imm ? '+' : '-',
               cfa);

        cell head = cfa;

        for(;; head += FUNC_SIZE) {
            printf("%p ", FUNC_FETCH(MEM, head));
            if(FUNC_FETCH(MEM, head) == _next || FUNC_FETCH(MEM, head) == _nest) {
                head += FUNC_SIZE;
                break;
            }
        }
        printf("-- ");

        for(; head < end; head += CELL_SIZE) {
            if(PW(FA(CELL_FETCH(MEM, head))) != 0) {
                head += CELL_SIZE;
                printf("%i ", CELL_FETCH(MEM, head));
            }
        }
        printf("\n");
    }
}
cell find_word(VM *vm, char *c) {
    for(cell addr = lp; addr != 0; addr = CELL_FETCH(MEM, addr)) {
        byte len = BYTE_FETCH(MEM, addr + CELL_SIZE) & WORD_LEN;
        byte vis = BYTE_FETCH(MEM, addr + CELL_SIZE) & MASK_VIS;
        if(vis && (len == strlen(c)))
            if(strncmp(c, (void *) &BYTE_FETCH(MEM, addr + CELL_SIZE + BYTE_SIZE), len) == 0)
                return addr + CELL_SIZE + BYTE_SIZE + len;
    }

    return 0;
}
cell find_addr(VM *vm, cell cfa) {
    cell addr = lp;
    while(addr > cfa)
        addr = CELL_FETCH(MEM, addr);

    return addr;
}
cell print_word(VM *vm, cell addr) {
    cell link = CELL_FETCH(MEM, addr);
    byte len = BYTE_FETCH(MEM, addr + CELL_SIZE) & WORD_LEN;
    byte vis = BYTE_FETCH(MEM, addr + CELL_SIZE) & MASK_VIS;
    byte imm = BYTE_FETCH(MEM, addr + CELL_SIZE) & MASK_IMM;
    byte *name = &(MEM[addr + CELL_SIZE + BYTE_SIZE]);
    cell cfa = addr + CELL_SIZE + BYTE_SIZE + len;

    printf("%.*s ", len, name);

    if(len == 3 && strncmp(name, "LIT", 3) == 0)
        return addr;
    else
        return 0;

}

void next_str(VM *vm, char *c) {
    strcpy((void *) &BYTE_FETCH(MEM, hp), c);
    hp += strlen(c);
}

void next_if(VM *vm) {
    PF(FW(LIT));
    PPUSH = hp;
    hp += CELL_SIZE;
    PF(FW(JZ));
}
void next_then(VM *vm) {
    CELL_FETCH(MEM, PPOP) = hp;
}
void next_else(VM *vm) {
    PF(FW(LIT));
    PPUSH = hp;
    hp += CELL_SIZE;
    _swap(vm);
    PF(FW(JMP));
    CELL_FETCH(MEM, PPOP) = hp;
}

void next_begin(VM *vm) {
    PPUSH = hp;
}
void next_agin(VM *vm) {
    PF(FW(LIT), PPOP, FW(JMP));
}
void next_until(VM *vm) {
    PF(FW(LIT), PPOP, FW(JZ));
}
void next_while(VM *vm) {
    PF(FW(LIT));
    PPUSH = hp;
    hp += CELL_SIZE;
    PF(FW(JZ));
}
void next_repeat(VM *vm) {
    PF(FW(LIT));
    _swap(vm);
    PF(PPOP, FW(JMP));
    CELL_FETCH(MEM, PPOP) = hp;
}

void next_do(VM *vm) {
    (void) vm;
}
void next_loop(VM *vm) {
    (void) vm;
}
void next_ploop(VM *vm) {
    (void) vm;
}
