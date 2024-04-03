
#include "itc.h"


func fetch(VM *vm) {
    func f = FUNC_FETCH(mem, itc->ip);
    vm->itc.ip += BYTE_SIZE;
    return f;
}
void execute(VM *vm, func f) {
    f(vm);
}
void tick(VM *vm) {
    func f = fetch(vm);
    execute(vm, f);
}
void runc(VM *vm, cell addr) {
    vm->itc.ip = addr;
    for(vm->itc.p = ON; vm->itc.p == ON; tick(vm));
}




byte fetch(VM *vm) {
    byte op = BYTE_FETCH(vm->mem, vm->itc.ip);
    vm->itc.ip += BYTE_SIZE;
    return op;
}
func decode(byte op) {
    func prims[256] = { TABLE(XFUNCTAB) };
    return prims[op];
}
void execute(VM *vm, byte op) {
    func f = decode(op)
    f(vm);
}
void tick(VM *vm) {
    byte op = fetch(vm);
    execute(vm, op);
}
void runc(VM *vm, cell addr) {
    vm->itc.ip = addr;
    for(vm->itc.p = ON; vm->itc.p == ON; tick(vm));
}

void init(VM *vm, byte *mem) {
    // Setup ITC
    vm->itc.p = OFF;
    vm->itc.ip = 0;
    vm->itc.wp = 0;

    // Setup SPU
    vm->spu.p.sp = 0;
    vm->spu.r.sp = 0;

    // Setup MEM
    vm->mem = mem;
}