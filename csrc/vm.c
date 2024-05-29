
#include "vm.h"


mca fetch(VM *vm) {
    mca addr = MCA_FETCH(XMEM, XIP);
    XIP += MCA_SIZE;
    return addr;
}
void tick(VM *vm) {
    mca addr = fetch(vm);
    exec(vm, addr);
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


