

#ifndef _DTC_H
#define _DTC_H

#define FALSE   (0)
#define TRUE    (-1)


typedef enum pwr pwr;
typedef void (*func) (void *arg);
typedef long long int cell;
typedef unsigned char byte;
typedef cell (*reg);

typedef struct DTC DTC;


enum pwr {
    OFF = FALSE,
    ON = TRUE,
};

struct DTC {
    pwr p;
    reg fp;
    reg tp;
};


func fetch(DTC *dtc);
void exec(func cmd, void *arg);
void tick(DTC *dtc, void *arg);
void runc(DTC *dtc, cell fp, void *arg);

#define MEXT(DTC) ((DTC).fp = (reg) (*((DTC).tp++)))

#endif





