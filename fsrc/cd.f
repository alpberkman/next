: CONSTANT
  CREATE ,
  DOES> @
;

: VARIABLE
  CREATE 0,
  DOES>
;


: ENUM ( -- )
  CREATE 0 ,
  DOES> DUP @ DUP 1+ ROT ! CONSTANT
;

: ARRAY ( n -- )
  CREATE CELLS ALLOT
  DOES> SWAP CELLS +
;

: COUNTED-ARRAY ( n -- )
  CREATE DUP , CELLS ALLOT
  DOES> CELL+ SWAP CELLS +
;

: SIZEOF -1 ;


: TIMES ' SWAP 0 DO DUP >R EXECUTE R> LOOP DROP ;

3 times .s

\ Skips next n inlined arguements
\ lit, n, skip, 0, 1, ... , n-1 <jump to here>
: SKIP ( n -- ) ( R: ret-addr -- ret-addr+n*cell)
    R> R> ROT CELLS + >R >R ;