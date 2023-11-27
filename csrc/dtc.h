

#ifndef _DTC_H
#define _DTC_H

#define FALSE           (0)
#define TRUE            (-1)
#define LOGICAL(FLAG)   ((FLAG) ? TRUE : FALSE)


#define CELL_TYPE cell
#define BYTE_TYPE byte

#define CELL_SIZE (sizeof(cell))
#define BYTE_SIZE (sizeof(byte))

#define CELLS(N) (CELL_SIZE*(N))
#define BYTES(N) (BYTE_SIZE*(N))


typedef enum pwr pwr;
typedef void (*fun) (void *arg);
typedef long long int i64;
typedef unsigned char byte;
typedef union cell cell;
typedef cell (*reg);

typedef struct DTC DTC;


enum pwr {
    OFF = FALSE,
    ON = TRUE,
};
/*
union ptr {
    void *v;
    func *f;
    cell *c;
    byte *b;
};
*/
union cell {
    cell *cp;
    byte *bp;
    i64 i;
    fun f;
};

struct DTC {
    pwr p;
    reg fp;
    reg tp;
};


fun fetch(DTC *dtc);
void exec(fun f, void *arg);
void tick(DTC *dtc, void *arg);
void runc(DTC *dtc, void *arg);

#define MEXT(DTC) ((DTC).fp = (*((DTC).tp++)).cp)


/*
#define MHALT(DTC)  ((DTC).p = OFF)
#define MLIT(DTC)   *((DTC).tp++)

#define MNEST(DTC, VAR) (VAR) = (DTC).tp; (DTC).tp = (DTC).fp; MEXT(DTC)
#define UNNEST(DTC, VAR) (DTC).tp = (VAR); MEXT(DTC)

#define JMP(DTC) (DTC).tp
#define EXE(DTC, VAR) (DTC).fp = *(VAR); (DTC).tp++;
*/

#endif





