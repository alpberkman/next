
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

void next_if(VM *vm) {
    HERE_CELL_ALLOT;
}
void next_then(VM *vm) {
    HERE_SWAP_STORE;
}
void next_else(VM *vm) {
    HERE_CELL_ALLOT;
    PSWAP;
    HERE_SWAP_STORE;
}

void next_begin(VM *vm) {
    HERE;
}
void next_agin(VM *vm) {
    APPEND(PPOP);
}
void next_until(VM *vm) {
    APPEND(PPOP);
}
void next_while(VM *vm) {
    HERE_CELL_ALLOT;
}
void next_repeat(VM *vm) {
    PSWAP;
    APPEND(PPOP);
    HERE_SWAP_STORE;
}

void str(VM *vm, int len, byte *args) {
    for(int i = 0; i < len; ++i)
        BYTE_FETCH(XMEM, hp+BYTES(i)) = args[i];
    hp += BYTES(len);
}

void next_do(VM *vm) {
    HERE_CELL_ALLOT; HERE;
}
void next_ploop(VM *vm) {
    APPEND(PPOP); HERE_SWAP_STORE;
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