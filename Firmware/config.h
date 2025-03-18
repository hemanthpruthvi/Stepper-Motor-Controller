/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */ 
#ifndef XC_CONFIG_H
    #define	XC_CONFIG_H
    #include <xc.h> // include processor files - each processor file is guarded
    #include <p33FJ128GP802.h>

// Define required parameters
    // Internal oscillator
    #define FOSC (80000000) // Oscillator frequency (approx.)(To be set)
    #define FCY (FOSC/2)    // Peripheral clock frequency (To be set
    // Timers
    #define TIMER_VAL(FREQ) ((FCY/64)/2)/FREQ) // To be given by user
    // UARTs
    #define BAUDRATE1 (115200)
    #define WAIT_TX1 (FCY/BAUDRATE1)
    #define BRGVAL1 (((FCY/BAUDRATE1)/16)-1) 
    #define BAUDRATE2 (115200)
    #define WAIT_TX2 (FCY/BAUDRATE2)
    #define BRGVAL2 (((FCY/BAUDRATE2)/16)-1) 
    // LEDs
    #define LED1 LATAbits.LATA0
    #define LED2 LATAbits.LATA1
    #define LED3 LATAbits.LATA2
    // Motor-1 controls
    #define STEP1 LATBbits.LATB9
    #define DIR1 LATBbits.LATB8
    #define DIS1 LATBbits.LATB6 
    // Motor-2 controls
    #define STEP2 LATBbits.LATB13
    #define DIR2 LATBbits.LATB12
    #define DIS2 LATBbits.LATB11
    // Motor-3 controls
    #define STEP3 LATBbits.LATB4
    #define DIR3 LATAbits.LATA3
    #define DIS3 LATAbits.LATA4

// Define initialization functions for modules
    // Initialize Oscillator
    void INIT_OSCLI(void);    
    // Initialize timers
    void INIT_TIMR2(void);    
    void INIT_TIMR3(void);
    void INIT_TIMR4(void);
    // Initialize UARTs
    void INIT_UART1(void);
    void INIT_UART2(void);
    // Initialize I/O pins
    void INIT_INOUT(void);
    // Initialize External interrupts
    void INIT_INTRR(void);
    
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
    extern unsigned char SRESPONSE[4];   // Slave Response for the commands, 3rd char is always '\n'
    extern unsigned char MRESPONSE[4];   // Master Response for the commands, 3rd char is always '\n'
    
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
#endif	/* XC_CONFIG_H */