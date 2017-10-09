#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS_1 3000
#define BLINK_DELAY_MS_2 2000
#define BLINK_DELAY_MS_3 200
#define BLINK_DELAY_MS_4 10

void main (void)
{
    /* Set port B pin 7 for output for Arduino Mega yellow LED */
    DDRB |= _BV(DDB7);
    DDRB |= _BV(DDB6);

    while (1) {
        /* Set port B pin 7 high to turn Arduino Mega yellow LED on */
        PORTB |= _BV(PORTB7);
        _delay_ms(BLINK_DELAY_MS_3);
        /* Set port B pin 7 high to turn Arduino Mega yellow LED off */
        PORTB &= ~_BV(PORTB7);
        _delay_ms(BLINK_DELAY_MS_4);

        /* Set port B pin 7 high to turn Arduino Mega yellow LED on */
        PORTB |= _BV(PORTB6);
        _delay_ms(BLINK_DELAY_MS_3);
        /* Set port B pin 7 high to turn Arduino Mega yellow LED off */
        PORTB &= ~_BV(PORTB6);
        _delay_ms(BLINK_DELAY_MS_4);
    }
}
