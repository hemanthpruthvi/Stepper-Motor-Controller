/* 
 * File:   uart.c
 * Author: Pruthvi
 *
 * Created on June 2, 2014, 5:38 PM
 */
#include <p33FJ128GP802.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

unsigned char COMMAND[16];   // Command array
unsigned char SLAVE_COMMAND[16]; // Command array for slave
unsigned int COMM_IND = 0;       // Command array index
unsigned int COMM_LEN = 0;       // Command length
unsigned int COMM_REC = NO;       // Command received?
unsigned char SRESPONSE[4];
unsigned char MRESPONSE[4];

unsigned int NUMBER_MOTO = '0';    // Motor number
unsigned int FUNCTION_MOTO = '0';  // Function of drivers
unsigned long int NUMBER = 0;         // Numerical value

unsigned int MOT1_ROTAT = OFF; // Motor-1 rotation?
unsigned int MOT1_HOME = OFF;  // Motor-1 homing?
unsigned long int STEP1_NUM = 0;  // Number of steps left
unsigned long int HSTEP1_NUM = 0; // Number of toggles (half-steps)  = 2* Number of steps
unsigned int STEP1_FREQ = 1000; // Step frequency
unsigned long int POS1_CURRENT = 0; // Current value - 1

unsigned int MOT2_ROTAT = OFF; // Motor-2 rotation?
unsigned int MOT2_HOME = OFF;  // Motor-2 homing?
unsigned long int STEP2_NUM = 0;  // Number of steps left
unsigned long int HSTEP2_NUM = 0; // Number of toggles (half-steps) = 2* Number of steps
unsigned int STEP2_FREQ = 1000; // Step frequency
unsigned long int POS2_CURRENT = 0; // Current value - 2


unsigned int MOT3_ROTAT = OFF; // Motor-3 rotation?
unsigned int MOT3_HOME = OFF;  // Motor-3 homing?
unsigned long int STEP3_NUM = 0;  // Number of steps left
unsigned long int HSTEP3_NUM = 0; // Number of toggles (half-steps) = 2* Number of steps
unsigned int STEP3_FREQ = 1000; // Step frequency
unsigned long int POS3_CURRENT = 0; // Current value - 3

#pragma config POSCMD = NONE   // Primary Oscillator Mode is None
#pragma config OSCIOFNC = ON   // Oscillator pin's I/O Funcion - On
#pragma config FCKSM = CSDCMD  // Clock Switching & Monitoring - Both Disabled
#pragma config FNOSC = FRCPLL  // Oscillator select - FastRC with PLL
#pragma config FWDTEN = OFF    // Watch Dog Timer Enable - Off

void PROCESS_COMM(void);
void DELAY(int);

int main(void){
    ADPCFG = 0xFFFF;    //make ADC pins all digital
    INIT_OSCLI();   // Initiate =internal Oscillator
    INIT_INOUT();   // Input/Output
    INIT_UART1();   // UART-1
    INIT_UART2();   // UART-2
    INIT_TIMR2();   // Timer-2
    INIT_TIMR3();   // Timer-2
    INIT_TIMR4();   // Timer-2
    INIT_INTRR();   // External interrupts
    // Default Motor Speeds
    T2CONbits.TON = 0;		// Disable Timer
    PR2 = ((FCY/64)/2)/STEP1_FREQ;
    T2CONbits.TON = 1;		// Enable Timer
    T3CONbits.TON = 0;		// Disable Timer
    PR3 = ((FCY/64)/2)/STEP2_FREQ;
    T3CONbits.TON = 1;		// Enable Timer
    T4CONbits.TON = 0;		// Disable Timer
    PR4 = ((FCY/64)/2)/STEP3_FREQ;
    T4CONbits.TON = 1;		// Enable Timer
    while(1){
        // Command Processing
        if (COMM_REC){ // If command is received in UART-1
            PROCESS_COMM();
            MRESPONSE[2] = '\n';
            MRESPONSE[3] = '\0';
            U1TX_SENDSTR(MRESPONSE);
            COMM_REC = NO;
        }
    }
    return 0;
}

void DELAY(int temp){
    int i=0, j=0;
    for (i=0;i<2000;i++)
            for(j=0;j<temp;j++);
}

void PROCESS_COMM(void){
	unsigned int i;
	char temp;
    temp = COMMAND[0]-'0';
    if (temp > 3 && temp < 7){ // Check if the COMMAND is for the slave
        SLAVE_COMMAND[0] = '<';
        SLAVE_COMMAND[1] = COMMAND[0]-3;
        for (i = 1; COMMAND[i] != '\0'; i++){
            SLAVE_COMMAND[i+1] = COMMAND[i];
            SLAVE_COMMAND[i+2] = '>';
        }        
        U2TX_SENDSTR(SLAVE_COMMAND);
        MRESPONSE[0] = 'M'; 
        MRESPONSE[1] = 'A'; // 'A' for acknowledge
        return;
    }
    
    else{ // COMMAND is for the master
        NUMBER_MOTO = COMMAND[0];       // Corresponding motor (1, 2 or 3)
        FUNCTION_MOTO = COMMAND[1];     // Function? (Rotate or adjust speed)
        NUMBER = 0;
        for(i = 2; COMMAND[i] != '\0'; i++){    // Numerical value
            temp = COMMAND[i] - '0';
            if (temp < 0 || temp > 9){
                NUMBER = 0;
                MRESPONSE[0] = 'M'; 
                MRESPONSE[1] = 'X'; // 'X' for wrong
                return;
            }
            NUMBER = (NUMBER*10)+ temp;
        }
        // Execute the function for the motor      
        switch (COMMAND[0]){
            // Command for motor-1
            case '1':
                MRESPONSE[0] = '1';
                if (COMMAND[1] == 'Q') {
                    MOT1_ROTAT = OFF;
                    MOT1_HOME = OFF;
                    LED1 = OFF; 
                    MRESPONSE[1] = 'Q'; // 'Q' for quitting
                    return;
                }
                else if (MOT1_ROTAT == YES || MOT1_HOME == YES){ 
                    MRESPONSE[1] = 'B'; // 'B' for busy
                    return;
                }
                else{
                    switch (COMMAND[1]){
                        case 'D':
                            DIS1 = 1;
                            MRESPONSE[1] = 'D'; // 'D' for disable 
                            return;
                        case 'E':
                            DIS1 = 0;
                            MRESPONSE[1] = 'E'; // 'E' for enable 
                            return;
                        case 'H':
                            STEP1_NUM = 10000000;
                            HSTEP1_NUM = 2*STEP1_NUM;
                            DIR1 = 1;
                            MOT1_HOME = ON;
                            MOT1_ROTAT = ON;
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        case 'h': 
                            STEP1_NUM = 10000000;
                            HSTEP1_NUM = 2*STEP1_NUM;
                            DIR1 = 0;
                            MOT1_HOME = ON;
                            MOT1_ROTAT = ON;
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        case'F':
                            STEP1_FREQ = NUMBER; // STEP FREQUENCY
                            T2CONbits.TON = 0;		// Disable Timer
                            PR2 = ((FCY/64)/2)/STEP1_FREQ;
                            T2CONbits.TON = 1;		// Enable Timer
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        case '+':
                            if (NUMBER == 0){
                                MRESPONSE[1] = 'R';
                                return;
                            }
                            STEP1_NUM = NUMBER;
                            HSTEP1_NUM = 2*STEP1_NUM;
                            DIR1 = 0;
                            MOT1_ROTAT = ON;
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        case '-':
                            if (NUMBER == 0){
                                MRESPONSE[1] = 'R';
                                return;
                            }
                            STEP1_NUM = NUMBER;
                            HSTEP1_NUM = 2*STEP1_NUM;
                            DIR1 = 1;
                            MOT1_ROTAT = ON;
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        default:
                            MRESPONSE[1] = 'X'; // 'X' for wrong 
                            return;
                    }
                }
            // End of Case-1   
                
            // Command for motor-2
            case '2':
                MRESPONSE[0] = '2';
                if (COMMAND[1] == 'Q') {
                    MOT2_ROTAT = OFF;
                    MOT2_HOME = OFF;
                    LED2 = OFF;
                    MRESPONSE[1] = 'Q'; // 'Q' for quitting 
                    return;
                }
                else if (MOT2_ROTAT == YES || MOT2_HOME == YES){
                    MRESPONSE[1] = 'B'; // 'A' for acknowledge 
                    return; // 'B' for busy
                }
                else{
                    switch (COMMAND[1]){
                        case 'D':
                            DIS2 = 1;
                            MRESPONSE[1] = 'D'; // 'D' for disable 
                            return;
                        case 'E':
                            DIS2 = 0;
                            MRESPONSE[1] = 'E'; // 'E' for enable 
                            return;
                        case 'H':
                            STEP2_NUM = 10000000;
                            HSTEP2_NUM = 2*STEP2_NUM;
                            DIR2 = 1;
                            MOT2_HOME = ON;
                            MOT2_ROTAT = ON;
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        case 'h': 
                            STEP2_NUM = 10000000;
                            HSTEP2_NUM = 2*STEP2_NUM;
                            DIR2 = 0;
                            MOT2_HOME = ON;
                            MOT2_ROTAT = ON;
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        case'F':
                            STEP2_FREQ = NUMBER; // STEP FREQUENCY
                            T3CONbits.TON = 0;		// Disable Timer
                            PR3 = ((FCY/64)/2)/STEP2_FREQ;
                            T3CONbits.TON = 1;		// Enable Timer
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        case '+':
                            if (NUMBER == 0){
                                MRESPONSE[1] = 'R';
                                return;
                            }
                            STEP2_NUM = NUMBER;
                            HSTEP2_NUM = 2*STEP2_NUM;
                            DIR2 = 0;
                            MOT2_ROTAT = ON;
                            MRESPONSE[1] = 'A';
                            return;
                        case '-':
                            if (NUMBER == 0){
                                MRESPONSE[1] = 'R';
                                return;
                            }
                            STEP2_NUM = NUMBER;
                            HSTEP2_NUM = 2*STEP2_NUM;
                            DIR2 = 1;
                            MOT2_ROTAT = ON;
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        default:
                            MRESPONSE[1] = 'X'; // 'X' for wrong 
                            return;
                    }
                }
            // End of Case-2
                
            // Command for motor-3
            case '3':
                MRESPONSE[0] = '3';
                if (COMMAND[1] == 'Q') {
                    MOT3_ROTAT = OFF;
                    MOT3_HOME = OFF;
                    LED3 = OFF;
                    MRESPONSE[1] = 'Q'; // 'Q' for quitting 
                    return;
                }
                else if (MOT3_ROTAT == YES || MOT3_HOME == YES){
                    MRESPONSE[1] = 'B'; // 'B' for busy 
                    return;
                }
                else{
                    switch (COMMAND[1]){
                        case 'D':
                            DIS3 = 1;
                            MRESPONSE[1] = 'D'; // 'D' for disable 
                            return;
                        case 'E':
                            DIS3 = 0;
                            MRESPONSE[1] = 'E'; // 'E' for enable 
                            return;
                        case 'H':
                            if (POS3_CURRENT == 0){
                                MRESPONSE[1] = 'H';
                                return;
                            }
                            STEP3_NUM = 10000000;
                            HSTEP3_NUM = 2*STEP3_NUM;
                            DIR3 = 1;
                            MOT3_HOME = ON;
                            MOT3_ROTAT = ON;
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        case 'h':
                            STEP3_NUM = 10000000;
                            HSTEP3_NUM = 2*STEP3_NUM;
                            DIR3 = 0;
                            MOT3_HOME = ON;
                            MOT3_ROTAT = ON;
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        case 'I':
                            STEP3_NUM = 1000;
                            HSTEP3_NUM = 2*STEP3_NUM;
                            DIR3 = 0;
                            MOT3_ROTAT = ON;
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        case'F':
                            STEP3_FREQ = NUMBER; // STEP FREQUENCY
                            T4CONbits.TON = 0;		// Disable Timer
                            PR4 = ((FCY/64)/2)/STEP3_FREQ;
                            T4CONbits.TON = 1;		// Enable Timer
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        case '+':
                            if (NUMBER == 0){
                                MRESPONSE[1] = 'R';
                                return;
                            }
                            STEP3_NUM = NUMBER;
                            HSTEP3_NUM = 2*STEP3_NUM;
                            DIR3 = 0;
                            MOT3_ROTAT = ON;
                            MRESPONSE[1] = 'A';
                            return;
                        case '-':
                            if (NUMBER == 0){
                                MRESPONSE[1] = 'R';
                                return;
                            }
                            if (POS3_CURRENT == 0){
                                MRESPONSE[1] = 'H';
                                return;
                            }
                            STEP3_NUM = NUMBER;
                            HSTEP3_NUM = 2*STEP3_NUM;
                            DIR3 = 1;
                            MOT3_ROTAT = ON;
                            MRESPONSE[1] = 'A'; // 'A' for acknowledge 
                            return;
                        default:
                            MRESPONSE[1] = 'X'; // 'X' for wrong
                            return;
                    }
                }
            // End of Case-3   
            
            default:
                MRESPONSE[0] = 'M';
                MRESPONSE[1] = 'X'; // 'X' for wrong
                return;
        }
        MRESPONSE[0] = 'M';
        MRESPONSE[1] = 'X'; // 'X' for wrong
        return;
    }
}
