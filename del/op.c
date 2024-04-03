
#include "op.h"

func decode(byte op) {
    func prims[256] = { TABLE(XFUNCTAB) };
    return prims[op];
}

FTH(_nop) {}
FTH(_halt) {}
FTH(_lit) {}
FTH(_next) {}
FTH(_nest) {}
FTH(_unnest) {}
FTH(_jmp) {}
FTH(_jz) {}
FTH(_exe) {}
FTH(_dup) {}
FTH(_drop) {}
FTH(_swap) {}
FTH(_push) {}
FTH(_pop) {}
FTH(_pick) {}
FTH(_rick) {}
FTH(_ldp) {}
FTH(_ldr) {}
FTH(_eq) {}
FTH(_neq) {}
FTH(_gt) {}
FTH(_lt) {}
FTH(_and) {}
FTH(_or) {}
FTH(_xor) {}
FTH(_shr) {}
FTH(_shl) {}
FTH(_tru) {}
FTH(_fls) {}
FTH(_add) {}
FTH(_sub) {}
FTH(_mul) {}
FTH(_div) {}
FTH(_mod) {}
FTH(_ldc) {}
FTH(_strc) {}
FTH(_ldb) {}
FTH(_strb) {}
FTH(_func) {}
FTH(_cell) {}
FTH(_byte) {}
FTH(_mems) {}
FTH(_key) {}
FTH(_emit) {}