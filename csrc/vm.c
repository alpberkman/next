
#include "vm.h"
#include "op.h"


byte fetch(VM *vm) {
    byte op = BYTE_FETCH(vm->mem, vm->itc.ip);
    vm->itc.ip += BYTE_SIZE;
    return op;
}
void execute(VM *vm, byte op) {
    decode(op)(vm);
}
void tick(VM *vm) {
    byte op = fetch(vm);
    execute(vm, op);
}
void runc(VM *vm, cell addr) {
    vm->itc.ip = addr;
    for(vm->itc.p = ON; vm->itc.p == ON; tick(vm));
}


