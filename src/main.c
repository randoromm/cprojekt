#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS_1 1000

void main (void) {
    /* Set port B pin 7 for output for Arduino Mega green LED */
    DDRB |= _BV(DDB7);
    /* Set port B pin 6 for output for Arduino Mega red LED */
    DDRB |= _BV(DDB6);

    while (1) {
        /* Set port B pin 7 high to turn Arduino Mega green and red (yellow) LED on */
        PORTB |= _BV(PORTB7) | _BV(PORTB6);
        _delay_ms(BLINK_DELAY_MS_1);
        /* Set port B pin 7 high to turn Arduino Mega green and red (yellow) LED off */
        PORTB &= ~(_BV(PORTB7) | _BV(PORTB6));
        _delay_ms(BLINK_DELAY_MS_1);
    }
}
