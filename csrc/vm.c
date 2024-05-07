
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
void rund(VM *vm, cell addr, func debug) {
    XIP = addr;
    for(XP = ON; XP == ON; tick(vm))
        debug(vm);
}

void reset(VM *vm) {
    // Setup ITC
    XP = OFF;
    XIP = 0;
    XWP = 0;

    // Setup SPU
    XPSP = 0;
    XRSP = 0;
}
void init(VM *vm, byte *mem) {
    // Reset ITC and SPU
    reset(vm);

    // Setup MEM
    XMEM = mem;
}


