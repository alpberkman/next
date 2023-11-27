

#include "next.h"

#include <ctype.h>
#include <stdarg.h>


void *hp;
void *lp;


cell header(VM *vm, const char *name, int len) {
    (void) vm;

    *((cell *) hp) = (cell) lp;
    lp = hp;
    hp += CELL_SIZE;

    *((byte *) hp) = MASK_VIS | len;
    hp += BYTE_SIZE;

    for(int i = 0; i < len; ++i)
        ((byte *) hp)[i] = toupper(name[i]);
    hp += len*BYTE_SIZE;

    return (cell) hp;
}

void tokens(VM *vm, int len, ...) {
    (void) vm;

    va_list l;
    va_start(l, len);

    for(int i = 0; i < len; ++i)
        ((cell *) hp)[i] = va_arg(l, cell);
    hp += len*CELL_SIZE;

    va_end(l);
}








void init(VM *vm) {

    hp = RAM;
    lp = 0;

    FP = (reg) RAM;
    TP = (reg) RAM;

    PSP = 0;
    RSP = 0;

}

















