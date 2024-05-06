

#ifndef _VM_H
#define _VM_H

#define CELL_TYPE int

#define MEM_SIZE (0x8000)
#define MASK_VIS (1<<7)
#define MASK_IMM (1<<6)
#define WORD_LEN (31)


#define FALSE   (0)
#define TRUE    (-1)


typedef struct VM VM;

typedef CELL_TYPE cell;
typedef unsigned CELL_TYPE ucell;
typedef unsigned char byte;
typedef void (*func) (VM *vm);

typedef enum power power;
typedef struct stack stack;

typedef struct ITC ITC;
typedef struct SPU SPU;
typedef byte *MEM;


enum power {
    OFF = FALSE,
    ON = TRUE,
};

struct stack {
    cell s[0x100];
    byte sp;
};

struct ITC {
    power p;
    cell ip;
    cell wp;
};

struct SPU {
    stack p;
    stack r;
};

struct VM {
    ITC itc;
    SPU spu;
    MEM mem;
};


byte fetch(VM *vm);
func decode(byte op);
void execute(VM *vm, byte op);
void tick(VM *vm);
void runc(VM *vm, cell addr);

void reset(VM *vm);
void init(VM *vm, byte *mem);


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


#define LOGICAL(FLAG) ((FLAG) ? TRUE : FALSE)

#define PPOP    (XPS[--XPSP])
#define PPUSH   (XPS[XPSP++])
#define RPOP    (XRS[--XRSP])
#define RPUSH   (XRS[XRSP++])


#define MEXT \
    XIP = CELL_FETCH(XMEM, XWP); \
    XWP += CELL_SIZE

#define MLIT \
    CELL_FETCH(XMEM, XWP); \
    XWP += CELL_SIZE

#define MNEST \
    XWP; \
    XWP = XIP

#define MUNNEST \
    XWP

#define MJMP \
    XWP

#define MEXE \
    XIP

#define MCALL \
    FUNC_FETCH(XMEM, XWP); \
    XWP += FUNC_SIZE

#endif

