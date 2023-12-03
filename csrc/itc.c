

#include "itc.h"


func fetch(ITC *itc, byte *mem) {
    func f = FUNC_FETCH(mem, itc->ip);
    itc->ip += FUNC_SIZE;
    return f;
}
void tick(ITC *itc, byte *mem, void *arg) {
    fetch(itc, mem)(arg);
}
void runc(ITC *itc, byte *mem, void *arg, cell addr) {
    itc->ip = addr;
    for(itc->p = ON; itc->p == ON; tick(itc, mem, arg));
}

