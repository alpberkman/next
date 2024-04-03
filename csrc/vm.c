
#include "vm.h"


byte fetch(VM *vm) {
    byte op = BYTE_FETCH(vm->mem, vm->itc.ip);
    vm->itc.ip += BYTE_SIZE;
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


