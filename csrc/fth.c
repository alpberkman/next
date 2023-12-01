

#include "fth.h"

#include <stdio.h>


FTH(_nop) BEGIN
END

FTH(_halt) BEGIN
    MOFF(DTC, MEM);
END

FTH(_lit) BEGIN
    PPUSH = MLIT(DTC, MEM);
END

FTH(_next) BEGIN
    MEXT(DTC, MEM);
END

FTH(_nest) BEGIN
    RPUSH = MNEST(DTC, MEM);
    MEXT(DTC, MEM);
END

FTH(_unnest) BEGIN
    MUNNEST(DTC, MEM) = RPOP;
    MEXT(DTC, MEM);
END

FTH(_jmp) BEGIN
    cell addr = PPOP;
    MJMP(DTC, MEM) = addr;
END

FTH(_jz) BEGIN
    cell addr = PPOP;
    cell flag = PPOP;
    if(flag == FALSE)
        MJMP(DTC, MEM) = addr;
END

FTH(_exe) BEGIN
    cell addr = PPOP;
    MEXE(DTC, MEM) = addr;
END


FTH(_dup) BEGIN
    cell val = PPOP;
    PPUSH = val;
    PPUSH = val;
END

FTH(_drop) BEGIN
    (void) PPOP;
END

FTH(_swap) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = a;
    PPUSH = b;
END

FTH(_push) BEGIN
    RPUSH = PPOP;
END

FTH(_pop) BEGIN
    PPUSH = RPOP;
END

FTH(_pick) BEGIN
    byte n = PPOP + 1;
    n = PSP - n;
    PPUSH = PS[n];
END

FTH(_rick) BEGIN
    byte n = PPOP + 1;
    n = RSP - n;
    PPUSH = RS[n];
END

FTH(_ldp) BEGIN
    byte val = PSP;
    PPUSH = val;
END

FTH(_ldr) BEGIN
    byte val = RSP;
    PPUSH = val;
END

FTH(_eq) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b == a);
END

FTH(_neq) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b != a);
END

FTH(_gt) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b > a);
END

FTH(_lt) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b < a);
END

FTH(_and) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b & a;
END

FTH(_or) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b | a;
END

FTH(_xor) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b ^ a;
END

FTH(_shr) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b >> a;
END

FTH(_shl) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b << a;
END

FTH(_tru) BEGIN
    PPUSH = TRUE;
END

FTH(_fls) BEGIN
    PPUSH = FALSE;
END

FTH(_add) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b + a;
END

FTH(_sub) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b - a;
END

FTH(_mul) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b * a;
END

FTH(_div) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b / a;
END

FTH(_mod) BEGIN
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b % a;
END

FTH(_ldc) BEGIN
    cell addr = PPOP;
    cell val = *((cell *) &(MEM[addr]));
    PPUSH = val;
END

FTH(_strc) BEGIN
    cell addr = PPOP;
    cell val = PPOP;
    *((cell *) &(MEM[addr])) = val;
END

FTH(_ldb) BEGIN
    cell addr = PPOP;
    byte val = *((byte *) &(MEM[addr]));
    PPUSH = val;
END

FTH(_strb) BEGIN
    cell addr = PPOP;
    byte val = PPOP;
    *((byte *) &(MEM[addr])) = val;
END

FTH(_func) BEGIN
    PPUSH = FUNC_SIZE;
END

FTH(_cell) BEGIN
    PPUSH = CELL_SIZE;
END

FTH(_byte) BEGIN
    PPUSH = BYTE_SIZE;
END

FTH(_mem) BEGIN
    PPUSH = MEM_SIZE;
END

FTH(_key) BEGIN
    byte c = getchar();
    PPUSH = c;
END

FTH(_emit) BEGIN
    byte c = PPOP;
    putchar(c);
END



