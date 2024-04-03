

#ifndef _ITC_H
#define _ITC_H

#include "macro.h"
#include "prims.h"


typedef struct VM VM;

typedef long long cell;
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




#endif

