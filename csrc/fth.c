

#include "fth.h"

#include <stdio.h>


FTH(_nop) IS
END

FTH(_halt) IS
    MOFF(&ITC, MEM);
END

FTH(_lit) IS
    PPUSH = MLIT(&ITC, MEM);
END

FTH(_next) IS
    MEXT(&ITC, MEM);
END

FTH(_nest) IS
    RPUSH = MNEST(&ITC, MEM);
    MEXT(&ITC, MEM);
END

FTH(_unnest) IS
    MUNNEST(&ITC, MEM) = RPOP;
    MEXT(&ITC, MEM);
END

FTH(_jmp) IS
    cell addr = PPOP;
    MJMP(&ITC, MEM) = addr;
END

FTH(_jz) IS
    cell addr = PPOP;
    cell flag = PPOP;
    if(flag == FALSE)
        MJMP(&ITC, MEM) = addr;
END

FTH(_exe) IS
    cell addr = PPOP;
    MEXE(&ITC, MEM) = addr;
END


FTH(_dup) IS
    cell val = PPOP;
    PPUSH = val;
    PPUSH = val;
END

FTH(_drop) IS
    (void) PPOP;
END

FTH(_swap) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = a;
    PPUSH = b;
END

FTH(_push) IS
    RPUSH = PPOP;
END

FTH(_pop) IS
    PPUSH = RPOP;
END

FTH(_pick) IS
    byte n = PPOP + 1;
    n = PSP - n;
    PPUSH = PS[n];
END

FTH(_rick) IS
    byte n = PPOP + 1;
    n = RSP - n;
    PPUSH = RS[n];
END

FTH(_ldp) IS
    byte val = PSP;
    PPUSH = val;
END

FTH(_ldr) IS
    byte val = RSP;
    PPUSH = val;
END

FTH(_eq) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b == a);
END

FTH(_neq) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b != a);
END

FTH(_gt) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b > a);
END

FTH(_lt) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = LOGICAL(b < a);
END

FTH(_and) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b & a;
END

FTH(_or) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b | a;
END

FTH(_xor) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b ^ a;
END

FTH(_shr) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b >> a;
END

FTH(_shl) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b << a;
END

FTH(_tru) IS
    PPUSH = TRUE;
END

FTH(_fls) IS
    PPUSH = FALSE;
END

FTH(_add) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b + a;
END

FTH(_sub) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b - a;
END

FTH(_mul) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b * a;
END

FTH(_div) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b / a;
END

FTH(_mod) IS
    cell a = PPOP;
    cell b = PPOP;
    PPUSH = b % a;
END

FTH(_ldc) IS
    cell addr = PPOP;
    cell val = CELL_FETCH(MEM, addr);
    PPUSH = val;
END

FTH(_strc) IS
    cell addr = PPOP;
    cell val = PPOP;
    CELL_FETCH(MEM, addr) = val;
END

FTH(_ldb) IS
    cell addr = PPOP;
    byte val = BYTE_FETCH(MEM, addr);
    PPUSH = val;
END

FTH(_strb) IS
    cell addr = PPOP;
    byte val = PPOP;
    BYTE_FETCH(MEM, addr) = val;
END

FTH(_func) IS
    PPUSH = FUNC_SIZE;
END

FTH(_cell) IS
    PPUSH = CELL_SIZE;
END

FTH(_byte) IS
    PPUSH = BYTE_SIZE;
END

FTH(_mem) IS
    PPUSH = MEM_SIZE;
END

FTH(_key) IS
    byte c = getchar();
    PPUSH = c;
END

FTH(_emit) IS
    byte c = PPOP;
    putchar(c);
END



