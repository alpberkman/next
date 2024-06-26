

#ifndef _VM_H
#define _VM_H


#define MEM_SIZE (0x8000)
#define MASK_VIS (1<<7)
#define MASK_IMM (1<<6)
#define WORD_LEN (31)

#define FALSE   (0)
#define TRUE    (-1)


typedef struct VM VM;

typedef int cell;
typedef unsigned int ucell;
typedef unsigned char byte;
typedef void (*func) (VM *vm);
typedef byte mca;

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


mca fetch(VM *vm);
void exec(VM *vm, mca addr);
void tick(VM *vm);
void runc(VM *vm, cell addr);
void rund(VM *vm, cell addr, func debug);

void reset(VM *vm);
void init(VM *vm, byte *mem);


#define FUNC_SIZE (sizeof(func))
#define CELL_SIZE (sizeof(cell))
#define BYTE_SIZE (sizeof(byte))
#define MCA_SIZE  (sizeof(mca))

#define FUNCS(N) (N*FUNC_SIZE)
#define CELLS(N) (N*CELL_SIZE)
#define BYTES(N) (N*BYTE_SIZE)
#define MCAS(N)  (N*MCA_SIZE)

#define TYPE_FETCH(TYPE, MEM, ADDR) (*((TYPE *) &((MEM)[ADDR])))
#define FUNC_FETCH(MEM, ADDR) (TYPE_FETCH(func, MEM, ADDR))
#define CELL_FETCH(MEM, ADDR) (TYPE_FETCH(cell, MEM, ADDR))
#define BYTE_FETCH(MEM, ADDR) (TYPE_FETCH(byte, MEM, ADDR))
#define MCA_FETCH(MEM, ADDR)  (TYPE_FETCH(mca, MEM, ADDR))


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

#define PPOP    (XPS[0xff & (--XPSP)])
#define PPUSH   (XPS[0xff & (XPSP++)])
#define RPOP    (XRS[0xff & (--XRSP)])
#define RPUSH   (XRS[0xff & (XRSP++)])
#define TOS     (XPS[0xff & (XPSP-1)])
#define NOS     (XPS[0xff & (XPSP-2)])

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

