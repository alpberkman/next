

#ifndef _LED_H
#define _LED_H

//#include "vm.h"

#include <termios.h>

//extern cell hp;
//extern cell lp;

#define CONSTANT_STR(X) (X), (sizeof(X))
#define BUF             led.buf, led.ctr
#define SLAVE_FILENO    led.pipefd[1]


#define DEL_KEYCODE 127


#define LED_CTRL(X) ((X) & 0x1f)
#define LED_F(NAME) \
    void led_##NAME (char c)


typedef void (*led_func) (char c);

typedef struct LED LED;
struct LED {
    struct termios orig;
    int x, y;
    int w, l;
    char buf[1024];
    int ctr;
    int pipefd[2];
    led_func lut[256];
};


void led_disable_raw_mode();
void led_enable_raw_mode();
void led_init();
/*
void led_enable_cursor();
void led_disable_cursor();
void led_move_cursor(int x, int y);
*/
int led_getkey();
void led_handle_key(unsigned char c);
void led_register_key(unsigned char c, led_func f);

int led_slave(char *pathname, char *argv[], char *envp[]);



LED_F(nop);
LED_F(echo);
LED_F(passthrough);

LED_F(cr);
LED_F(del);

LED_F(flush);
LED_F(quit);
LED_F(eof);


LED_F(debug);
LED_F(autocomplete);

#define XFUNCTAB(E, F)  [E] = F,
#define XLUT(E, F)      led_register_key((E), (F));

#define LED_TABLE(APPLY) \
    APPLY(LED_CTRL('a'),  led_nop) \
    APPLY(LED_CTRL('b'),  led_nop) \
    APPLY(LED_CTRL('c'),  led_nop) \
    APPLY(LED_CTRL('d'),  led_nop) \
    APPLY(LED_CTRL('e'),  led_eof) \
    APPLY(LED_CTRL('f'),  led_flush) \
    APPLY(LED_CTRL('g'),  led_nop) \
    APPLY(LED_CTRL('h'),  led_nop) \
    APPLY(LED_CTRL('i'),  led_nop) \
    APPLY(LED_CTRL('j'),  led_nop) \
    APPLY(LED_CTRL('k'),  led_nop) \
    APPLY(LED_CTRL('l'),  led_nop) \
    APPLY(LED_CTRL('m'),  led_nop) \
    APPLY(LED_CTRL('n'),  led_nop) \
    APPLY(LED_CTRL('o'),  led_nop) \
    APPLY(LED_CTRL('p'),  led_nop) \
    APPLY(LED_CTRL('q'),  led_quit) \
    APPLY(LED_CTRL('r'),  led_nop) \
    APPLY(LED_CTRL('s'),  led_nop) \
    APPLY(LED_CTRL('t'),  led_nop) \
    APPLY(LED_CTRL('u'),  led_nop) \
    APPLY(LED_CTRL('v'),  led_nop) \
    APPLY(LED_CTRL('w'),  led_nop) \
    APPLY(LED_CTRL('x'),  led_nop) \
    APPLY(LED_CTRL('y'),  led_nop) \
    APPLY(LED_CTRL('z'),  led_nop)

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