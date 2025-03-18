/*
 * File:   custom.c
 * Author: Pruthvi
 *
 * Created on 12 May, 2016, 6:23 PM
 */

#include "xc.h"
#include <p33FJ128GP802.h>
#include "config.h"

// Send an unsigned character by UART1 transmitter
void U1TX_SENDCHR(unsigned char chr){
    while(U1STAbits.TRMT==0); // Wait for previously sent character to be transmitted
	U1TXREG = chr; // Transmit one character
}
// Send an unsigned character string by UART1 transmitter
void U1TX_SENDSTR(unsigned char str[]){
    unsigned int i;
	for(i=0;str[i]!='\0';i++)   // Until null character
		U1TX_SENDCHR(str[i]);
}

// Send an unsigned character by UART2 transmitter
void U2TX_SENDCHR(unsigned char chr){
    while(U2STAbits.TRMT==0); // Wait for previously sent character to be transmitted
	U2TXREG = chr; // Transmit one character
}
// Send an unsigned character string by UART1 transmitter
void U2TX_SENDSTR(unsigned char str[]){
    unsigned int i;
	for(i=0;str[i]!='\0';i++)   // Until null character
		U2TX_SENDCHR(str[i]);
}

