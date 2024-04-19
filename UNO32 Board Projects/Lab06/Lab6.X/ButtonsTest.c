// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****
char* down = "DOWN";
char* up = "  UP";
char* spot1 = "----";
char* spot2 = "----";
char* spot3 = "----";
char* spot4 = "----";

int ButtonValue;
// **** Declare function prototypes ****

int main(void) {
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 2; // 1:64 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to 1760640's lab6 part4 (ButtonsTest).  Compiled on %s %s.\n", __TIME__, __DATE__);


    printf("Please press some buttons!\n");

    while (1) {

        if (ButtonValue != BUTTON_EVENT_NONE) {

            spot1 = "----";
            spot2 = "----";
            spot3 = "----";
            spot4 = "----";

            //checking which buttons are pushed in order to modify printed output

            if ((ButtonValue & BUTTON_EVENT_1DOWN) == BUTTON_EVENT_1DOWN) {
                spot1 = down;
            }
            if ((ButtonValue & BUTTON_EVENT_2DOWN) == BUTTON_EVENT_2DOWN) {
                spot2 = down;
            }
            if ((ButtonValue & BUTTON_EVENT_3DOWN) == BUTTON_EVENT_3DOWN) {
                spot3 = down;
            }
            if ((ButtonValue & BUTTON_EVENT_4DOWN) == BUTTON_EVENT_4DOWN) {
                spot4 = down;
            }
            if ((ButtonValue & BUTTON_EVENT_1UP) == BUTTON_EVENT_1UP) {
                spot1 = up;
            }
            if ((ButtonValue & BUTTON_EVENT_2UP) == BUTTON_EVENT_2UP) {
                spot2 = up;
            }
            if ((ButtonValue & BUTTON_EVENT_3UP) == BUTTON_EVENT_3UP) {
                spot3 = up;
            }
            if ((ButtonValue & BUTTON_EVENT_4UP) == BUTTON_EVENT_4UP) {
                spot4 = up;
            }

            printf("EVENT:  4:%s 3:%s 2:%s 1:%s\n", spot4, spot3, spot2, spot1);

            ButtonValue = BUTTON_EVENT_NONE; //resetting temporary value ButtonValue back to BUTTON_EVENT_NONE so it won't spam output
        }
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);

}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void) {
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    ButtonValue = ButtonsCheckEvents(); //ISR repeatedly calls ButtonsCheckEvents() to check for any changes in button states.
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}