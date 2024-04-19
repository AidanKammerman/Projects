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
int ButtonValue;
int Led_Value = 0b00000000;
int Button1 = 0b00000011;
int Button2 = 0b00001100;
int Button3 = 0b00110000;
int Button4 = 0b11000000;
int SWITCH_STATE_SW0 = 0x0;

// **** Define global, module-level, or external variables here ****


// **** Declare function prototypes ****

int main(void) {

    LEDS_INIT();
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
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
    printf("Welcome to 1760640's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);

    while (TRUE) {

        if (ButtonValue != BUTTON_EVENT_NONE) {

            //If switch 1 is down, then each Button DOWN event toggles the appropriate LEDs
            if ((SWITCH_STATES() & SWITCH_STATE_SW1) == SWITCH_STATE_SW0) {
                if ((ButtonValue & BUTTON_EVENT_1DOWN) == BUTTON_EVENT_1DOWN) {
                    Led_Value = (Led_Value ^ Button1);
                }
                if ((ButtonValue & BUTTON_EVENT_2DOWN) == BUTTON_EVENT_2DOWN) {
                    Led_Value = (Led_Value ^ Button2);
                }
                if ((ButtonValue & BUTTON_EVENT_3DOWN) == BUTTON_EVENT_3DOWN) {
                    Led_Value = (Led_Value ^ Button3);
                }
                if ((ButtonValue & BUTTON_EVENT_4DOWN) == BUTTON_EVENT_4DOWN) {
                    Led_Value = (Led_Value ^ Button4);
                }
            }//If switch 1 is up, then each Button UP event toggles the appropriate LEDs
            else if ((SWITCH_STATES() & SWITCH_STATE_SW1) == SWITCH_STATE_SW1) {
                if ((ButtonValue & BUTTON_EVENT_1UP) == BUTTON_EVENT_1UP) {
                    Led_Value = (Led_Value ^ Button1);
                }
                if ((ButtonValue & BUTTON_EVENT_2UP) == BUTTON_EVENT_2UP) {
                    Led_Value = (Led_Value ^ Button2);
                }
                if ((ButtonValue & BUTTON_EVENT_3UP) == BUTTON_EVENT_3UP) {
                    Led_Value = (Led_Value ^ Button3);
                }
                if ((ButtonValue & BUTTON_EVENT_4UP) == BUTTON_EVENT_4UP) {
                    Led_Value = (Led_Value ^ Button4);
                }
            }

            LEDS_SET(Led_Value);


            ButtonValue = BUTTON_EVENT_NONE;
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