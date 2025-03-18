/*
 * File:   uarts.c
 * Author: Pruthvi
 *
 * Created on 14 May, 2016, 3:36 PM
 */

#include "xc.h"
#include <p33FJ128GP802.h>
#include "config.h"
// UART-1 configuration
void INIT_UART1(void){
    // Peripheral select
    RPINR18bits.U1RXR = 2;      // RX1 is set to RP2
    RPOR1bits.RP3R = 0b00011;   // RP3 is set to be TX1
    U1MODEbits.UARTEN = 0;  // Disable UART
    // Baudrate, parity, data, stop bit selections
    U1MODEbits.ABAUD = 0;   // Auto Baud Off
    U1MODEbits.BRGH = 0;    // BaudRate Generate High Off
    U1BRG = BRGVAL1;    // BaudRate Generate is loaded
    U1MODEbits.PDSEL = 0b00;   // Parity, Data Select - 8-bit , no parity
    U1MODEbits.STSEL = 0;   // Stop select - 1-bit
    // Receiver settings
    IEC0bits.U1RXIE = 1;    // Interrupt Enable Select - U1RX interrupt On
    IPC2bits.U1RXIP = 0b001;    // Interrupt Priority Control - U1RX low priority 
    U1STAbits.URXISEL = 0;  // Interrupt after one character received
    U1MODEbits.UEN = 0;  // UART is used without RXCTS, TXCTS
    U1MODEbits.UARTEN = 1;  // Enable UART
    U1STAbits.UTXEN = 1;    // Enable UART TX
    // Wait at least (1/BAUDRATE2) seconds before sending first char
    IFS0bits.U1RXIF=0;      // Clear U2RX interrupt flag
    unsigned int i;
    for(i = 0; i < WAIT_TX1; i++){Nop();}
}

// UART-2 configuration
void INIT_UART2(void){
    // Peripheral select
    RPINR19bits.U2RXR = 15;     // RX2 is set to RP15
	RPOR7bits.RP14R = 0b00101;  // RP14 is set to be TX2
    U2MODEbits.UARTEN = 0;  // Disable UART
    // Baudrate, parity, data, stop bit selections
    U2MODEbits.ABAUD = 0;   // Auto Baud Off
    U2MODEbits.BRGH = 0;    // BaudRate Generate High Off
    U2BRG = BRGVAL2;    // BaudRate Generate is loaded
    U2MODEbits.PDSEL = 0b00;   // Parity, Data Select - 8-bit , no parity
    U2MODEbits.STSEL = 0;   // Stop select - 1-bit
    // Receiver settings
    IEC1bits.U2RXIE = 1;    // Interrupt Enable Select - U1RX interrupt On
    IPC7bits.U2RXIP = 0b010;    // Interrupt Priority Control - U2RX low priority 
    U2STAbits.URXISEL = 0;  // Interrupt after one character received
    U2MODEbits.UEN = 0;  // UART is used without RXCTS, TXCTS
    U2MODEbits.UARTEN = 1;  // Enable UART
    U2STAbits.UTXEN = 1;    // Enable UART TX
    // Wait at least (1/BAUDRATE2) seconds before sending first char
    IFS1bits.U2RXIF=0;      // Clear U2RX interrupt flag
    unsigned int i;
    for(i = 0; i < WAIT_TX2; i++){Nop();}
}
