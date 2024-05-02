#include "tests.h"
#include "debug.h"

void test(VM *vm) {
    (void) vm;
     // Begining of tests

/*
    XCOLON(ASDF,true, dup, swap, add, halt, unnest);
    XCOLON(qwer,ASDF, dup, swap, add, halt, unnest); IMMEDIATE;
    XCOLON(test1, lit, 1, false, dup, xfunc, unnest);
    XCOLON(test2, lit, 2, test1, lit, 22, halt);
    XCOLON(test3, lit, test1, execute, halt);


    XCOLON(r1, lit, 1, unnest);
    XCOLON(r2, r1, dup, lit, 1, add, unnest);
    XCOLON(r3, r2, dup, lit, 1, add, unnest);
    XCOLON(test4, r3, r3, iexecute, r2, dup, add, halt, halt);

    XCOLON(test5, r3, r3, irjmp, 8, xbyte, xcell, xfunc, lit, 0, halt);
    XCOLON(test6, r3, r3, ijmp, test2+1, halt);

    XCOLON(test8, lit, 1, dup, lit, 5, sub, xbyte, dup, xcell, xfunc, lit, 123, halt);
    XCOLON(test7, lit, 1, add, dup, lit, 5, sub, irjz, CELL_SIZE, test7, halt, halt);


    penum2func();
    puts("");
    pwords(vm);
    puts("");
    hexdump(vm, 16, (hp | 0xf)/16 + 1);
    puts("");

    DR(test8);

    DR(test3);

    DR(test3);

    DR(test4);

    DR(test5);
    */
}