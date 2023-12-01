

#ifndef _DTC_H
#define _DTC_H

#define FALSE   (0)
#define TRUE    (-1)


typedef void (*func) (void *arg);
typedef long long int cell;
typedef unsigned char byte;

typedef struct DTC DTC;
typedef enum power power;
typedef cell REG;


enum power {
    OFF = FALSE,
    ON = TRUE,
};

struct DTC {
    power p;
    REG fp;
    REG tp;
};


#define FUNC_SIZE (sizeof(func))
#define CELL_SIZE (sizeof(cell))
#define BYTE_SIZE (sizeof(byte))


func fetch(DTC *dtc, byte *mem);
void exec(func f, void *arg);
void tick(DTC *dtc, byte *mem, void *arg);
void runc(DTC *dtc, byte *mem, void *arg, cell addr);


#define MEXT(DTC, MEM) \
    (DTC).fp = *((cell *) &((MEM)[(DTC).tp])); \
    (DTC).tp += CELL_SIZE;

#define MOFF(DTC, MEM) \
    (DTC).p = OFF

#define MLIT(DTC, MEM) \
    *((cell *) &((MEM)[(DTC).tp])); \
    (DTC).tp += CELL_SIZE

#define MNEST(DTC, MEM) \
    (DTC).tp; \
    (DTC).tp = (DTC).fp

#define MUNNEST(DTC, MEM) \
    (DTC).tp

#define MJMP(DTC, MEM) \
    (DTC).tp

#define MEXE(DTC, MEM) \
    (DTC).fp

#endif

