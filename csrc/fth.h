

#ifndef _FTH_H
#define _FTH_H

#include "itc.h"


#define MEM_SIZE (0x8000)


typedef struct VM VM;
typedef struct SPU SPU;
typedef byte *MEM;


struct SPU {
    cell ps[0x100];
    byte psp;

    cell rs[0x100];
    byte rsp;
};

struct VM {
    ITC itc;
    SPU spu;
    MEM mem;
};


#define ITC (vm->itc)
#define P   (vm->itc.p)
#define IP  (vm->itc.ip)
#define WP  (vm->itc.wp)

#define SPU (vm->spu)
#define PSP (vm->spu.psp)
#define RSP (vm->spu.rsp)
#define PS  (vm->spu.ps)
#define RS  (vm->spu.rs)

#define MEM (vm->mem)


#define PPOP    (PS[--PSP])
#define PPUSH   (PS[PSP++])
#define RPOP    (RS[--RSP])
#define RPUSH   (RS[RSP++])

#define LOGICAL(FLAG) ((FLAG) ? TRUE : FALSE)


#define FTH(NAME) \
    void NAME(void *arg)

#define BEGIN \
    { \
        VM *vm = (VM *) arg;

#define END \
    }


FTH(_nop);
FTH(_halt);
FTH(_lit);
FTH(_next);
FTH(_nest);
FTH(_unnest);
FTH(_jmp);
FTH(_jz);
FTH(_exe);
FTH(_dup);
FTH(_drop);
FTH(_swap);
FTH(_push);
FTH(_pop);
FTH(_pick);
FTH(_rick);
FTH(_ldp);
FTH(_ldr);
FTH(_eq);
FTH(_neq);
FTH(_gt);
FTH(_lt);
FTH(_and);
FTH(_or);
FTH(_xor);
FTH(_shr);
FTH(_shl);
FTH(_tru);
FTH(_fls);
FTH(_add);
FTH(_sub);
FTH(_mul);
FTH(_div);
FTH(_mod);
FTH(_ldc);
FTH(_strc);
FTH(_ldb);
FTH(_strb);
FTH(_func);
FTH(_cell);
FTH(_byte);
FTH(_mem);
FTH(_key);
FTH(_emit);

#endif

