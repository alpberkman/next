

#include "dtc.h"


fun fetch(DTC *dtc) {
    return (*((dtc->fp)++)).f;
}
void exec(fun f, void *arg) {
    f(arg);
}
void tick(DTC *dtc, void *arg) {
    exec(fetch(dtc), arg);
}
void runc(DTC *dtc, void *arg) {
    for(dtc->p = ON; dtc->p == ON; tick(dtc, arg));
}

