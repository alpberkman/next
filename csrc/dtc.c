

#include "dtc.h"
#include <stdio.h>

func fetch(DTC *dtc) {
    return *((dtc->fp)++);
}
void exec(func cmd, void *arg) {
    cmd(arg);
}
void tick(DTC *dtc, void *arg) {
    exec(fetch(dtc), arg);
}
void runc(DTC *dtc, func *fp, void *arg) {
    dtc->fp = fp;
    for(dtc->p = ON; dtc->p == ON; tick(dtc, arg))
        printf("0x%016llx\t0x%016llx\n", (cell) dtc->fp, (cell) dtc->tp);
}

