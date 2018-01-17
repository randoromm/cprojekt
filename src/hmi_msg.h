#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define VER_FW "Version: %S built on: %S %S"
#define VER_LIBC "avr-libc version: %S avr-gcc version: %S"

#define NAME_STRING "Rando Rommot"
#define ASK_NUMBER "Enter number >"
#define ACK_NUMBER "You entered number %S."
#define INC_NUMBER "Please enter number between 0 and 9!"
#define BLINK_DELAY_MS_1 100

const char num0[] PROGMEM = "Zero";
const char num1[] PROGMEM = "One";
const char num2[] PROGMEM = "Two";
const char num3[] PROGMEM = "Three";
const char num4[] PROGMEM = "Four";
const char num5[] PROGMEM = "Five";
const char num6[] PROGMEM = "Six";
const char num7[] PROGMEM = "Seven";
const char num8[] PROGMEM = "Eight";
const char num9[] PROGMEM = "Nine";

PGM_P const num_strings[] PROGMEM = {num0, num1, num2, num3, num4,
                                num5, num6, num7, num8, num9};

#endif /* End of header guard */
