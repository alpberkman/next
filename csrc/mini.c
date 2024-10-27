
#include "imm.h"
#include "prims.h"

#include "mini.h"

#include "tools/debug.h"
#include <stdio.h>

void dict(FTH *fth) {
    //(void) fth;
    hp =  0;
    lp = -1;

    PRIMS("NEXT", NEXT);

    // X -> unique name
    // Y -> manual
    // Z -> add P_

////////////////////////////////////////////////////////////////////////////////

    // Begining of primitive words
    // ITC words
    XPRIMS(nop,     NOP, NEXT);
    XPRIMS(bye,     HALT, NEXT);
    XPRIMS(lit,     LIT, NEXT);
    //XPRIMS(next,    NEXT);
    //XPRIMS(nest,    NEST);
    XPRIMS(exit,    UNNEST);
    //XPRIMS(jmp,     JMP, NEXT);
    //XPRIMS(jz,      JZ, NEXT);
    XPRIMS(execute, EXE, NEXT);
    
    // Stack manipulation and status words
    XPRIMS(dup,     DUP, NEXT);
    XPRIMS(drop,    DROP, NEXT);
    XPRIMS(swap,    SWAP, NEXT);
    YPRIMS(push,    ">R", PUSH, NEXT);
    YPRIMS(pop,     "R>", POP, NEXT);
    XPRIMS(pick,    PICK, NEXT);
    XPRIMS(rick,    RICK, NEXT);
    XPRIMS(depth,   LDP, NEXT);
    XPRIMS(rdepth,  LDR, NEXT);
 
    // Logic operators
    YPRIMS(eq,      "=", EQ, NEXT);
    YPRIMS(neq,     "<>", NEQ, NEXT);
    YPRIMS(gt,      ">", GT, NEXT);
    YPRIMS(lt,      "<", LT, NEXT);
   
    // Bitweise operators
    XPRIMS(and,     AND, NEXT);
    XPRIMS(or,      OR, NEXT);
    XPRIMS(xor,     XOR, NEXT);
    XPRIMS(rshift,  SHR, NEXT);
    XPRIMS(lshift,  SHL, NEXT);

    // Arithmethic operators
    YPRIMS(add,     "+", ADD, NEXT);
    YPRIMS(sub,     "-", SUB, NEXT);
    YPRIMS(mul,     "*", MUL, NEXT);
    YPRIMS(div,     "/", DIV, NEXT);
    XPRIMS(mod,     MOD, NEXT);

    // Memory read and write operators
    YPRIMS(ldc,     "@", LDC, NEXT);
    YPRIMS(strc,    "!", STRC, NEXT);
    YPRIMS(ldb,     "C@", LDB, NEXT);
    YPRIMS(strb,    "C!", STRB, NEXT);

    // C function calls
    XPRIMS(call, CALL, NEXT);

    // IO operators
    XPRIMS(key,     KEY, NEXT);
    XPRIMS(emit,    EMIT, NEXT);


    // Begining of higher primitive words
    // Flow control
    //XPRIMS(ijmp,        LIT, JMP, NEXT);
    //XPRIMS(ijz,         LIT, JZ, NEXT);
    //XPRIMS(iexecute,    LIT, EXE, NEXT);
    //XPRIMS(wp,      POP, DUP, PUSH, NEXT);

    YPRIMS(pif,     "(IF)",     LIT, JZ, NEXT);
    YPRIMS(pthen,   "(THEN)",   NEXT);
    YPRIMS(pelse,   "(ELSE)",   LIT, JMP, NEXT);

    YPRIMS(pbegin,  "(BEGIN)",  NEXT);
    YPRIMS(pagain,  "(AGAIN)",  LIT, JMP, NEXT);
    YPRIMS(puntil,  "(UNTIL)",  LIT, JZ, NEXT);
    YPRIMS(pwhile,  "(WHILE)",  LIT, JZ, NEXT);
    YPRIMS(prepeat, "(REPEAT)", LIT, JMP, NEXT);

    YPRIMS(pdo,     "(DO)",     LIT, PUSH, SWAP, PUSH, PUSH, NEXT);
    YPRIMS(pploop,  "(+LOOP)",  NEXT);

////////////////////////////////////////////////////////////////////////////////

    // Begining of colon words
    // Variables
    // DOES> part of variable
    XDOES(dovar,    exit);
    // Interprete/compiler variables
    XVAR(state);
    YVAR(xhp, "hp");
    YVAR(xlp, "lp");
    XCOLON(here, xhp, ldc, exit);
    XCOLON(last, xlp, ldc, exit);
    // Base
    XVARINIT(base, 10);
    XCOLON(hex, lit, 16, base, strc, exit);
    XCOLON(decimal, lit, 10, base, strc, exit);




    // Constants
    // DOES> part of constant
    XDOES(docon,    ldc, exit);
    // Logical values
    XCON(true, TRUE);
    XCON(false, FALSE);
    // Size values
    XCON(mems, MEM_SIZE);
    YCON(xfunc, "func", FUNC_SIZE);
    YCON(xcell, "cell", CELL_SIZE);
    YCON(xbyte, "byte", BYTE_SIZE);
    YCON(xmca,  "mca", MCA_SIZE);
    YCOLON(funcp,   "FUNC+", xfunc, add, exit);
    YCOLON(cellp,   "CELL+", xcell, add, exit);
    YCOLON(bytep,   "BYTE+", xbyte, add, exit);
    YCOLON(mcap,    "MCA+", xmca, add, exit);
    XCOLON(cells,   xcell, mul, exit);
    XCOLON(bytes,   xbyte, mul, exit);
    // Special constants
    XCON(bl, ' ');





    // Stack words
    XCOLON(over,    lit, 1, pick, exit);
    XCOLON(nip,     swap, drop, exit);
    XCOLON(tuck,    swap, over, exit);
    YCOLON(rat,     "R@", lit, 1, rick, exit);
    XCOLON(rot,     push, swap, pop, swap, exit);
    YCOLON(mrot,    "-rot", rot, rot, exit);
    YCOLON(qdup,    "?DUP", dup); IF(dup); THEN(exit);
    YCOLON(ddup,    "2DUP", over, over, exit);
    YCOLON(ddrop,   "2DROP", drop, drop, exit);

    // Logic words
    YCOLON(zeq,     "0=", lit, 0, eq, exit);
    YCOLON(zlt,     "0<", lit, 0, lt, exit);
    YCOLON(zgt,     "0>", lit, 0, gt, exit);
    YCOLON(zneq,    "0<>", lit, 0, neq, exit);
    YCOLON(geq,     ">=", lt, zeq, exit);
    YCOLON(leq,     "<=", gt, zeq, exit);

    // Arithmetic words
    XCOLON(invert,  lit, -1, xor, exit);
    XCOLON(negate,  invert, lit, 1, add, exit);
    XCOLON(abs,     dup, zlt); IF(negate); THEN(exit);
    XCOLON(max,     ddup, lt); IF(swap); THEN(drop, exit);
    XCOLON(min,     ddup, gt); IF(swap); THEN(drop, exit);
    //XCOLON(within,  over, sub, push, sub, pop, ult, exit);
    YCOLON(onep,    "1+", lit, 1, add, exit);


    //XDOES(dostr,    dup, ldc, swap, cellp, bye);

//and variables
    // CREATE ... DOES> like words





    // Other constants









// Helpers for dict
    YCOLON(word_len, "WORD-LEN?", cellp, ldb, lit, WORD_LEN, and, bye);
    YCOLON(word_imm, "WORD-IMM?", cellp, ldb, lit, MASK_IMM, and, bye);
    YCOLON(word_vis, "WORD-VIS?", cellp, ldb, lit, MASK_VIS, and, bye);
    

    XCOLON(lfa,     bye);
    XCOLON(ffa,     lfa, cellp, bye);
    XCOLON(nfa,     ffa, bytep, bye);
    XCOLON(cfa,     dup, nfa, swap, word_len, add, bye);
    XCOLON(pfa,     cfa, mcap, bye);

// link field address (lfa),  
// name field address (nfa), 
// code field address (cfa),
// parameter field address (pfa)



    hexdump(fth, 16, (hp | 0xf)/16 + 1);
    puts("");
    disasmd(fth);
    puts("");

    XCOLON(TEST1, true, base, ldc, hex, base, ldc, bye);
    DR(TEST1);
}