

#include "dtc.h"


func fetch(DTC *dtc) {
    return *((FP)++);
}
void exec(func f, void *arg) {
    f(arg);
}
void tick(DTC *dtc, void *arg) {
    exec(fetch(dtc), arg);
}
void runc(DTC *dtc, void *arg) {
    for(P = ON; P == ON; tick(dtc, arg));
}

void t(DTC dtc, void *arg) {

}
/*
void _dtc_halt(DTC *dtc) {
    P = OFF;
}
token _dtc_lit(DTC *dtc) {
    token t = *TP;
    TP += 1;
    return t;
}
void _next(VM *vm) {
    MEXT(WP);
}
void _nest(VM *vm) {

    RPUSH = WP;
    WP = IP;
    MEXT(WP);
}
void _unnest(VM *vm) {
    WP = RPOP;
    MEXT(WP);
}
void _jmp(VM *vm) {
    cell addr = PPOP;
    WP = addr;
}
void _jz(VM *vm) {
    cell addr = PPOP;
    cell flag = PPOP;
    if(flag == ((cell) FALSE))
        WP = addr;
}
void _exe(VM *vm) {
    MEXT(PPOP);
}
*/
