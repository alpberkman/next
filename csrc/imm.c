
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
void cf(VM *vm, int len, byte *args) {
    for(int i = 0; i < len; ++i)
        BYTE_FETCH(XMEM, hp+BYTES(i)) = args[i];
    hp += BYTES(len);
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

/*


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