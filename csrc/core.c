
#include "core.h"


mca fetch(FTH *fth) {
    mca addr = MCA_FETCH(XMEM, XIP);
    XIP += MCA_SIZE;
    return addr;
}
void tick(FTH *fth) {
    mca addr = fetch(fth);
    exec(fth, addr);
}
void runc(FTH *fth, cell addr) {
    XIP = addr;
    for(XP = ON; XP == ON; tick(fth));
}
void rund(FTH *fth, cell addr, func debug) {
    XIP = addr;
    for(XP = ON; XP == ON; tick(fth))
        debug(fth);
}

void init(FTH *fth) {
    // Setup ITC
    XP = OFF;
    XIP = 0;
    XWP = 0;

    // Setup SPU
    XPSP = 0;
    XRSP = 0;
}
