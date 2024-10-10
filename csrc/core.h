
#ifndef _CORE_H
#define _CORE_H


#define MEM_SIZE (0x8000)
#define MASK_VIS (1<<7)
#define MASK_IMM (1<<6)
#define WORD_LEN (31)

#define FALSE   (0)
#define TRUE    (-1)


typedef struct FTH FTH;
typedef void (*func) (FTH *fth);

typedef int cell;
typedef unsigned char byte;
typedef byte mca;

typedef enum power power;
typedef struct stack stack;

typedef struct ITU ITU;
typedef struct SPU SPU;
typedef byte MEM[MEM_SIZE];


enum power {
    OFF = FALSE,
    ON = TRUE,
};

struct stack {
    cell s[0x100];
    byte sp;
};

struct ITU {
    power p;
    cell ip;
    cell wp;
};

struct SPU {
    stack p;
    stack r;
};

struct FTH {
    ITU itu;
    SPU spu;
    MEM mem;
};


mca fetch(FTH *fth);
void exec(FTH *fth, mca addr);
void tick(FTH *fth);
void runc(FTH *fth, cell addr);
void rund(FTH *fth, cell addr, func debug);
void init(FTH *fth);


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


#define XITU (fth->itu)
#define XP   (fth->itu.p)
#define XIP  (fth->itu.ip)
#define XWP  (fth->itu.wp)

#define XSPU (fth->spu)
#define XPSP (fth->spu.p.sp)
#define XRSP (fth->spu.r.sp)
#define XPS  (fth->spu.p.s)
#define XRS  (fth->spu.r.s)

#define XMEM (fth->mem)


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