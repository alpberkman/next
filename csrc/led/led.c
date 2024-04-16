
#include "led.h"

#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/wait.h>


LED led;

led_func led_lut[256];


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
    for(int i = 0; i < 256; ++i)
        led_register_key(i, led_echo);
    led_register_key('\t', led_autocomplete);
    led_register_key('\r', led_newline);
    led_register_key(LED_CTRL('q'), led_quit);
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
    led_lut[c](c);
}

void led_register_key(unsigned char c, led_func f) {
    led_lut[c] = f;
}


int led_slave(char *pathname, char *argv[], char *envp[]) {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execve(pathname, argv, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        close(pipefd[0]);

        for(;;) {
            int c = led_getkey();
            if(c == -1) break;
            if(c == 0) continue;
            write(pipefd[1], &c, 1);
            //printf("%d ('%c')\r\n", c, c);
        }


        // Close write end of pipe
        close(pipefd[1]);

        // Wait for the child to finish
        wait(NULL);
    }

    return 0;
}


LED_F(quit) {
    (void) c;
    exit(0);
}

LED_F(debug) {
    printf("%d\r\n", c);
}

LED_F(autocomplete) {
    (void) c;
    write(STDOUT_FILENO, "\rautcomplete\r\n", sizeof("\rautcomplete\r\n"));
}

LED_F(echo) {
    led.buf[led.ctr++] = c;
    write(STDOUT_FILENO, &c, 1);
}

LED_F(newline) {
    (void) c;
    write(STDOUT_FILENO, "\r\n", 2);
    write(STDOUT_FILENO, led.buf, led.ctr);
    write(STDOUT_FILENO, "\r\n", 2);

    led.ctr = 0;
//    printf("a\r\n");
}
LED_F(nop) {
    (void) c;
}

/*
int led_handle_cntrl(char c) {

    switch(c) {
    case CTRL('q'):
        exit(1);
    default:
        return 0;
    }
}

int led_handle_escape(char c) {
    return 0;
}
*/