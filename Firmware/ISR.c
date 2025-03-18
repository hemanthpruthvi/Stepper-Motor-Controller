/*
 * File:   ISR.c
 * Author: Pruthvi
 *
 * Created on 10 May, 2016, 3:42 PM
 */


#include "xc.h"
#include <p33FJ128GP802.h>
#include "config.h"

// Command receive
void __attribute__((__interrupt__, no_auto_psv)) _U1RXInterrupt(void){
    unsigned int temp;
    static unsigned int  FIRST_CHAR_REC = NO;
    temp = U1RXREG;
    switch(temp){
        case FIRST_CHAR:    // If the first character of the command is received
            COMM_IND = 0;   // Start the index
            FIRST_CHAR_REC = YES;  // Flag it
            break;
        case LAST_CHAR:     // If the last character of the command is received
            COMM_LEN = COMM_IND;    // Length of the command is index
            COMMAND[COMM_IND] = '\0';   // Final character in null
            FIRST_CHAR_REC = NO;     // Clear the First character received flag
            COMM_REC = YES;    // Flag that the command is received
            break;
        default:
            if (FIRST_CHAR_REC){    // If the first character is received
                COMMAND[COMM_IND] = temp;   // Store it in command array
                COMM_IND++;     // Increment the array index
            }
            else    // Else send that no command is received
                U1TX_SENDCHR('X');  
    }
    IFS0bits.U1RXIF = 0;    // Clear U1RX Interrupt Flag
}

// Receive from slave
void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt(void){
    unsigned int temp;
    temp = U2RXREG;
    if(temp == '1' || temp == '2' || temp == '3') 
        SRESPONSE[0] = temp + 3; // First character is for motor
    else if(temp == 'M')
        SRESPONSE[0] = 'S'; // First character is not for motor
    else if (temp == '\n'){ // Last character is newline so that you can read by line
        SRESPONSE[2] = temp;
        SRESPONSE[3] = '\0';
        U1TX_SENDSTR(SRESPONSE);
    }
    else SRESPONSE[1] = temp;
    IFS1bits.U2RXIF = 0;    // Clear U2RX Interrupt Flag
}




// Motor-1 rotation
void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void){
    if (MOT1_ROTAT){     // If motor is rotating 
        LED1 = ~LED1;   // Toggle the LED
        STEP1 = ~STEP1; // Toggle the step input to the driver
        HSTEP1_NUM--;    // Decrement the required half steps
        if (DIR1 == 0){POS1_CURRENT++;}
        if (DIR1 == 1){POS1_CURRENT--;}
        if (HSTEP1_NUM == 0){     // If the no. of steps are over
            MOT1_ROTAT = OFF;  // Stop the motor
            LED1 = OFF;
            MRESPONSE[0] = '1';
            MRESPONSE[1] = 'R';  // 'R' for rotation done
            U1TX_SENDSTR(MRESPONSE);
        }
        
    }
    IFS0bits.T2IF = 0;      // Clear Timer-2 interrupt flag
}
// Motor-1 home position
void __attribute__((__interrupt__, no_auto_psv)) _INT0Interrupt(void){
    POS1_CURRENT = 0;
    if (MOT1_HOME){
        MOT1_HOME = OFF;
        MOT1_ROTAT = OFF;
        LED1 = OFF;
        MRESPONSE[0] = '1';
        MRESPONSE[1] = 'H';  // 'H' for home
        U1TX_SENDSTR(MRESPONSE);
    }
    IFS0bits.INT0IF = 0;
}




// Motor-2 rotation
void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void){
    if (MOT2_ROTAT){     // If motor is rotating 
        LED2 = ~LED2;   // Toggle the LED
        STEP2 = ~STEP2; // Toggle the step input to the driver
        HSTEP2_NUM--;    // Decrement the required half steps
        if (DIR2 == 0){POS2_CURRENT++;}
        if (DIR2 == 1){POS2_CURRENT--;}
        if (HSTEP2_NUM == 0){     // If the no. of steps are over
            MOT2_ROTAT = OFF;  // Stop the motor
            LED2 = OFF;
            MRESPONSE[0] = '2';
            MRESPONSE[1] = 'R';  // 'R' for rotation done
            U1TX_SENDSTR(MRESPONSE);
        }
    }
    IFS0bits.T3IF = 0;      // Clear Timer-2 interrupt flag
}
// Motor-2 home position
void __attribute__((__interrupt__, no_auto_psv)) _INT1Interrupt(void){
    POS2_CURRENT = 0;
    if (MOT2_HOME){
        MOT2_HOME = OFF;
        MOT2_ROTAT = OFF;
        LED2 = OFF;
        MRESPONSE[0] = '2';
        MRESPONSE[1] = 'H';  // 'H' for home
        U1TX_SENDSTR(MRESPONSE);
    }
    IFS1bits.INT1IF = 0;
}




// Motor-3 rotation
void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt(void){
    if (MOT3_ROTAT){     // If motor is rotating 
        LED3 = ~LED3;   // Toggle the LED
        STEP3 = ~STEP3; // Toggle the step input to the driver
        HSTEP3_NUM--;    // Decrement the required half steps
        if (DIR3 == 0){POS3_CURRENT++;}
        if (DIR3 == 1){POS3_CURRENT--;}
        if (HSTEP3_NUM == 0){     // If the no. of steps are over
            MOT3_ROTAT = OFF;  // Stop the motor
            LED3 = OFF;
            MRESPONSE[0] = '3';
            MRESPONSE[1] = 'R';  // 'R' for rotation done
            U1TX_SENDSTR(MRESPONSE);
        }
    }
    IFS1bits.T4IF = 0;      // Clear Timer-2 interrupt flag
}
// Motor-3 home position
void __attribute__((__interrupt__, no_auto_psv)) _INT2Interrupt(void){
    POS3_CURRENT = 0;
    if (MOT3_HOME){
        MOT3_HOME = OFF;
        MOT3_ROTAT = OFF;
        LED3 = OFF;
        MRESPONSE[0] = '3';
        MRESPONSE[1] = 'H';  // 'H' for home
        U1TX_SENDSTR(MRESPONSE);
    }
    IFS1bits.INT2IF = 0;
}

