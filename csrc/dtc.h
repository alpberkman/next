

#ifndef _DTC_H
#define _DTC_H

#define FALSE   (0)
#define TRUE    (-1)


typedef enum power power;
typedef void (*func) (void *arg);
typedef void (*ptr);
typedef long long int i64;
typedef unsigned char byte;
typedef union cell cell;

typedef struct DTC DTC;
typedef struct SPU SPU;
typedef byte *RAM;
typedef struct VM VM;


enum power {
    OFF = FALSE,
    ON = TRUE,
};

union cell {
    i64 i;
    ptr p;
};

struct DTC {
    power p;
    func *fp;
    cell *tp;
};

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


#define P   (dtc->p)
#define FP  (dtc->fp)
#define TP  (dtc->tp)

func fetch(DTC *dtc);
void exec(func f, void *arg);
void tick(DTC *dtc, void *arg);
void runc(DTC *dtc, void *arg);

#define MEXT(DTC) ((DTC).fp = *((DTC).tp++))


/*
#define MHALT(DTC)  ((DTC).p = OFF)
#define MLIT(DTC)   *((DTC).tp++)

#define MNEST(DTC, VAR) (VAR) = (DTC).tp; (DTC).tp = (DTC).fp; MEXT(DTC)
#define UNNEST(DTC, VAR) (DTC).tp = (VAR); MEXT(DTC)

#define JMP(DTC) (DTC).tp
#define EXE(DTC, VAR) (DTC).fp = *(VAR); (DTC).tp++;
*/

#endif
































