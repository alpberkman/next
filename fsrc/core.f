
\ Try dpans94 from stdref


\ Extra
VARIABLE HP ( -- a-addr )
VARIABLE LP ( -- a-addr )
sizeof(func) CONSTANT FUNC
sizeof(cell) CONSTANT CELL
sizeof(byte) CONSTANT BYTE
sizeof(mca) CONSTANT MCA
: LAST LP @ ;
\ To deal with -ROT and ?DO


\ Memory
B: ! ( x a-addr -- ) ;
B: @ ( a-addr -- x ) ;
B: C! ( char c-addr -- ) ;
B: C@ ( c-addr -- char ) ;
: ALIGNED ( addr -- a-addr ) DUP CELL MOD CELL SWAP - CELL MOD + ;
: ALIGN ( -- ) HERE ALIGNED HP ! ;
: 2! ( x1 x2 a-addr -- ) SWAP OVER ! CELL+ ! ;
: 2@ ( a-addr -- x1 x2 ) DUP CELL+ @ SWAP @ ;
: , ( x -- ) HERE CELL ALLOT ! ;
: C, ( char -- ) HERE BYTE ALLOT C! ;
: CELL+ ( a-addr1 -- a-addr2 ) CELL + ;
: CHAR+ ( c-addr1 -- c-addr2 ) BYTE+ ;
: CELLS ( n1 -- n2 ) CELL * ;
: CHARS ( n1 -- n2 ) BYTES ;
: +! ( n|u a-addr -- ) SWAP OVER @ + SWAP ! ;
: ALLOT ( n -- ) HP +! ;
: HERE ( -- addr ) HP @ ;
: FILL ( c-addr u char -- ) -ROT 0 ?DO 2DUP C! CHAR+ LOOP 2DROP ;
: LITERAL ( x -- ) ( -- x ) POSTPONE LIT , ; IMMEDIATE
: MOVE ( addr1 addr2 u -- ) 0 MAX 0 ?DO OVER I CHARS + C@ OVER I CHARS + C! LOOP 2DROP ;



\ Interpreter
VARIABLE STATE ( -- a-addr )
VARIABLE BASE ( -- a-addr )
B: EXECUTE ( i*x xt -- j*x ) ;
: [ TRUE STATE ! ; IMMEDIATE
: ] FALSE STATE ! ;
: CHAR ( "<spaces>name" -- char ) BL WORD CELL+ C@ ;
: [CHAR] ( "<spaces>name" -- ) CHAR POSTPONE LITERAL ; IMMEDIATE
: IMMEDIATE ( -- ) LAST CELL+ DUP @ [ 1 6 LSHIFT ] LITERAL OR SWAP ! ;
: DECIMAL ( -- ) 10 BASE ! ;
N: ' ;
: ['] ( "<spaces>name" -- ) ( -- xt ) ' POSTPONE LITERAL ; IMMEDIATE
N: ; ;
N: CHAR ;
N: CONSTANT ;
N: VARIABLE                 ;
N: CREATE ;
N: DOES> ; IMMEDIATE
N: POSTPONE ; IMMEDIATE
N: : ;
N: ABORT ;
N: ABORT" ;
N: QUIT ;
N: >BODY ;
N: EVALUATE ;
N: FIND ;
N: SOURCE ;
N: WORD ;

\ Math
B: + ( n1|u1 n2|u2 -- n3|u3 ) ;
B: - ( n1|u1 n2|u2 -- n3|u3 ) ;
B: * ( n1|u1 n2|u2 -- n3|u3 ) ;
B: / ( n1 n2 -- n3 ) ;
B: MOD ( n1 n2 -- n3 );
: 1+ ( n1|u1 -- n2|u2 ) 1 + ;
: 1- ( n1|u1 -- n2|u2 ) 1 - ;
: 2* ( x1 -- x2 ) 1 LSHIFT ;
: 2/ ( x1 -- x2 ) 1 RSHIFT ;
: ABS ( n -- u ) DUP 0< IF NEGATE THEN ;
: MAX ( n1 n2 -- n3 ) 2DUP < IF SWAP THEN DROP ;
: MIN ( n1 n2 -- n3 ) 2DUP > IF SWAP THEN DROP ;
: NEGATE ( n1 -- n2 ) INVERT 1+ ;
: S>D ( n -- d ) DUP 0< IF -1 ELSE 0 THEN ;
: U< ( u1 u2 -- flag ) 2DUP XOR 0< IF SWAP DROP ELSE - THEN 0< ;
B: M* ( n1 n2 -- d ) ;  
B: FM/MOD ( d1 n1 -- n2 n3 ) ;
B: SM/REM (  d1 n1 -- n2 n3 ) ;
B: UM* ( u1 u2 -- ud ) ;
N: UM/MOD ( ud u1 -- u2 u3 ) ;
: /MOD ( n1 n2 -- n3 n4 ) >R S>D R> FM/MOD ;
: */MOD ( n1 n2 n3 -- n4 n5 ) >R M* R> FM/MOD ;
: */ ( n1 n2 n3 -- n4 ) */MOD SWAP DROP ;


\ Looping and logic structures
B: EXIT ( -- ) ( R: nest-sys -- ) ;
B: IRJZ ( flag offset -- ) ;
B: IRJMP ( offset -- ) ;
: RECURSE ( -- ) LAST CELL+ DUP C@ 31 OR + BYTE+ , ;
: IF ( C: -- orig ) ( x -- ) POSTPONE IRJZ HERE CELL ALLOT ; IMMEDIATE
: THEN ( C: orig -- ) ( -- ) HERE OVER - CELL - SWAP ! ; IMMEDIATE
: ELSE ( C: orig1 -- orig2 ) ( -- ) POSTPONE IRJMP HERE CELL ALLOT SWAP POSTPONE THEN ; IMMEDIATE
N: DO ; IMMEDIATE
N: LOOP ; IMMEDIATE
N: +LOOP ; IMMEDIATE
N: UNLOOP ;
N: I ;
N: J ;
N: LEAVE ;
N: BEGIN ( C: -- dest ) ( -- ) HERE ; IMMEDIATE
N: UNTIL ( C: dest -- ) ( x -- ) POSTPONE IRJZ HERE - CELL - , ; IMMEDIATE
N: WHILE ( C: dest -- orig dest ) ( x -- ) POSTPONE IRJZ HERE CELL ALLOT ; IMMEDIATE
N: REPEAT ( C: orig dest -- ) ( -- ) POSTPONE IRJMP SWAP HERE - CELL - , HERE OVER - CELL - SWAP ! ; IMMEDIATE




\ String
32 CONSTANT BL ( -- char )
: SPACE ( -- ) BL EMIT ;
: SPACES ( n -- ) 0 MAX 0 ?DO SPACE LOOP ;
: CR ( -- ) 13 EMIT 10 EMIT ;
: ( ( "ccc<paren>" -- ) [CHAR] ) PARSE 2DROP ;              \ Not happy because of parse, should something that doesnt dpend on a buffer
: ." ( "ccc<quote>" -- ) [CHAR] " PARSE TYPE ; IMMEDIATE
: COUNT DUP CELL+ SWAP @ ;
N: . ;
N: U. ;
N: >NUMBER ;
N: <# ;
N: # ;
N: #s ;
N: #> ;
N: ACCEPT ;
N: ENVIRONMENT? ;
N: SIGN ;
N: >IN ;
N: HOLD ;
N: S" ;

\ Stack
B: DUP ( x -- x x ) ;
B: DROP ( x -- ) ;
B: SWAP ( x1 x2 -- x2 x1 ) ;
B: >R ( x -- ) ( R: -- x ) ;
B: R> ( -- x ) ( R: x -- ) ;
B: DEPTH ( -- +n ) ;
: R@ ( -- x ) ( R: x -- x ) 1 RICK ;
: ROT ( x1 x2 x3 -- x2 x3 x1 ) >R SWAP R> SWAP ;
: OVER ( x1 x2 -- x1 x2 x1 ) 1 PICK ;
: ?DUP ( x -- 0 | x x ) DUP IF DUP THEN ;
: 2SWAP ( x1 x2 x3 x4 -- x3 x4 x1 x2 ) >R -ROT R> -ROT ;
: 2DROP ( x1 x2 -- ) DROP DROP ;
: 2DUP ( x1 x2 -- x1 x2 x1 x2 ) OVER OVER ;
: 2OVER ( x1 x2 x3 x4 -- x1 x2 x3 x4 x1 x2 ) 3 PICK 3 PICK ;

\ Logic
B: = ( x1 x2 -- flag ) ;
B: > ( n1 n2 -- flag ) ;
B: < ( n1 n2 -- flag ) ;
B: OR ( x1 x2 -- x3 ) ;
B: XOR ( x1 x2 -- x3 ) ;
B: AND ( x1 x2 -- x3 ) ;
B: RSHIFT ( x1 u -- x2 ) ;
B: LSHIFT ( x1 u -- x2 ) ;
: 0< ( n -- flag ) 0 < ;
: 0= ( x -- flag ) 0 = ;
: INVERT ( x1 -- x2 ) -1 XOR ;

\ IO
B: EMIT ( x -- ) ;
B: KEY ( -- char ) ;
: TYPE ( c-addr u -- ) 0 MAX 0 ?DO DUP C@ EMIT CHAR+ LOOP DROP ;

\ Extension
N: #TIB ;
: .( ( "ccc<paren>" -- ) [CHAR] ) PARSE TYPE ; IMMEDIATE
N: .R ;
: 0<> ( x -- flag ) 0 <> ;
: 0> ( n -- flag ) 0 > ;
: 2>R ( x1 x2 -- ) ( R: -- x1 x2 ) SWAP >R >R ;
: 2R> ( -- x1 x2 ) ( R: x1 x2 -- ) R> R> SWAP ;
: 2R@ ( -- x1 x2 ) ( R: x1 x2 -- x1 x2 ) 2 RICK 1 RICK ;
N: :NONAME ;
B: <> ( x1 x2 -- flag ) ;
N: ?DO ;
: AGAIN ( C: dest -- ) ( -- ) POSTPONE IRJMP HERE - CELL - , ;
N: C" ;
N: CASE ;
: COMPILE, ( xt -- ) , ;
N: CONVERT ;
N: ENDCASE ;
N: ENDOF ;
N: ERASE ;
N: EXPECT ;
0 CONSTANT FALSE ( -- false )
: HEX ( -- ) 16 BASE ! ;
N: MARKER ;
: NIP ( x1 x2 -- x2 ) SWAP DROP ;
N: OF ;
N: PAD ;
N: PARSE ;
B: PICK ( xu ... x1 x0 u -- xu ... x1 x0 xu ) ;
N: QUERY ;
N: REFILL ;
N: RESTORE-INPUT ;
N: ROLL ;
N: SAVE-INPUT ;
N: SOURCE-ID ;
N: SPAN ;
N: TIB ;
N: TO ;
-1 CONSTANT TRUE ( -- true )
: TUCK ( x1 x2 -- x2 x1 x2 ) SWAP OVER ;
N: U.R ;
N: U> ;
N: UNUSED ;
N: VALUE ;
N: WITHIN ;
N: [COMPILE] ;
N: \ ;

: -ROT ROT ROT ;
