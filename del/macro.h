
#ifndef _MACRO_H
#define _MACRO_H


#define MEM_SIZE (0x8000)


#define FALSE   (0)
#define TRUE    (-1)

#define LOGICAL(FLAG) ((FLAG) ? TRUE : FALSE)


#define FUNC_SIZE (sizeof(func))
#define CELL_SIZE (sizeof(cell))
#define BYTE_SIZE (sizeof(byte))

#define FUNCS(N) (N*FUNC_SIZE)
#define CELLS(N) (N*CELL_SIZE)
#define BYTES(N) (N*BYTE_SIZE)

#define TYPE_FETCH(TYPE, MEM, ADDR) (*((TYPE *) &((MEM)[ADDR])))
#define FUNC_FETCH(MEM, ADDR) (TYPE_FETCH(func, MEM, ADDR))
#define CELL_FETCH(MEM, ADDR) (TYPE_FETCH(cell, MEM, ADDR))
#define BYTE_FETCH(MEM, ADDR) (TYPE_FETCH(byte, MEM, ADDR))


#define XITC (vm->itc)
#define XP   (vm->itc.p)
#define XIP  (vm->itc.ip)
#define XWP  (vm->itc.wp)

#define XSPU (vm->spu)
#define XPSP (vm->spu.p.sp)
#define XRSP (vm->spu.r.sp)
#define XPS  (vm->spu.p.s)
#define XRS  (vm->spu.r.s)

#define XMEM (vm->mem)


#define PPOP    (XPS[--XPSP])
#define PPUSH   (XPS[XPSP++])
#define RPOP    (XRS[--XRSP])
#define RPUSH   (XRS[XRSP++])


#define MEXT(XVM) \
    (XVM)->itc.ip = CELL_FETCH((XVM)->mem, (XVM)->itc.wp); \
    (XVM)->itc.wp += CELL_SIZE

#define MLIT(XVM) \
    CELL_FETCH((XVM)->mem, (XVM)->itc.wp); \
    (XVM)->itc.wp += CELL_SIZE

#define MNEST(XVM) \
    (XVM)->itc.wp; \
    (XVM)->itc.wp = (XVM)->itc.ip

#define MUNNEST(XVM) \
    (XVM)->itc.wp

#define MJMP(XVM) \
    (XVM)->itc.wp

#define MEXE(XVM) \
    (XVM)->itc.ip

#endif
