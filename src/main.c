#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "print_helper.h"
#include "hmi_msg.h"

static inline void init_leds(void) {
    /* Set port A pin 0 for output for Arduino Mega red LED */
    DDRA |= _BV(DDA0);
}


/* Init error console as stderr in UART1 and print user code info */
static inline void init_errcon(void) {
    simple_uart1_init();
    simple_uart0_init();
    stdin = stdout = &simple_uart0_io;
    stderr = &simple_uart1_out;
    fprintf(stderr, "Version: %s built on: %s %s\n",
            FW_VERSION, __DATE__, __TIME__);
    fprintf(stderr, "avr-libc version: %s avr-gcc version: %s\n",
            __AVR_LIBC_VERSION_STRING__, __VERSION__);
    fprintf(stdout, NAME_STRING "\n");
    print_ascii_tbl(stdout);
    unsigned char ascii[128] = {0};

    for (unsigned char c = 0; c < 128; c++) {
        ascii[c] = c;
    }

    print_for_human(stdout, ascii, 128);
}

static inline void ask_number(void) {
    char inBuffer = ' ';
    fprintf(stdout, "Enter number >");
    fscanf(stdin, "%c", &inBuffer);
    fprintf(stdout, "%c\n", inBuffer);

    if ((int)inBuffer - (int)'0' >= 0 && (int)inBuffer - (int)'0' < 10) {
        fprintf(stdout, "You entered number %s.\n",
                numStrings[(int)inBuffer - (int)'0']);
    } else {
        fprintf(stdout, "Please enter number between 0 and 9!\n");
    }
}

static inline void blink_leds(void) {
    /* Set port A pin 0 high to turn Arduino Mega red LED on */
    PORTA |= _BV(PORTA0);
    _delay_ms(BLINK_DELAY_MS_1);
    /* Ask for a number and return it as a string to user */
    ask_number();
    /* Set port B pin 0 high to turn Arduino Mega red LED off */
    PORTA &= ~_BV(PORTA0);
    _delay_ms(BLINK_DELAY_MS_1);
}

void main(void) {
    init_leds();
    init_errcon();

    while (1) {
        blink_leds();
    }
}
