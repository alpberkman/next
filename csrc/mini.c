
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
    XPRIMS(jmp,     JMP, NEXT);
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
    XPRIMS(ijmp,        LIT, JMP, NEXT);
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
    //YPRIMS(pploop,  "(+LOOP)",  NEXT);
    XPRIMS(unloop, POP, DROP, POP, DROP, POP, DROP, NEXT);
    XPRIMS(leave, POP, DROP, POP, DROP, POP, JMP, NEXT);

    YPRIMS(pdoes,   "(DOES>)", POP, NEXT);


////////////////////////////////////////////////////////////////////////////////

#define GEQ lt, lit, 0, eq
#define LEQ gt, lit, 0, eq
#define DRAT lit, 1, rick, lit, 0, rick
    //  XCOLON(unloop, pop, pop, drop, pop, drop, pop, drop, push, exit);
    XCOLON(i, lit, 1, rick, exit);
    XCOLON(j, lit, 4, rick, exit);
    //XCOLON(leave, pop, drop, pop, drop, pop, drop, exit);
    YCOLON(pploop,  "(+LOOP)",  // n                | leave-addr limit counter ret-addr
        pop, swap,              // ret-addr n       | leave-addr limit counter
        DRAT, gt,               // ret-addr n flag  | leave-addr limit counter
        swap, pop, add, push,   // ret-addr flag    | leave-addr limit counter+n
        DRAT, LEQ, and,         // ret-addr flag    | leave-addr limit counter+n
        swap, ldc, push);       // flag             | leave-addr limit counter+n do-addr
        IF(unloop); THEN(exit);



    // Begining of colon words

    // Comment words
    YCOLON(bs, "\\"); BEGIN(key, lit, '\n', eq); UNTIL(exit); IMMEDIATE;
    YCOLON(paren, "("); BEGIN(key, lit, ')', eq); UNTIL(exit); IMMEDIATE;


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
    YCOLON(dover,   "2OVER", lit, 3, pick, lit, 3, pick, exit);
    YCOLON(dswap,   "2SWAP", rot, push, rot, pop, exit);

    // Logic words
    YCOLON(zeq,     "0=", lit, 0, eq, exit);
    YCOLON(zlt,     "0<", lit, 0, lt, exit);
    YCOLON(zgt,     "0>", lit, 0, gt, exit);
    YCOLON(zneq,    "0<>", lit, 0, neq, exit);
    YCOLON(geq,     ">=", lt, zeq, exit);
    YCOLON(leq,     "<=", gt, zeq, exit);
    
    // Bitweise words
    XCOLON(invert,  lit, -1, xor, exit);

    // Arithmetic words
    XCOLON(negate,  invert, lit, 1, add, exit);
    XCOLON(abs,     dup, zlt); IF(negate); THEN(exit);
    XCOLON(max,     ddup, lt); IF(swap); THEN(drop, exit);
    XCOLON(min,     ddup, gt); IF(swap); THEN(drop, exit);
    //XCOLON(within,  over, sub, push, sub, pop, ult, exit);
    YCOLON(onep,    "1+", lit, 1, add, exit);
    YCOLON(onem,    "1-", lit, 1, sub, exit);



    // Memory
    YCOLON(pldc,        "+!", swap, over, ldc, add, swap, strc, exit);
    XCOLON(allot,       xhp, pldc, exit);
    YCOLON(comma,       ",", here, xcell, allot, strc, exit);
    YCOLON(ccomma,      "C,", here, xbyte, allot, strb, exit);
    XCOLON(move, qdup); IF(lit, 0); DO(over, i, add, ldb, over, i, add, strb); LOOP(); THEN(ddrop, exit);
    XCOLON(fill, mrot, qdup); IF(lit, 0); DO(over, over, i, add, strb); LOOP(); THEN(ddrop, exit);
//: MOVE ( addr1 addr2 u -- ) 0 MAX 0 ?DO OVER I CHARS + C@ OVER I CHARS + C! LOOP 2DROP ;
//: FILL ( c-addr u char -- ) -ROT 0 ?DO 2DUP C! CHAR+ LOOP 2DROP ;


    // Interpreter words
    XCOLON(literal, POSTPONE(lit), comma, exit); IMMEDIATE;
    YCOLON(compilec,    "COMPILE,", comma, exit);
    YCOLON(imm,         "IMMEDIATE", last, cellp, dup, ldb, lit, MASK_IMM, or, swap, strb, exit);

    // String words
    XCON(bl, ' ');
    XCOLON(count, dup, cellp, swap, ldc, exit);
    YCOLON(xchar, "CHAR"); BEGIN(key, dup, bl, eq); WHILE(drop); REPEAT(exit); IMMEDIATE;
    YCOLON(pchar, "[CHAR]", xchar, POSTPONEI(literal), exit); IMMEDIATE;
    XCOLON(dostr,
        rat, count,
        pop, drop,
        over, over, add, jmp);
    YCOLON(s, "S\"", POSTPONE(dostr), here, xcell, allot); 
        BEGIN(key, dup, lit, '\"', neq); WHILE(comma); REPEAT(here, over, sub, swap, strc, exit); IMMEDIATE;


    // Control flow words
    XCOLON(recurse, last, cellp, dup, ldb, lit, WORD_LEN, and, add, xmca, add, comma, exit); IMMEDIATE;
    YCOLON(xif, "IF", POSTPONE(pif), here, xcell, allot, exit); IMMEDIATE;
    YCOLON(xthen, "THEN", POSTPONE(pthen), here, swap, strc, exit); IMMEDIATE;
    YCOLON(xelse, "ELSE", POSTPONE(pelse), here, xcell, allot, swap, here, swap, strc, exit); IMMEDIATE;

    YCOLON(xbegin, "BEGIN", POSTPONE(pbegin), here, exit); IMMEDIATE;
    YCOLON(xagain, "AGAIN", POSTPONE(pagain), comma, exit); IMMEDIATE;
    YCOLON(xuntil, "UNTIL", POSTPONE(puntil), comma, exit); IMMEDIATE;
    YCOLON(xwhile, "WHILE", POSTPONE(pwhile), here, xcell, allot, exit); IMMEDIATE;
    YCOLON(xrepeat, "REPEAT", POSTPONE(prepeat), swap, comma, here, swap, strc, exit); IMMEDIATE;

    YCOLON(xdo, "DO", POSTPONE(pdo), here, xcell, allot, here, exit); IMMEDIATE;
    YCOLON(xploop, "+LOOP", POSTPONE(pploop), comma, here, swap, strc, exit); IMMEDIATE;
    YCOLON(xloop, "LOOP", lit, 1, POSTPONEI(literal), POSTPONE(pploop), comma, here, swap, strc, exit); IMMEDIATE;





// Helpers for dict
    YCOLON(word_len, "WORD-LEN?", cellp, ldb, lit, WORD_LEN, and, exit);
    YCOLON(word_imm, "WORD-IMM?", cellp, ldb, lit, MASK_IMM, and, exit);
    YCOLON(word_vis, "WORD-VIS?", cellp, ldb, lit, MASK_VIS, and, exit);
    

    XCOLON(lfa,     exit);
    XCOLON(ffa,     lfa, cellp, exit);
    XCOLON(nfa,     ffa, bytep, exit);
    XCOLON(cfa,     dup, nfa, swap, word_len, add, exit);
    XCOLON(pfa,     cfa, mcap, exit);

// link field address (lfa),  
// name field address (nfa), 
// code field address (cfa),
// parameter field address (pfa)


    // Start
    COLD(
        lit, new_hp, xhp, strc, 
        lit, new_lp, xlp, strc, 
        false, state, strc, 
        lit, 10, base, strc,
        bye);


    // For debugging
    printf("hp: %i lp: %i\n", hp, lp);
////////////////////////////////////////////////////////////////////////////////

    hexdump(fth, 16, (hp | 0xf)/16 + 1);
    puts("");
    disasmd(fth);
    puts("");
/*
    XCOLON(TEST1, true, base, ldc, hex, base, ldc, bye);
    DR(TEST1);
    XCOLON(TEST2, lit, 1, lit, 2, lit, 3, lit, 4, dswap, bye);
    DR(TEST2);

    XCOLON(echo5);
        PF(lit, 250, lit, 0); DO(lit, 9); LOOP();

        PF(lit, 300, lit, 0); DO();
            PF(lit, 3, lit, 0); DO(j);
                PF(leave);
            LOOP();
        LOOP(bye);
    DR(echo5);
*/


}