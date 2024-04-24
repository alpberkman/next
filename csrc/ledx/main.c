#include <stddef.h>

#include "led.h"

int main(int argc, char *argv[]) {
    if(argc < 2)
        return 1;
    
    led_init();
    led_slave(argv[1], &argv[1], NULL);

    return 0;
}