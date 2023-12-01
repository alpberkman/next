

#include "dtc.h"


func fetch(DTC *dtc, byte *mem) {
    func f = *((func *) &(mem[dtc->fp]));
    dtc->fp += FUNC_SIZE;
    return f;
}
void exec(func f, void *arg) {
    f(arg);
}
void tick(DTC *dtc, byte *mem, void *arg) {
    exec(fetch(dtc, mem), arg);
}
void runc(DTC *dtc, byte *mem, void *arg, cell addr) {
    dtc->fp = addr;
    for(dtc->p = ON; dtc->p == ON; tick(dtc, mem, arg));
}

