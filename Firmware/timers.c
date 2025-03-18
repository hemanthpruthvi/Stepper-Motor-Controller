/*
 * File:   timers.c
 * Author: Pruthvi
 *
 * Created on 14 May, 2016, 3:37 PM
 */


#include "xc.h"
#include <p33FJ128GP802.h>
#include "config.h"

// Timer-2 configuration
void INIT_TIMR2(void){
    // Timer-2 Control bits (T2CONbits)
    T2CONbits.TON = 0;      // Timer Off
    T2CONbits.TGATE = 0;    // Timer Gated accumulation Off
    T2CONbits.TCKPS = 0b10;    // Timer Clock Pre-scalar Select (Pre-Scalar = 64)
    T2CONbits.TCS = 0;      // Timer Clock Source - Internal(0) FCY
    //T2CONbits.T32 = 0;      // 32-bit timer
    // Timer-2 registers
    TMR2 = 0x00;        // Timer register cleared
    PR2 = 4;            // Period value set
    // Timer-2 Interrupt
    IPC1bits.T2IP = 0b011;  // Interrupt Priority
    IFS0bits.T2IF = 0;      // Interrupt Flag
    IEC0bits.T2IE = 1;      // Interrupt Enable 
    
    T2CONbits.TON = 1;  // Timer 2 On
}

// Timer-3 configuration
void INIT_TIMR3(void){
    // Timer-3 Control bits (T3CONbits)
    T3CONbits.TON = 0;      // Timer Off
    T3CONbits.TGATE = 0;    // Timer Gated accumulation Off
    T3CONbits.TCKPS = 0b10;    // Timer Clock Pre-scalar Select (Pre-Scalar = 64)
    T3CONbits.TCS = 0;      // Timer Clock Source - Internal(0) FCY
//    T3CONbits.T32 = 0;      // 32-bit timer
    // Timer-3 registers
    TMR3 = 0x00;        // Timer register cleared
    PR3 = 4;            // Period value set
    // Timer-3 Interrupt
    IPC2bits.T3IP = 0b011;  // Interrupt Priority
    IFS0bits.T3IF = 0;      // Interrupt Flag
    IEC0bits.T3IE = 1;      // Interrupt Enable 
    
    T3CONbits.TON = 1;  // Timer-3 On
}

// Timer-4 configuration
void INIT_TIMR4(void){
    // Timer-4 Control bits (T4CONbits)
    T4CONbits.TON = 0;      // Timer Off
    T4CONbits.TGATE = 0;    // Timer Gated accumulation Off
    T4CONbits.TCKPS = 0b10;    // Timer Clock Pre-scalar Select (Pre-Scalar = 64)
    T4CONbits.TCS = 0;      // Timer Clock Source - Internal(0) FCY
    //T4CONbits.T32 = 0;      // 32-bit timer
    // Timer-4 registers
    TMR4 = 0x00;        // Timer register cleared
    PR4 = 4;            // Period value set
    // Timer-2 Interrupt
    IPC6bits.T4IP = 0b011;  // Interrupt Priority
    IFS1bits.T4IF = 0;      // Interrupt Flag
    IEC1bits.T4IE = 1;      // Interrupt Enable 
    
    T4CONbits.TON = 1;  // Timer-4 On
}



