

#define MEM_SIZE (0x8000)
#define CELL_TYPE signed short
#define BYTE_TYPE unsigned char


typedef enum power power;
typedef CELL_TYPE cell;
typedef BYTE_TYPE byte;
typedef struct SPU SPU;
typedef byte *RAM;
typedef struct VM VM;

typedef enum prim prim;
typedef void (*fun) (VM *vm);


#define FALSE (0)
#define TRUE (-1)

enum power {
    OFF = FALSE,
    ON = TRUE,
};

struct SPU {
    power p;

    cell ip;
    cell wp;

    cell ps[0x100];
    byte psp;

    cell rs[0x100];
    byte rsp;
};

struct VM {
    SPU spu;
    RAM ram;
};


#define TABLE(APPLY) \
    APPLY(NOP, _nop) \
    APPLY(HALT, _halt) \
    APPLY(LIT, _lit) \

enum prim {


    APPLY(NEXT, _next) \
    APPLY(NEST, _nest) \
    APPLY(UNNEST,
    ) \
    APPLY(JMP, ) \
    APPLY(JZ, ) \
    APPLY(EXE,
// Stack
    ) \
    APPLY(DUP, ) \
    APPLY(DROP, ) \
    APPLY(SWAP,
    ) \
    APPLY(PUSH, ) \
    APPLY(POP,
    ) \
    APPLY(PICK, ) \
    APPLY(RICK,
    ) \
    APPLY(LDP, ) \
    APPLY(LDR,
// Logic
    EQ, NEQ, GT, LT,
    AND, OR, XOR,
    SHR, SHL,
    TRU, FLS,
// Arithmetic
    ADD, SUB, MUL,
    DIV, MOD,
// Memory
    LDC, STRC,
    LDB, STRB,
    CELL, BYTE,
    MEM,
// IO
    KEY, EMIT,
};


byte fetch(VM *vm);
void exec(VM *vm, byte opcode);
void tick(VM *vm);
void run(VM *vm);


#define CELL_SIZE (sizeof(cell))
#define BYTE_SIZE (sizeof(byte))

#define CELLS(N) (CELL_SIZE*(N))
#define BYTES(N) (BYTE_SIZE*(N))


#define P   (vm->spu.p)
#define IP  (vm->spu.ip)
#define WP  (vm->spu.wp)
#define PSP (vm->spu.psp)
#define RSP (vm->spu.rsp)
#define PS  (vm->spu.ps)
#define RS  (vm->spu.rs)

#define PPOP    (PS[--PSP])
#define PPUSH   (PS[PSP++])
#define RPOP    (RS[--RSP])
#define RPUSH   (RS[RSP++])

#define READAS(TYPE, VAR)   (*((TYPE *) &(VAR)))
#define READAS_CELL(VAR)    (READAS(cell, VAR))
#define READAS_BYTE(VAR)    (READAS(byte, VAR))

#define CELL_VAL(ADDR) (READAS_CELL(vm->ram[(ADDR)]))
#define BYTE_VAL(ADDR) (READAS_BYTE(vm->ram[(ADDR)]))


#define MEXT(IADDR) \
    cell iaddr = (IADDR); \
    cell addr = CELL_VAL(iaddr); \
    WP += CELL_SIZE; \
    IP = addr;

#define INCIP (IP += BYTE_SIZE)
#define INCWP (WP += CELL_SIZE)

#define LOGICAL(FLAG) (FLAG ? TRUE : FALSE)

#define PRIMS \
    ((fun[]) { \
        _nop, _halt, _lit, \
        _next, _nest, _unnest, \
        _jmp, _jz, _exe, \
        _dup, _drop, _swap, \
        _push, _pop, \
        _pick, _rick, \
        _ldp, _ldr, \
        _eq, _neq, _gt, _lt, \
        _and, _or, _xor, \
        _shr, _shl, \
        _tru, _fls, \
        _add, _sub, _mul, \
        _div, _mod, \
        _ldc, _strc, \
        _ldb, _strb, \
        _cell, _byte, \
        _mem, \
        _key, _emit, \
    })


void _nop(VM *vm);
void _halt(VM *vm);
void _lit(VM *vm);
void _next(VM *vm);
void _nest(VM *vm);
void _unnest(VM *vm);
void _jmp(VM *vm);
void _jz(VM *vm);
void _exe(VM *vm);
void _dup(VM *vm);
void _drop(VM *vm);
void _swap(VM *vm);
void _push(VM *vm);
void _pop(VM *vm);
void _pick(VM *vm);
void _rick(VM *vm);
void _ldp(VM *vm);
void _ldr(VM *vm);
void _eq(VM *vm);
void _neq(VM *vm);
void _gt(VM *vm);
void _lt(VM *vm);
void _and(VM *vm);
void _or(VM *vm);
void _xor(VM *vm);
void _shr(VM *vm);
void _shl(VM *vm);
void _tru(VM *vm);
void _fls(VM *vm);
void _add(VM *vm);
void _sub(VM *vm);
void _mul(VM *vm);
void _div(VM *vm);
void _mod(VM *vm);
void _ldc(VM *vm);
void _strc(VM *vm);
void _ldb(VM *vm);
void _strb(VM *vm);
void _cell(VM *vm);
void _byte(VM *vm);
void _mem(VM *vm);
void _key(VM *vm);
void _emit(VM *vm);




