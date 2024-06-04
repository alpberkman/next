
#include "next.h"
#include "imm.h"
#include "prims.h"

#include "tools/debug.h"

#include <stdio.h>


void dict(VM *vm) {
    //(void) vm;
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
    XPRIMS(next,    NEXT);
    XPRIMS(nest,    NEST);
    XPRIMS(exit,  UNNEST);
    XPRIMS(jmp,     JMP, NEXT);
    XPRIMS(jz,      JZ, NEXT);
    XPRIMS(execute, EXE, NEXT);
    XPRIMS(rjmp,    RJMP, NEXT);
    XPRIMS(rjz,     RJZ, NEXT);
    
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

    // Math operators
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
    XPRIMS(ijz,         LIT, JZ, NEXT);
    XPRIMS(iexecute,    LIT, EXE, NEXT);
    XPRIMS(irjmp,       LIT, RJMP, NEXT);
    XPRIMS(irjz,        LIT, RJZ, NEXT);

////////////////////////////////////////////////////////////////////////////////

    // Begining of colon words
    // Constants and variables
    // CREATE ... DOES> like words
    XCOLON(dovar,   pop, exit);
    XCOLON(docon,   pop, ldc, exit);

    // Logical values
    XCON(true, TRUE);
    XCON(false, FALSE);

    // Size values
    YCON(xfunc, "func", FUNC_SIZE);
    YCON(xcell, "cell", CELL_SIZE);
    YCON(xbyte, "byte", BYTE_SIZE);
    YCON(xmca,  "mca", MCA_SIZE);
    XCON(mems, MEM_SIZE);
    YCOLON(cellp,   "CELL+", xcell, add, exit);
    YCOLON(bytep,   "BYTE+", xbyte, add, exit);
    YCOLON(mcap,   "MCA+", xmca, add, exit);
    YCOLON(cellm,   "CELL-", xcell, sub, exit);
    YCOLON(bytem,   "BYTE-", xbyte, sub, exit);
    XCOLON(cells,   xcell, mul, exit);
    XCOLON(bytes,   xbyte, mul, exit);

    // Important variables
    YVAR(xhp, "hp");
    YVAR(xlp, "lp");
    XVAR(state);

    // Other constants
    XCOLON(here, xhp, ldc, exit);
    XCOLON(last, xlp, ldc, exit);
    XCON(bl, ' ');

////////////////////////////////////////////////////////////////////////////////

    // Stack words
    XCOLON(over,    lit, 1, pick, exit);
    XCOLON(nip,     swap, drop, exit);
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
    YCOLON(ult,     "U<", ddup, xor, zlt); IF(swap, drop, zlt, exit); THEN(sub, zlt, exit);
    YCOLON(geq,     ">=", lt, zeq, exit);
    YCOLON(leq,     "<=", gt, zeq, exit);

    // Arithmetic words
    XCOLON(invert,  lit, -1, xor, exit);
    XCOLON(negate,  invert, lit, 1, add, exit);
    XCOLON(abs,     dup, zlt); IF(negate); THEN(exit);
    XCOLON(max,     ddup, lt); IF(swap); THEN(drop, exit);
    XCOLON(within,  over, sub, push, sub, pop, ult, exit);
    YCOLON(onep,    "1+", lit, 1, add, exit);

    // Machine words
    XCOLON(alligned,    dup, xcell, mod, xcell, swap, sub, xcell, mod, add, exit);
    YCOLON(pldc,        "+!", swap, over, ldc, add, swap, strc, exit);
    XCOLON(allot,       xhp, pldc);
    YCOLON(comma,       ",", here, xcell, allot, strc);

    // String words
    XCOLON(count, dup, cellp, swap, ldc, exit);

    // Other CREATE ... DOES> like words
/*    XCOLON(dostr,
        rat, cellp, 
        rat, ldc,
        pop, over, add, cellp, jmp);
    XCOLON(dostr,
        rat, count,
        dup, pop, add, cellp, jmp);
*/
    XCOLON(dostr,
        rat, count,
        pop, drop,
        over, over, add, jmp);



    XCOLON(unloop, pop, pop, drop, pop, drop, pop, drop, push, exit);
    XCOLON(i, lit, 1, rick, exit);
    XCOLON(j, lit, 4, rick, exit);
    XCOLON(leave, pop, drop, pop, drop, pop, drop, exit);
    YCOLON(pploop,  "[+loop]", 
        pop, swap,
        lit, 0, rick, lit, 1, rick, lt,
        pop, rot, add, push, 
        lit, 0, rick, lit, 1, rick, geq, and);
        IF(cellp, unloop); ELSE(ldc); THEN(push, exit);
    YCOLON(pdo,     "[do]", pop, dup, ldc, push, mrot, swap, push, push, cellp, push, exit);
    // Start
    COLD(lit, new_hp, xhp, strc, lit, new_lp, xlp, strc, false, state, strc, bye);


    // For debugging
    printf("%i %i\n", hp, lp);

    penum2func();
    puts("");
    disasmd(vm);
    puts("");
    hexdump(vm, 16, (hp | 0xf)/16 + 1);
    puts("");




////////////////////////////////////////////////////////////////////////////////

XCOLON(XXXXX, lit, MEM_SIZE, exit);

    XCON(test1, 123);
    XCOLON(test2, test1, bye);
    DR(test2);

    XVAR(test3);
    XCOLON(test4, lit, 546, test3, strc, test3, ldc, bye);
    DR(test4);
   
   XCOLON(test5, xbyte, mems, false, bye);
   DR(test5);



   XCOLON(test6, false);
   IF(true, true, true, true);
   ELSE(false, false, false, false);
   THEN(lit, 134, bye);
   DR(test6);

    XCOLON(test7, lit, 123);
    STR("Hello World!");
    PF(lit, 456, bye);


    DR(test7);


    XCOLON(test8, lit, 123);
    CCALL(stacks);
    PF(lit, 456, bye);
    DR(test8);


    XCOLON(t9, key, dup, lit, 41, neq);
    IF(emit);//, ijmp, t9+1);
    RECURSE;
    THEN(drop, bye);
    //DR(t9);

    XCOLON(t10, lit, 16+0, alligned, lit, 16+1, alligned, lit, 16+2, alligned, lit, 16+3, alligned, lit, 16+4, alligned, lit, 16+5, alligned, bye);
    DR(t10);

    hexdump(vm, 16, (hp | 0xf)/16 + 1);
    puts("");

    XCOLON(t11, lit, 1, lit, 3, lt, bye);
    DR(t11);
    //DR(t9);

    XCOLON(echo);
    BEGIN(key, emit);
    AGAIN();

    XCOLON(echo2);
    BEGIN(key, dup, emit, lit, 'q', eq);
    UNTIL(bye);

    XCOLON(echo3);
    BEGIN(key, dup, lit, 'q', neq);
    WHILE(emit);
    REPEAT(drop, bye);

    XCOLON(echo4, lit, 84, lit, 0);
    DO(i, lit, 3, lit, 0);
        DO(i, leave);
        LOOP(lit, 667, lit, 1);
    PLOOP(bye);

    XCOLON(echo5);
        PF(lit, 250, lit, 0); DO(lit, 9); LOOP();

        PF(lit, 1000, lit, 0); DO();
            PF(lit, 3, lit, 0); DO(j);
                PF(leave);
            LOOP();
        LOOP(bye);

    XCOLON(echo6);
        PF(lit, 1000, lit, 0); DO();
            PF(lit, 3, lit, 0); DO(j);
                PF(j, lit, 10, eq);
                IF(unloop, leave); THEN();
            LOOP();
        LOOP(bye);

    XCOLON(echo7);
        PF(lit, 1000, lit, 0); DO();
            PF(lit, 3, lit, 0); DO(j);
                PF(j, lit, 10, eq);
                IF(unloop, unloop, bye); THEN();
            LOOP();
        LOOP(bye);


    disasmd(vm);
    puts("");
    hexdump(vm, 16, (hp | 0xf)/16 + 1);
    puts("");
    DR(echo7);


;;;;;
}

