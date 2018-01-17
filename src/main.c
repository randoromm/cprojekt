#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
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
    fprintf_P(stderr, PSTR(VER_FW "\n"),
              PSTR(FW_VERSION), PSTR(__DATE__), PSTR(__TIME__));
    fprintf_P(stderr, PSTR(VER_LIBC "\n"),
              PSTR(__AVR_LIBC_VERSION_STRING__), PSTR(__VERSION__));
    fprintf_P(stdout, PSTR(NAME_STRING "\n"));
    print_ascii_tbl(stdout);
    unsigned char ascii[128] = {0};

    for (unsigned char c = 0; c < 128; c++) {
        ascii[c] = c;
    }

    print_for_human(stdout, ascii, 128);
}

static inline void ask_number(void) {
    char inBuffer = ' ';
    fprintf_P(stdout, PSTR(ASK_NUMBER));
    fscanf(stdin, "%c", &inBuffer);
    fprintf(stdout, "%c\n", inBuffer);
    int number = (int)inBuffer - (int)'0';

    if (number >= 0 && number < 10) {
        fprintf_P(stdout, PSTR(ACK_NUMBER "\n"),
                  (PGM_P)pgm_read_word(&(num_strings[number])));
    } else {
        fprintf_P(stdout, PSTR(INC_NUMBER "\n"));
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
