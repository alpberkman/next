
#include "imm.h"

#include <ctype.h>
#include <string.h>


cell hp;
cell lp;


cell header(FTH *fth, const char *name, int len) {
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
void cf(FTH *fth, int len, mca *args) {
    for(int i = 0; i < len; ++i)
        MCA_FETCH(XMEM, hp+MCAS(i)) = args[i];
    hp += MCAS(len);
}
void pf(FTH *fth, int len, cell *args) {
    for(int i = 0; i < len; ++i)
        CELL_FETCH(XMEM, hp+CELLS(i)) = args[i];
    hp += CELLS(len);
}

void next_if(FTH *fth) {
    HERE_CELL_ALLOT;
}
void next_then(FTH *fth) {
    HERE_SWAP_STORE;
}
void next_else(FTH *fth) {
    HERE_CELL_ALLOT;
    PSWAP;
    HERE_SWAP_STORE;
}

void next_begin(FTH *fth) {
    HERE;
}
void next_agin(FTH *fth) {
    APPEND(PPOP);
}
void next_until(FTH *fth) {
    APPEND(PPOP);
}
void next_while(FTH *fth) {
    HERE_CELL_ALLOT;
}
void next_repeat(FTH *fth) {
    PSWAP;
    APPEND(PPOP);
    HERE_SWAP_STORE;
}

void str(FTH *fth, int len, byte *args) {
    for(int i = 0; i < len; ++i)
        BYTE_FETCH(XMEM, hp+BYTES(i)) = args[i];
    hp += BYTES(len);
}

void next_do(FTH *fth) {
    HERE_CELL_ALLOT; HERE;
}
void next_ploop(FTH *fth) {
    APPEND(PPOP); HERE_SWAP_STORE;
}
/*
cell find_word(FTH *fth, char *c) {
    for(cell addr = lp; addr != 0; addr = CELL_FETCH(MEM, addr)) {
        byte len = BYTE_FETCH(MEM, addr + CELL_SIZE) & WORD_LEN;
        byte vis = BYTE_FETCH(MEM, addr + CELL_SIZE) & MASK_VIS;
        if(vis && (len == strlen(c)))
            if(strncmp(c, (void *) &BYTE_FETCH(MEM, addr + CELL_SIZE + BYTE_SIZE), len) == 0)
                return addr + CELL_SIZE + BYTE_SIZE + len;
    }

    return 0;
}
cell find_addr(FTH *fth, cell cfa) {
    cell addr = lp;
    while(addr > cfa)
        addr = CELL_FETCH(MEM, addr);

    return addr;
}


*/