/*
 * File:   inouts.c
 * Author: Pruthvi
 *
 * Created on 15 May, 2016, 11:28 AM
 */


#include "xc.h"
#include <p33FJ128GP802.h>
#include "config.h"

void INIT_INOUT(void) {
    // LEDs
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    // Motor-1
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB11 = 0;
    // Motor-2
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB6 = 0;
    // Motor-3
    TRISBbits.TRISB4 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;


}

