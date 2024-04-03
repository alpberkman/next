
#ifndef _FE_H
#define _FE_H


#define FALSE   (0)
#define TRUE    (-1)



typedef struct VM VM;

typedef int cell;
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




#define MEXT(ITC, MEM) \
    (ITC)->ip = CELL_FETCH(MEM, (ITC)->wp); \
    (ITC)->wp += CELL_SIZE

#define MOFF(ITC, MEM) \
    (ITC)->p = OFF

#define MLIT(ITC, MEM) \
    CELL_FETCH(MEM, (ITC)->wp); \
    (ITC)->wp += CELL_SIZE

#define MNEST(ITC, MEM) \
    (ITC)->wp; \
    (ITC)->wp = (ITC)->ip

#define MUNNEST(ITC, MEM) \
    (ITC)->wp

#define MJMP(ITC, MEM) \
    (ITC)->wp

#define MEXE(ITC, MEM) \
    (ITC)->ip


#endif