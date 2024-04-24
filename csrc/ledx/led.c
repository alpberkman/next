
#include "led.h"

#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/wait.h>


LED led;


void led_disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &led.orig);
}
void led_enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &led.orig);

    atexit(led_disable_raw_mode);

    struct termios raw = led.orig;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


void led_init() {
    led_enable_raw_mode();
    //for(int i = 0; i < 256; ++i)
    //    led_register_key(i, led_nop);
    for(int i = 0; i < 256; ++i)
        led_register_key(i, led_echo);

    LED_TABLE(XLUT);

    led_register_key('\t', led_autocomplete);
    led_register_key('\r', led_cr);
    led_register_key(DEL_KEYCODE, led_del);

    //led_register_key(LED_CTRL('q'), led_quit);
    //led_register_key(LED_CTRL('d'), led_flush);
    //led_register_key(LED_CTRL('i'), led_stop);

    //led_register_key('A', led_passthrough);
}

int led_getkey() {
    char c;
    int len;

    for(;;) {
        len = read(STDIN_FILENO, &c, 1);

        if(len == -1) return -1;
        if(len == 0) return 0;

        //printf("%d\r\n", c);
        led_handle_key(c);
        return c;
    }
}

void led_handle_key(unsigned char c) {
    led.lut[c](c);
}
void led_register_key(unsigned char c, led_func f) {
    led.lut[c] = f;
}


int led_slave(char *pathname, char *argv[], char *envp[]) {
    pid_t pid;

    if (pipe(led.pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        close(led.pipefd[1]);
        dup2(led.pipefd[0], STDIN_FILENO);
        execve(pathname, argv, envp);

        close(led.pipefd[0]);
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        close(led.pipefd[0]);
        for(;;) {
            int c = led_getkey();
            if(c == -1) break;
            if(c == 0) continue;
            //printf("%d ('%c')\r\n", c, c);
        }

        close(led.pipefd[1]);
        wait(NULL);
    }

    return 0;
}

LED_F(nop) {
    (void) c;
}
LED_F(echo) {
    if(isprint(c))
        led.buf[led.ctr++] = c;
    write(STDOUT_FILENO, &c, 1);
}
LED_F(passthrough) {
    led.buf[led.ctr++] = c;
}

LED_F(cr) {
    (void) c;
    led.buf[led.ctr++] = '\r';
    led.buf[led.ctr++] = '\n';
    write(STDOUT_FILENO, CONSTANT_STR("\r\n"));
    write(SLAVE_FILENO,  BUF);
    led.ctr = 0;
}
LED_F(del){
    (void) c;
    --led.ctr;
    write(STDOUT_FILENO, CONSTANT_STR("\033[D"));
    write(STDOUT_FILENO, CONSTANT_STR(" "));
    write(STDOUT_FILENO, CONSTANT_STR("\033[D"));
}

LED_F(flush) {
    write(SLAVE_FILENO,  BUF);
    led.ctr = 0;
}
LED_F(quit){
    (void) c;
    exit(EXIT_SUCCESS);
}
LED_F(eof) {
    //led_disable_raw_mode();
    //close(STDIN_FILENO);
    close(SLAVE_FILENO);
    wait(NULL);
}


LED_F(debug) {
    printf("%d\r\n", c);
}
LED_F(autocomplete) {
    (void) c;
    write(STDOUT_FILENO, "\rautcomplete\n\r\n", sizeof("\rautcomplete\r\n"));
}

