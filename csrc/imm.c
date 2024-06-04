
#include "imm.h"

#include <ctype.h>
#include <string.h>


cell hp;
cell lp;


cell header(VM *vm, const char *name, int len) {
    CELL_FETCH(XMEM, hp) = lp;
    lp = hp;
    hp += CELL_SIZE;

    BYTE_FETCH(XMEM, hp) = MASK_VIS | len;
    hp += BYTE_SIZE;

    for(int i = 0; i < len; ++i)
        BYTE_FETCH(XMEM, hp+BYTES(i)) = (byte) toupper(name[i]);
    hp += BYTES(len);

    return hp;
}
void cf(VM *vm, int len, mca *args) {
    for(int i = 0; i < len; ++i)
        MCA_FETCH(XMEM, hp+MCAS(i)) = args[i];
    hp += MCAS(len);
}
void pf(VM *vm, int len, cell *args) {
    for(int i = 0; i < len; ++i)
        CELL_FETCH(XMEM, hp+CELLS(i)) = args[i];
    hp += CELLS(len);
}

void next_if(VM *vm, cell word) {
    PF(word);
    PPUSH = hp;
    hp += CELL_SIZE;
}
void next_then(VM *vm) {
    cell addr = PPOP;
    cell offset = hp - addr - CELL_SIZE;
    CELL_FETCH(XMEM, addr) = offset;
}
void next_else(VM *vm, cell word) {
    next_if(vm, word);
    PSWAP;
    next_then(vm);
}

void next_begin(VM *vm) {
    PPUSH = hp;
}
void next_agin(VM *vm, cell word) {
    PF(word);
    cell addr = PPOP;
    cell offset = addr - hp - CELL_SIZE;
    CELL_FETCH(XMEM, hp) = offset;
    hp += CELL_SIZE;
}
void next_until(VM *vm, cell word) {
    PF(word);
    cell addr = PPOP;
    cell offset = addr - hp - CELL_SIZE;
    CELL_FETCH(XMEM, hp) = offset;
    hp += CELL_SIZE;
}
void next_while(VM *vm, cell word) {
    PF(word);
    PPUSH = hp;
    hp += CELL_SIZE;
}
void next_repeat(VM *vm, cell word) {
    PF(word);
    PSWAP;
    cell addr = PPOP;
    cell offset = addr - hp - CELL_SIZE;
    CELL_FETCH(XMEM, hp) = offset;
    hp += CELL_SIZE;
    addr = PPOP;
    offset = hp - addr - CELL_SIZE;
    CELL_FETCH(XMEM, addr) = offset;
}

void str(VM *vm, int len, byte *args) {
    for(int i = 0; i < len; ++i)
        BYTE_FETCH(XMEM, hp+BYTES(i)) = args[i];
    hp += BYTES(len);
}

void next_do(VM *vm) {
    PPUSH = hp;
    hp += CELL_SIZE;
    PPUSH = hp;
}
void next_loop(VM *vm) {
    (void) vm;
    cell addr = PPOP;
    CELL_FETCH(XMEM, hp) = addr;
    hp += CELL_SIZE;
    addr = PPOP;
    CELL_FETCH(XMEM, addr) = hp;
}
/*
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


*/