/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_CUSTOM_H
    #define	XC_CUSTOM_H
    #include <xc.h> // include processor files - each processor file is guarded
    #include <p33FJ128GP802.h>

//  Define custom functions
    void U1TX_SENDCHR(unsigned char);
    void U1TX_SENDSTR(unsigned char *);
    void U2TX_SENDCHR(unsigned char);
    void U2TX_SENDSTR(unsigned char *);
    
// Define commonly used symbols here
    #define FIRST_CHAR '<'  // Command's first character
    #define LAST_CHAR '>'   // Command's last character
    #define YES 1
    #define NO 0
    #define ON 1
    #define OFF 0
// Declare global variables
    extern unsigned char COMMAND[16];   // Command array
    extern unsigned char SLAVE_COMMAND[16]; // Command array for slave
    extern unsigned int COMM_IND;       // Command array index
    extern unsigned int COMM_LEN;       // Command length
    extern unsigned int COMM_REC;       // Command received?
    extern unsigned char SRESPONSE[3];   // Slave Response for the commands, 3rd char is always '\n'
    extern unsigned char MRESPONSE[3];   // Master Response for the commands, 3rd char is always '\n'
    
    extern unsigned int NUMBER_MOTO;    // Motor number
    extern unsigned int FUNCTION_MOTO;  // Function of drivers
    extern unsigned long int NUMBER;         // Numerical value
    
    extern unsigned int MOT1_ROTAT; // Motor-1 rotation?
    extern unsigned int MOT1_HOME;  // Motor-1 homing?
    extern unsigned long int STEP1_NUM;  // Number of steps left
    extern unsigned long int HSTEP1_NUM; // Number of toggles (half-steps)  = 2* Number of steps
    extern unsigned int STEP1_FREQ; // Step frequency
    extern unsigned long int POS1_CURRENT; // Current value - 1
   
    extern unsigned int MOT2_ROTAT; // Motor-2 rotation?
    extern unsigned int MOT2_HOME;  // Motor-2 homing?
    extern unsigned long int STEP2_NUM;  // Number of steps left
    extern unsigned long int HSTEP2_NUM; // Number of toggles (half-steps) = 2* Number of steps
    extern unsigned int STEP2_FREQ; // Step frequency
    extern unsigned long int POS2_CURRENT; // Current value - 2

    
    extern unsigned int MOT3_ROTAT; // Motor-3 rotation?
    extern unsigned int MOT3_HOME;  // Motor-3 homing?
    extern unsigned long int STEP3_NUM;  // Number of steps left
    extern unsigned long int HSTEP3_NUM; // Number of toggles (half-steps) = 2* Number of steps
    extern unsigned int STEP3_FREQ; // Step frequency
    extern unsigned long int POS3_CURRENT; // Current value - 3
    #endif	/* XC_HEADER_TEMPLATE_H */

