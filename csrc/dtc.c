

#include "dtc.h"
#include <stdio.h>

fun fetch(DTC *dtc) {
    return (fun) (*((dtc->fp)++));
}
void exec(fun f, void *arg) {
    f(arg);
}
void tick(DTC *dtc, void *arg) {
    exec(fetch(dtc), arg);
}
void runc(DTC *dtc, void *arg) {
    for(dtc->p = ON; dtc->p == ON; tick(dtc, arg))
        printf("0x%016llx\t0x%016llx\n", dtc->fp, dtc->tp);
}

