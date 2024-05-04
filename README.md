# Next
Next is a ITC Forth, implemented in the C progamming language.
It uses a VM with a dispatch table to implement primitives.
One interesting implementation detail is that most of the kernel words are written in C using Forth style.
This prevents the need of an eval function in C as the outer interpreter.
This also lets users write their Forth programs in C and then compile it just like C programs.


# VM Structure
The VM is implemented as a struct, which itself holds other structs depending on their purpose.

```
+-VM-------+
| ITC itc  |-------->+-ITC-----+
|          |         | power p |
| SPU spu  |-\       | cell ip |
|          |  -\     | cell wp |
| MEM mem  |    -\   +---------+
+----------+      -\
                    >+-SPU-------+
                     | stack p   |------->+-stack----------+
                     | stack r   |        | cell s[0x100]  |
                     +-----------+        | byte sp        |
                                          +----------------+
```
* VM
    * ITC itc: is responsible for threading
        * power p: is used to enable or stop the VM
        * cell ip: is the instrucion pointer. It points to the next primitive
        * cell wp: is the word pointer. It points to the next word
    * SPU spu: is the stack processing unit. It holds the stacks
        * stack p: is the parameter stack
            * cell s[0x100]: available stack space
            * byte sp: stack pointer
        * stack r: is the return stack
    * MEM mem: a byte pointer to the memory 

# Primitives
The VM runs on a dispatch table that takes a byte as a pointer.
It is a byte code interpreter.
The primitives are shown below along with their byte code value and relevant function:

NOP: No operation. It exists to fill the dispatch table

HALT: Stops VM by changing the vm.itc.p to false

```
0x00: NOP    <--->    _nop
0x01: HALT   <--->   _halt
0x02: LIT    <--->    _lit
0x03: NEXT   <--->   _next
0x04: NEST   <--->   _nest
0x05: UNNEST <---> _unnest
0x06: JMP    <--->    _jmp
0x07: JZ     <--->     _jz
0x08: EXE    <--->    _exe
0x09: RJMP   <--->   _rjmp
0x0a: RJZ    <--->    _rjz
0x0b: DUP    <--->    _dup
0x0c: DROP   <--->   _drop
0x0d: SWAP   <--->   _swap
0x0e: PUSH   <--->   _push
0x0f: POP    <--->    _pop
0x10: PICK   <--->   _pick
0x11: RICK   <--->   _rick
0x12: LDP    <--->    _ldp
0x13: LDR    <--->    _ldr
0x14: EQ     <--->     _eq
0x15: NEQ    <--->    _neq
0x16: GT     <--->     _gt
0x17: LT     <--->     _lt
0x18: AND    <--->    _and
0x19: OR     <--->     _or
0x1a: XOR    <--->    _xor
0x1b: SHR    <--->    _shr
0x1c: SHL    <--->    _shl
0x1d: ADD    <--->    _add
0x1e: SUB    <--->    _sub
0x1f: MUL    <--->    _mul
0x20: DIV    <--->    _div
0x21: MOD    <--->    _mod
0x22: LDC    <--->    _ldc
0x23: STRC   <--->   _strc
0x24: LDB    <--->    _ldb
0x25: STRB   <--->   _strb
0x26: KEY    <--->    _key
0x27: EMIT   <--->   _emit
```


# ITC
ITC stands for indirect threaded code. It is threading technique where instead of functions getting **call**ed and **ret**urned.
When a function finishes, it **fetch**es the address of the next function and **jump**s directly to it.

## Word Structure
In Next the dictionary is implemented as a linked list.
They have the following structure:
```
[ link field | flags | word name | code field | parameter field ]
```
* link field (1 cell): address of the previous word
* flags (1 byte): ```[ visible (1 bit) | immmediate (1 bit) | not used (1 bit) | word name length (5 bit) ]```
* word name (0-31 bytes): name of the word
* code field (1-n bytes): primitives for the VM
* parameter field (0-n cells): code field address of other words

## Primitive Word Structure
Primitive words are only made out of primitives and they end with and instruction that affects the control flow.
Most of the primitive words end with the primitive **next**.

## Colon Word Structure
Colon words are the high level words of Forth.
They start with the primitive **nest**.
They consist of primitive words and other colon words.
They end with words that change the control flow, with the most common one being the colon word **unnest**.


# Other
Table made using https://textik.com