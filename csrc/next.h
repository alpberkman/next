

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

#define ENUM(E, F)  E,
#define FUN(E, F)   F,
#define ENAME(E, F) #E,
#define FSIG(E, F) void F (VM *vm);
#define FTAB(E, F) [E] = F,
#define TABLE(APPLY) \
    APPLY(NOP,  _nop) \
    APPLY(HALT, _halt) \
    APPLY(LIT,  _lit) \
    APPLY(NEXT, _next) \
    APPLY(NEST, _nest) \
    APPLY(UNNEST, _unnest) \
    APPLY(JMP,  _jmp) \
    APPLY(JZ,   _jz) \
    APPLY(EXE,  _exe) \
    APPLY(DUP,  _dup) \
    APPLY(DROP, _drop) \
    APPLY(SWAP, _swap) \
    APPLY(PUSH, _push) \
    APPLY(POP,  _pop) \
    APPLY(PICK, _pick) \
    APPLY(RICK, _rick) \
    APPLY(LDP,  _ldp) \
    APPLY(LDR,  _ldr) \
    APPLY(EQ,   _eq) \
    APPLY(NEQ,  _neq) \
    APPLY(GT,   _gt) \
    APPLY(LT,   _lt) \
    APPLY(AND,  _and) \
    APPLY(OR,   _or) \
    APPLY(XOR,  _xor) \
    APPLY(SHR,  _shr) \
    APPLY(SHL,  _shl) \
    APPLY(TRU,  _tru) \
    APPLY(FLS,  _fls) \
    APPLY(ADD,  _add) \
    APPLY(SUB,  _sub) \
    APPLY(MUL,  _mul) \
    APPLY(DIV,  _div) \
    APPLY(MOD,  _mod) \
    APPLY(LDC,  _ldc) \
    APPLY(STRC, _strc) \
    APPLY(LDB,  _ldb) \
    APPLY(STRB, _strb) \
    APPLY(CELL, _cell) \
    APPLY(BYTE, _byte) \
    APPLY(MEM,  _mem) \
    APPLY(KEY,  _key) \
    APPLY(EMIT, _emit)

enum prim {
    TABLE(ENUM)
};

#define LUT ((fun[]) { TABLE(FUN) })


byte fetch(VM *vm);
void exec(VM *vm, byte opcode);
void tick(VM *vm);
void run(VM *vm);

TABLE(FSIG)


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








