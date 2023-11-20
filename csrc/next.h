

#define MASK_VIS (1<<7)
#define MASK_IMM (1<<6)
#define WORD_LEN (31)


#define MEM_SIZE (0x8000)

#define FALSE (0)
#define TRUE (-1)

#define CELL_SIZE ((cell) sizeof(cell))
#define BYTE_SIZE ((cell) sizeof(byte))


typedef enum power power;
typedef short cell;
typedef unsigned char byte;
typedef struct SPU SPU;
typedef byte *RAM;
typedef struct VM VM;

typedef enum prim prim;
typedef void (*fun) (VM *vm);


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

enum prim {
    NOP, HALT, LIT,
// Controlflow
    NEXT, NEST, UNNEST,
    JMP, JZ, EXE,
// Stack
    DUP, DROP, SWAP,
    PUSH, POP,
    PICK, RICK,
    LDP, LDR,
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

#define PPOP    vm->spu.ps[--vm->spu.psp]
#define PPUSH   vm->spu.ps[vm->spu.psp++]
#define RPOP    vm->spu.rs[--vm->spu.rsp]
#define RPUSH   vm->spu.rs[vm->spu.rsp++]

#define CELL_VAL(ADDR) (*((cell *) &(vm->ram[(ADDR)])))
#define BYTE_VAL(ADDR) (*((byte *) &(vm->ram[(ADDR)])))

#define INCIP (vm->spu.ip += BYTE_SIZE)
#define INCWP (vm->spu.wp += CELL_SIZE)

#define MACRO_NEXT \
    cell addr = CELL_VAL(vm->spu.wp); \
    INCWP; \
    vm->spu.ip = addr;

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




