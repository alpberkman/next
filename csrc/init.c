

#include "init.h"

#include <ctype.h>
#include <stdarg.h>


int hp, lp;


int header(VM *vm, const char *name, int len) {
    CELL_VAL(hp) = lp;
    lp = hp;
    hp += CELL_SIZE;

    BYTE_VAL(hp) = MASK_VIS | len;
    hp += BYTE_SIZE;

    for(int i = 0; i < len; ++i)
        BYTE_VAL(hp+BYTES(i)) = toupper(name[i]);
    hp += BYTES(len);

    return hp;
}
void code(VM *vm, int len, ...) {
    va_list l;
    va_start(l, len);

    for(int i = 0; i < len; ++i)
        BYTE_VAL(hp+BYTES(i)) = va_arg(l, int);
    hp += BYTES(len);

    va_end(l);
}
void colon(VM *vm, int len, ...) {
    va_list l;
    va_start(l, len);

    //BYTE_VAL(hp) = NEST;
    //hp += BYTE_SIZE;

    for(int i = 0; i < len; ++i)
        CELL_VAL(hp+CELLS(i)) = va_arg(l, int);
    hp += CELLS(len);

    va_end(l);
}
void immediate(VM *vm) {
    BYTE_VAL(lp+CELL_SIZE) |= MASK_IMM;
}






void init(VM *vm) {
    (void) vm;
    hp = 0;
    lp = 0;
    CODE(NEXT, ADD, LDC);
}
