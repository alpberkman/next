

#ifndef _DTC_H
#define _DTC_H

#define FALSE   (0)
#define TRUE    (-1)


typedef enum power power;
typedef void (*func) (void *arg);
typedef long long int cell;
typedef unsigned char byte;
//typedef cell (*reg);

typedef struct DTC DTC;


enum power {
    OFF = FALSE,
    ON = TRUE,
};

struct DTC {
    power p;
    func  *fp;
    func **tp;
};


func fetch(DTC *dtc);
void exec(func cmd, void *arg);
void tick(DTC *dtc, void *arg);
void runc(DTC *dtc, func *fp, void *arg);

#define MEXT(DTC) ((DTC).fp = (func *) (*((DTC).tp++)))

#define CELL_SIZE (sizeof(cell))
#define BYTE_SIZE (sizeof(byte))
#define FUNC_SIZE (sizeof(func))

#endif





