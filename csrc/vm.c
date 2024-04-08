
#include "vm.h"


byte fetch(VM *vm) {
    byte op = BYTE_FETCH(XMEM, XIP);
    XIP += BYTE_SIZE;
    return op;
}
void execute(VM *vm, byte op) {
    func f = decode(op);
    f(vm);
}
void tick(VM *vm) {
    byte op = fetch(vm);
    execute(vm, op);
}
void runc(VM *vm, cell addr) {
    XIP = addr;
    for(XP = ON; XP == ON; tick(vm));
}

void init(VM *vm, byte *mem) {
    // Setup ITC
    XP = OFF;
    XIP = 0;
    XWP = 0;

    // Setup SPU
    XPSP = 0;
    XRSP = 0;

    // Setup MEM
    XMEM = mem;
}


