

#ifndef _FTH_H
#define _FTH_H

#include "dtc.h"


#define MEM_SIZE (0x8000)
#define CELL_SIZE (sizeof(cell))
#define BYTE_SIZE (sizeof(byte))


typedef struct SPU SPU;
typedef byte *RAM;
typedef struct VM VM;


struct SPU {
    cell ps[0x100];
    byte psp;

    cell rs[0x100];
    byte rsp;
};

struct VM {
    DTC dtc;
    SPU spu;
    RAM ram;
};


#define DTC (vm->dtc)
#define P   (vm->dtc.p)
#define FP  (vm->dtc.fp)
#define TP  (vm->dtc.tp)

#define SPU (vm->spu)
#define PSP (vm->spu.psp)
#define RSP (vm->spu.rsp)
#define PS  (vm->spu.ps)
#define RS  (vm->spu.rs)

#define RAM (vm->ram)

#define PPOP    (PS[--PSP])
#define PPUSH   (PS[PSP++])
#define RPOP    (RS[--RSP])
#define RPUSH   (RS[RSP++])

#define LOGICAL(FLAG)   ((FLAG) ? TRUE : FALSE)


void _nop(VM *vm);
void _halt(VM *vm);
void _lit(VM *vm);
void _next(VM *vm);
void _nest(VM *vm);
void _unnest(VM *vm);
void _jmp(VM *vm);
void _jz(VM *vm);
void _exe(VM *vm);
void _dup(VM *vm);
void _drop(VM *vm);
void _swap(VM *vm);
void _push(VM *vm);
void _pop(VM *vm);
void _pick(VM *vm);
void _rick(VM *vm);
void _ldp(VM *vm);
void _ldr(VM *vm);
void _eq(VM *vm);
void _neq(VM *vm);
void _gt(VM *vm);
void _lt(VM *vm);
void _and(VM *vm);
void _or(VM *vm);
void _xor(VM *vm);
void _shr(VM *vm);
void _shl(VM *vm);
void _tru(VM *vm);
void _fls(VM *vm);
void _add(VM *vm);
void _sub(VM *vm);
void _mul(VM *vm);
void _div(VM *vm);
void _mod(VM *vm);
void _ldc(VM *vm);
void _strc(VM *vm);
void _ldb(VM *vm);
void _strb(VM *vm);
void _cell(VM *vm);
void _byte(VM *vm);
void _mem(VM *vm);
void _key(VM *vm);
void _emit(VM *vm);

#endif
