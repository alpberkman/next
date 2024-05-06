
#ifndef _DEBUG_H
#define _DEBUG_H

#include "vm.h"

#include <stdio.h>
#include <string.h>


extern cell hp;
extern cell lp;


#define WORD_DISASM(ADDR) \
    cell link = CELL_FETCH(XMEM, ADDR); \
    byte len = BYTE_FETCH(XMEM, ADDR + CELL_SIZE) & WORD_LEN; \
    byte vis = BYTE_FETCH(XMEM, ADDR + CELL_SIZE) & MASK_VIS; \
    byte imm = BYTE_FETCH(XMEM, ADDR + CELL_SIZE) & MASK_IMM; \
    byte *name = &(BYTE_FETCH(XMEM, ADDR + CELL_SIZE + BYTE_SIZE)); \
    cell cfa = ADDR + CELL_SIZE + BYTE_SIZE + len;
// Given the address of a link field, disassembles a words's fields

#define DR(X) reset(vm); rund(vm, (X)); stacks(vm); puts("")
// Wrapper for debug runs 

#define DEBUG_ENABLE(A, B) ((DEBUG_LEVEL >= (A)) || (B))  
// If debug level is high enough then true else whatever B is
#define DEBUG_VERBOSE(A, B) ((DEBUG_LEVEL >= (strspn(#A"", "vV"))) || (B))
// Same as DEBUG_ENABLE but use v or V instead
// Ex: DEBUG_ENABLE(vVv, flag)

#define NO 0
#define MINIMAL 1
#define MINIMAL_PLUS 2
#define VERBOSE 3
#define EXTREME 4


void pstack(cell *s, cell p, char *sname, char *fstr);
// Prints a given stack
void stacks(VM *vm);
// Prints both stacks
void stat(VM *vm);
// Prints information about ITC and MEM of a vm
void info(VM *vm);
// Gives general information about a vm using, penum2func(), stat(), hexdump(), pwords(), stacks()

char *enum2s(byte p);
// Returns a string that represents an enum's name
char *func2s(func f);
// Returns a string that represents a function's name


void penum2func(void);
// Prints enum and function name pairs

void hexdump(VM *vm, int rlen, int clen);
// Dumps the memory contents, both in hex and if printable using chars
// rlen: length of rows
// clen: length of columns

void pword(VM *vm, cell addr);
// Print a words name
// addr: address of a link field of a word
void pheader(VM *vm, cell addr);
// Print a word's header
// addr: address of a link field of a word
void pwords(VM *vm);
// Disasemble the entire dictionary
void disasm(VM *vm, cell addr, cell limit);
// Disassembles a word including the header, code field and parameter field
// addr: address of a link field of a word
// limit: address of the end of a word (address of the previous words link field)

int locate(VM *vm, cell addr);
// Given an address that belongs to a words, returns the start of it

int wname(VM *vm, cell addr, char *target);
// Checks whether the name of the word is equal to target
// addr: address of a link field of a word

void disasm_instr(VM *vm);
// Disassemble the next instruction
// DEBUG_LEVEL 1: Show the last executed instruction, if none are available show 0th word
// DEBUG_LEVEL 2: Dont skip NEXT primitive
// DEBUG_LEVEL 4: Print the stack before every instruction
void rund(VM *vm, cell addr);
// Runs a given word with debugging using disasm_instr() also prints the stack before and after

#endif

