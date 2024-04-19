// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"


// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
#define TIMER_FREQ 38
#define Timer_A_REMAINING 2 * TIMER_FREQ
#define Timer_B_REMAINING 3 * TIMER_FREQ
#define Timer_C_REMAINING 5 * TIMER_FREQ
#define L1 0x01
#define L2 0x02
#define L3 0x04

struct Timer timerA = {FALSE, Timer_A_REMAINING};
struct Timer timerB = {FALSE, Timer_B_REMAINING};
struct Timer timerC = {FALSE, Timer_C_REMAINING};

int Led_Value; // Initializing value for input into LEDS_SET

// **** Declare function prototypes ****

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
    printf("Welcome to 1760640's lab6 part1 (timers).  Compiled on %s %s.\n", __TIME__, __DATE__);

    LEDS_INIT();

    while (1) {

        //poll timer A
        //react to timer A events
        //clear timer A event flag

        //checking if each respective timer event has been toggled and reacting with appropriate output

        if (timerB.event == TRUE) {
            printf("B ");
            timerB.event = FALSE; //Must reset each timer event after it's been changed to true
            Led_Value ^= L2;
            LEDS_SET(Led_Value);
        }

        if (timerA.event == TRUE) {
            printf("A ");
            timerA.event = FALSE; //Must reset each timer event after it's been changed to true
            Led_Value ^= L1;
            LEDS_SET(Led_Value);
        }

        if (timerC.event == TRUE) {
            printf("C ");
            timerC.event = FALSE; //Must reset each timer event after it's been changed to true
            Led_Value ^= L3;
            LEDS_SET(Led_Value);
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

    //when each of these timers remaining time reaches zero, we must change their events to TRUE

    timerB.timeRemaining--;
    if (timerB.timeRemaining == 0) {
        timerB.event = TRUE;
        timerB.timeRemaining = Timer_B_REMAINING; //We must reset their time remaining back to its original value  so it cycles appropriately 
    }

    timerA.timeRemaining--;
    if (timerA.timeRemaining == 0) {
        timerA.event = TRUE;
        timerA.timeRemaining = Timer_A_REMAINING; //We must reset their time remaining back to its original value  so it cycles appropriately 
    }

    timerC.timeRemaining--;
    if (timerC.timeRemaining == 0) {
        timerC.event = TRUE;
        timerC.timeRemaining = Timer_C_REMAINING; //We must reset their time remaining back to its original value  so it cycles appropriately 
    }


    //update timerA
    //if timerA has counted down,
    //generate timerA event
    //reset timerA




    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}