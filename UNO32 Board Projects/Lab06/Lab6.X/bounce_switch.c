
// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>



//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
struct Timer timer1 = {FALSE, 1};
int Led_Value = 0b00000001; // Initializing value for input into LEDS_SET
int Led_distance = 0; //Initializing value to help determine distance from left or right LED

// **** Declare function prototypes ****

#define shift 1
#define RIGHT 0
#define LEFT 1
#define L1 0x01
#define L2 0x02
#define L3 0x04
#define L4 0x08
#define L5 0x10
#define L6 0x20
#define L7 0x40
#define L8 0x80

int main(void) {
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
    printf("Welcome to 1760640's lab6 part2 (bounce_switch).  Compiled on %s %s.\n", __TIME__, __DATE__);

    LEDS_INIT();

    while (1) {
        //poll timer events and react if any occur

        if (timer1.event == TRUE) {

            if (Led_Value == L8) {
                Led_distance = RIGHT;
            }
            if (Led_Value == L1) {
                Led_distance = LEFT;
            }

            LEDS_SET(Led_Value);

            if (Led_distance == LEFT) { //checking if the LED has gone to its furthest left position so it can reverse direction
                Led_Value = Led_Value << shift;
            }
            if (Led_distance == RIGHT) { //checking if the LED has gone to its furthest right position so it can reverse direction
                Led_Value = Led_Value >> shift;
            }


            timer1.event = FALSE;
        }

    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void) {
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;


    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    timer1.timeRemaining -= 1;
    if (timer1.timeRemaining < 0) {
        if (SWITCH_STATES() == 0b0000) { //checking to see how much additional time must be added to timeRemaining depending on switch states
            timer1.timeRemaining = 1;
        }
        if (SWITCH_STATES() == 0b0001) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b0010) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b0011) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b0100) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b0101) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b0110) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b0111) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b1000) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b1001) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b1010) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b1011) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b1100) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b1101) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b1110) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        if (SWITCH_STATES() == 0b1111) {
            timer1.timeRemaining = 1 + SWITCH_STATES();
        }
        timer1.event = TRUE;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}