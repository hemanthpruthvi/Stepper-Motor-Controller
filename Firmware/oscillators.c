/*
 * File:   oscillators.c
 * Author: Pruthvi
 *
 * Created on 14 May, 2016, 3:37 PM
 */


#include "xc.h"
#include <p33FJ128GP802.h>
#include "config.h"

void INIT_OSCLI(void){
    // Default setting is FRC oscillator with post FRCN (division)
    // FOSC = (((FTUN/FRCDIVN)/N1)/N2)*M
    // FP = FOSC/2
    // FCY = FP/DOZE
    // FRC oscillator tuning and post-scalar
    OSCTUNbits.TUN = 0b000010; // TUN = 2, i.e. 7.37+2*(0.375%) = 7.43 MHz 
    CLKDIVbits.FRCDIV = 0b000; // FRCDIVN = 1
    // PLL configuration
    CLKDIVbits.PLLPRE = 0b00000;    // PLL pre-scalar N1 = 2 (default) 3.71 MHz
    CLKDIVbits.PLLPOST = 0b00;  // PLL post-scalar N2 = 2 (default is 4) 1.86 MHz
    PLLFBDbits.PLLDIV = 41;     // PLL feedback divisor M = 41+2 (default is 50)79.82 MHz
    // DOZE configuration
    CLKDIVbits.DOZEN = 1;       // Doze mode enable
    CLKDIVbits.DOZE = 0b000;    // FP/FCY = 1 79.82 MHz
    RCONbits.SWDTEN = 0;        // Disable Watch Dog Timer
    while(OSCCONbits.LOCK!=1);  // Wait for PLL to lock
}