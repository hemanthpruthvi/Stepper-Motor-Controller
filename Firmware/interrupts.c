/*
 * File:   Interrupts.c
 * Author: Pruthvi
 *
 * Created on 28 October, 2016, 6:25 PM
 */


#include "xc.h"
#include <p33FJ128GP802.h>
#include "config.h"

void INIT_INTRR(void) {
    // INT0
    TRISBbits.TRISB7 = 0;
    IFS0bits.INT0IF = 0;    // Clear the flag
    INTCON2bits.INT0EP = 0; // Edge polarity - positive
    IPC0bits.INT0IP = 2;    // Interrupt priority
    IEC0bits.INT0IE = 1;    // Enable the interrupt
    
    // INT1
    TRISBbits.TRISB10 = 0;
    RPINR0bits.INT1R = 10;
    IFS1bits.INT1IF = 0;    // Clear the flag
    INTCON2bits.INT1EP = 0; // Edge polarity - positive
    IPC5bits.INT1IP = 3;    // Interrupt priority
    IEC1bits.INT1IE = 1;    // Enable the interrupt
    
    // INT2
    TRISBbits.TRISB5 = 0;
    RPINR1bits.INT2R = 5;
    IFS1bits.INT2IF = 0;    // Clear the flag
    INTCON2bits.INT2EP = 0; // Edge polarity - positive
    IPC7bits.INT2IP = 4;    // Interrupt priority
    IEC1bits.INT2IE = 1;    // Enable the interrupt
}
