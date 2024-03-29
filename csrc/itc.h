

#ifndef _ITC_H
#define _ITC_H


#define FALSE   (0)
#define TRUE    (-1)


typedef int cell;
typedef unsigned char byte;
typedef void (*func) (void *arg);

typedef enum power power;
typedef struct stack stack;

typedef struct VM VM;
typedef struct ITC ITC;
typedef struct SPU SPU;
typedef byte *MEM;

typedef enum OP OP;


enum power {
    OFF = FALSE,
    ON = TRUE,
};

struct stack {
    cell s[0x100];
    byte p;
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

enum OP {
    NOP, HALT, LIT, 

    NEXT, NEST, UNNEST, 

    JMP, JZ, EXE, 

    DUP, DROP, SWAP, 
    PUSH, POP, 

    PICK, RICK, 
    LDP, LDR, 
    
    EQ, NEQ, GT, LT, 
    AND, OR, XOR, 
    SHR, SHL, 
    TRU, FLS, 
    
    ADD, SUB, MUL, 
    DIV, MOD, 
    
    LDC, STRC, 
    LDB, STRB, 
    
    FUNC, CELL, BYTE, 
    MEM, 
    KEY, EMIT,
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


byte fetch(VM *vm);
void tick(VM *vm);
void runc(VM *vm);


#define FTH(NAME) \
    void NAME(VM *vm)

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

