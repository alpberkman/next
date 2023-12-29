
#include "next.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cell hp;
cell lp;

void runf(VM *vm, cell addr) {
    runc(&ITC, MEM, vm, addr);
}
void init(VM *vm) {
    hp = 0;
    lp = 0;

    // Setup ITC
    IP = 0;
    WP = 0;
    // Setup SPU
    PSP = 0;
    RSP = 0;
    //Setup RAM
    MEM = malloc(MEM_SIZE);
    if(MEM == NULL)
        return;

    XPRIMS(NOP, _nop, _next);
    XPRIMS(HALT, _halt, _next);
    XPRIMS(LIT, _lit, _next);
    XPRIMS(NEXT, _next, _next);
    XPRIMS(NEST, _nest, _next);
    XPRIMS(UNNEST, _unnest, _next);
    XPRIMS(JMP, _jmp, _next);
    XPRIMS(JZ, _jz, _next);
    XPRIMS(EXE, _exe, _next);

    XPRIMS(DUP, _dup, _next);
    XPRIMS(DROP, _drop, _next);
    XPRIMS(SWAP, _swap, _next);
    XPRIMS(PUSH, _push, _next);
    XPRIMS(POP, _pop, _next);
    XPRIMS(PICK, _pick, _next);
    XPRIMS(RICK, _rick, _next);
    XPRIMS(LDP, _ldp, _next);
    XPRIMS(LDR, _ldr, _next);
    XPRIMS(EQ, _eq, _next);
    XPRIMS(NEQ, _neq, _next);
    XPRIMS(GT, _gt, _next);
    XPRIMS(LT, _lt, _next);
    XPRIMS(AND, _and, _next);
    XPRIMS(OR, _or, _next);
    XPRIMS(XOR, _xor, _next);
    XPRIMS(SHR, _shr, _next);
    XPRIMS(SHL, _shl, _next);
    XPRIMS(TRU, _tru, _next);
    XPRIMS(FLS, _fls, _next);
    XPRIMS(ADD, _add, _next);
    XPRIMS(SUB, _sub, _next);
    XPRIMS(MUL, _mul, _next);
    XPRIMS(DIV, _div, _next);
    XPRIMS(MOD, _mod, _next);
    XPRIMS(LDC, _ldc, _next);
    XPRIMS(STRC, _strc, _next);
    XPRIMS(LDB, _ldb, _next);
    XPRIMS(STRB, _strb, _next);
    XPRIMS(FUNC, _func, _next);
    XPRIMS(CELL, _cell, _next);
    XPRIMS(BYTE, _byte, _next);
    XPRIMS(XMEM, _mem, _next);
    XPRIMS(KEY, _key, _next);
    XPRIMS(EMIT, _emit, _next);

    XPRIMS(t1, _tru, _tru, _next);

    XCOLON(t2, t1, t1, UNNEST);
    XCOLON(m, t2, LIT, 123, LIT, t1, EXE, t1, HALT);
    XCOLON(m2, LIT, 123, DUP, ADD, TRU, MUL, FLS, m);
    XCOLON(m3, NOP);
    BEGIN(KEY, DUP, LIT, 65, EQ);
    IF(HALT);
    ELSE(FLS);
    THEN(LIT, 777);
    AGAIN(HALT);

    XCOLON(echo, NOP);
    BEGIN(KEY, DUP, EMIT, LIT, 'q', EQ);
    UNTIL(HALT);

    XCOLON(e2, NOP);
    BEGIN(KEY, DUP, LIT, 'q', NEQ);
    WHILE(DUP, EMIT);
    REPEAT(LIT, 1234, HALT);

    CONST(X1, 123);
    VAR(Z1);
    VAR(Z2);
    XCOLON(t3, Z1, LDB, X1, Z1, STRB, TRU, Z1, LDB, HALT);

    debug(vm);
    runf(vm, t3);
}

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
            //byte len = BYTE_FETCH(MEM, head + CELL_SIZE) & WORD_LEN;
            //byte *name = &(MEM[head + CELL_SIZE + BYTE_SIZE]);
            //printf("%.*s ", len, name);
            if(FUNC_FETCH(MEM, head) == _next || FUNC_FETCH(MEM, head) == _nest) {
                head += FUNC_SIZE;
                break;
            }
        }
        printf("-- ");
        for(; head < end; head += CELL_SIZE) {
            printf("0x%06x ", CELL_FETCH(MEM, head));
            //byte len = BYTE_FETCH(MEM, head + CELL_SIZE) & WORD_LEN;
            //byte *name = &(MEM[head + CELL_SIZE + BYTE_SIZE]);
            //printf("%.*s ", len, name);
        }/**/

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
