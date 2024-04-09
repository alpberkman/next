
#define MACRO(M)    NOP); M(vm); PF
#define IF          MACRO(nif)
#define THEN        MACRO(nthen)
#define ELSE        MACRO(nelse)

#define CF(...)         XCF(__VA_ARGS__)
#define YPF(...)         XPF(__VA_ARGS__)
#define PF(...)         YPF(__VA_ARGS__)

//#define LIT(NUM) LLIT, NUM

//#define BRANCH(ADDR)    LIT(ADDR), JMP
//#define BRANCH0(ADDR)   LIT(ADDR), JZ

#define SELF    BRANCH((lp+CELL_SIZE+BYTE_SIZE+(BYTE_VAL(lp+CELL_SIZE)&WORD_LEN)))
#define RECURSE (lp+CELL_SIZE+BYTE_SIZE+(BYTE_VAL(lp+CELL_SIZE)&WORD_LEN))

#define IF(...)     PPUSH = hp+CELL_SIZE;   PF(BRANCH0(0), __VA_ARGS__)
#define THEN(...)   CELL_VAL(PPOP) = hp;    PF(__VA_ARGS__)
#define ELSE(...)   CELL_VAL(PPOP) = hp+CELLS(3); \
                    PPUSH = hp+CELL_SIZE; \
                    PF(BRANCH(0), __VA_ARGS__)

#define BEGIN(...)  PPUSH = hp; PF(__VA_ARGS__)
#define AGAIN(...)  PF(BRANCH(PPOP), __VA_ARGS__)
#define UNTIL(...)  PF(BRANCH0(PPOP), __VA_ARGS__)
#define WHILE(...)  PPUSH = hp+CELL_SIZE; PF(BRANCH0(0), __VA_ARGS__)
#define REPEAT(...) CELL_VAL(PPOP) = hp+CELLS(3); \
                    PF(BRANCH(PPOP), __VA_ARGS__)

#define DO(...)     PPUSH = hp+CELL_SIZE; PPUSH = hp+CELLS(3); PF(LIT(0), DOI, __VA_ARGS__) // first one is leave , the second one is jumpback
#define LOOP(...)   _swap(vm); CELL_VAL(PPOP) = hp+CELLS(3); PF(LIT(PPOP), LOOPI, __VA_ARGS__)
#define PLOOP(...)  _swap(vm); CELL_VAL(PPOP) = hp+CELLS(3); PF(LIT(PPOP), PLOOPI, __VA_ARGS__)
#define UNLOOP // Not immediate
#define LEAVE  // Can be implemented as a regular word since the immediate version just compiles itself
