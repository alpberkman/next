

#ifndef _LED_H
#define _LED_H

//#include "vm.h"

#include <termios.h>

//extern cell hp;
//extern cell lp;


#define LED_CTRL(X) ((X) & 0x1f)
#define LED_F(NAME) \
    void led_##NAME (char c)


typedef struct LED LED;
struct LED {
    struct termios orig;
    int x, y;
    int w, l;
    char buf[1024];
    int ctr;
};

typedef void (*led_func) (char c);


void led_disable_raw_mode();
void led_enable_raw_mode();
void led_init();

void led_enable_cursor();
void led_disable_cursor();
void led_move_cursor(int x, int y);

int led_getkey();
void led_handle_key(unsigned char c);
void led_register_key(unsigned char c, led_func f);

int led_slave(char *pathname, char *argv[], char *envp[]);

//int led_getescseq();



LED_F(quit);
LED_F(debug);
LED_F(autocomplete);
LED_F(echo);
LED_F(newline);
LED_F(nop);
/*
#define XENUM(E, F)  E,
#define XFUNC(E, F)   F,
#define XENUMNAME(E, F) #E,
#define XFUNCNAME(E, F) #F,
#define XENUM2FUNC(E, F) #E, #F
#define XFUNCSIG(E, F) void F (VM *vm);
#define XFUNCTAB(E, F) [E] = F,

#define LED_TABLE(APPLY) \
    APPLY(NOP,  _nop) \
    APPLY(HALT, _halt) \
    APPLY(LIT,  _lit) \
    APPLY(NEXT, _next) \
    APPLY(NEST, _nest) \
    APPLY(UNNEST, _unnest) \
    APPLY(JMP,  _jmp) \
    APPLY(JZ,   _jz) 


TABLE(XFUNCSIG);
*/

#endif