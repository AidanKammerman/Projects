// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CSE13E Support Library
#include "BOARD.h"
#include "Ascii.h"
#include "Buttons.h"
#include "Leds.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>



// **** Set any macros or preprocessor directives here ****



// **** Set any local typedefs here ****

typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING //All constants must be declared as constants using either #define, enum or const

} OvenState;

typedef enum {
    BAKE, TOAST, BROIL
} OvenMode;

typedef enum {
    TIME, TEMP
} OvenSelector;

typedef struct {
    OvenState state;
    OvenMode mode;
    OvenSelector select;
    int16_t RemainingTime;
    int16_t temperature;
    int16_t press_time;
    int16_t start_time;
} OvenData;

struct AdcResult {
    uint8_t event;
    uint16_t voltage;
};

struct ButtonsResult {
    uint8_t event;
    uint8_t buttons;
};

struct TimerTick {
    uint8_t event;
};

struct Button3Event {
    uint8_t event;
};

// **** Declare any datatypes here ****

int16_t timeRemaining;
int16_t temp;
int16_t time_start;
int16_t time_press;

char time_arrow = '>';
char temp_arrow = ' ';
int mins = 0;
int secs = 0;
char secs_display[100] = "";
char oled[100] = "";
int partial_second = 0;
int button3timer = 0;
int freetime = 0;
int freetime_whole = 0;
int temptime = 0;
int starttime = 0;
int totalcooktime = 0;

OvenData Oven = {SETUP, BAKE, TIME, 1, 350, 0, 50}; //declaring necessary instances of structures for this lab

struct AdcResult Adc_Result = {FALSE, 0};

struct ButtonsResult Buttons_Result = {FALSE, 0};

struct TimerTick second = {FALSE};

struct Button3Event Button3event = {FALSE};

// **** Define any module-level, global, or external variables here ****

// **** Put any helper functions here ****
#define LONG_PRESS 5
#define MIN_TIME 1
#define MIN_TEMP 300
#define WHOLE_SEC 5

#define LED0 0b00000000         //defining all the different possibilities necessary for the LEDS in this lab
#define LED1 0b10000000
#define LED2 0b11000000
#define LED3 0b11100000
#define LED4 0b11110000
#define LED5 0b11111000
#define LED6 0b11111100
#define LED7 0b11111110
#define LED8 0b11111111

/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData) {
    //update OLED

    OledClear();

    mins = Oven.RemainingTime / 60; //setting up correct format for time displayed on the Toaster Oven Interface]
    secs = Oven.RemainingTime % 60;

    sprintf(secs_display, "%d", secs);

    if (secs < 10) {
        sprintf(secs_display, "0%d", secs);
    }


    if (Oven.select == TIME) { //Changing arrow display to match which the selected TIME or TEMP
        time_arrow = '>';
        temp_arrow = ' ';
    } else if (Oven.select == TEMP) {
        time_arrow = ' ';
        temp_arrow = '>';
    }



    if (Oven.state == SETUP || Oven.state == RESET_PENDING || Oven.state == SELECTOR_CHANGE_PENDING) {
        if (Oven.mode == BAKE) {
            sprintf(oled, "|%s%s%s%s%s| MODE: BAKE\n|     | %cTIME: %d:%s\n|-----| %cTEMP: %d\n|%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, time_arrow, mins, secs_display, temp_arrow, Oven.temperature, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
        } else if (Oven.mode == TOAST) {
            sprintf(oled, "|%s%s%s%s%s| MODE: TOAST\n|     |  TIME: %d:%s\n|-----| \n|%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, mins, secs_display, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
        } else if (Oven.mode == BROIL) {
            sprintf(oled, "|%s%s%s%s%s| MODE: BROIL\n|     |  TIME: %d:%s\n|-----|  TEMP: 500\n|%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, mins, secs_display, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
        }
        OledDrawString(oled);
        OledUpdate();
    } else if (Oven.state == COOKING) {
        if (Oven.mode == BAKE) {
            sprintf(oled, "|%s%s%s%s%s| MODE: BAKE\n|     |  TIME: %d:%s\n|-----|  TEMP: %d\n|%s%s%s%s%s|", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, mins, secs_display, Oven.temperature, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
        } else if (Oven.mode == TOAST) {
            sprintf(oled, "|%s%s%s%s%s| MODE: TOAST\n|     |  TIME: %d:%s\n|-----| \n|%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, mins, secs_display, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
        } else if (Oven.mode == BROIL) {
            sprintf(oled, "|%s%s%s%s%s| MODE: BROIL\n|     |  TIME: %d:%s\n|-----|  TEMP: 500\n|%s%s%s%s%s|", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, mins, secs_display, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
        }
        OledDrawString(oled);
        OledUpdate();
    }
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void) {
    //write your SM logic here.

    switch (Oven.state) {
        case SETUP:

            LEDS_SET(LED0); // resetting LED Display if the Cooking is cancelled early

            if (Buttons_Result.buttons == BUTTON_EVENT_3DOWN) {
                temptime = freetime;
                do {

                } while (Buttons_Result.buttons != BUTTON_EVENT_3UP);

                if ((freetime - temptime) > LONG_PRESS) { //checking to see how long Button 3 is held down for 

                    if (Oven.select == TIME) {
                        Oven.select = TEMP;
                    } else if (Oven.select == TEMP) {
                        Oven.select = TIME;
                    }
                } else if (Oven.mode == BAKE) {
                    Oven.mode = TOAST;
                } else if (Oven.mode == TOAST) {
                    Oven.mode = BROIL;
                } else if (Oven.mode == BROIL) {
                    Oven.mode = BAKE;
                    Oven.select = TIME;
                }
            }

            if (Adc_Result.event == TRUE) {
                if (Oven.mode == BAKE) { //if in BAKE mode, we must determine which variable is selected in order to change it accordingly
                    if (Oven.select == TIME) {
                        Oven.RemainingTime = 1 + (AdcRead() >> 2);
                    } else if (Oven.select == TEMP) {
                        Oven.temperature = 300 + (AdcRead() >> 2);
                    }
                } else {
                    Oven.RemainingTime = 1 + (AdcRead() >> 2);
                }
            }

            if (Buttons_Result.buttons == BUTTON_EVENT_4DOWN) { //changing state to COOKING once Button 4 is pressed down
                starttime = freetime_whole;
                totalcooktime = Oven.RemainingTime;
                Oven.state = COOKING;
            }
            break;
        case SELECTOR_CHANGE_PENDING:
            break;
        case COOKING:

            partial_second = 0;

            if (second.event == TRUE) { //Every second that passes, we must subtract from the Remaining time
                Oven.RemainingTime--;
                if (Oven.RemainingTime <= 0) {
                    Oven.state = SETUP;
                    Oven.RemainingTime = totalcooktime;
                    LEDS_SET(LED0);
                }
            }

            if (Buttons_Result.buttons == BUTTON_EVENT_4DOWN) { //Checking to see how long button 4 is held down to determine if cooking is ended early
                temptime = freetime;
                do {

                } while (Buttons_Result.buttons != BUTTON_EVENT_4UP);

                if ((freetime - temptime) > LONG_PRESS) {
                    Oven.state = SETUP;
                    LEDS_SET(LED0);
                    Oven.RemainingTime = totalcooktime;
                }
            }

            if ((freetime_whole - starttime) >= (totalcooktime)) { //Logic for determining which LEDS to toggle based on the remaining time before completion
                LEDS_SET(LED0);
            } else if ((freetime_whole - starttime) >= 7 * (totalcooktime / 8)) {
                LEDS_SET(LED1);
            } else if ((freetime_whole - starttime) >= 6 * (totalcooktime / 8)) {
                LEDS_SET(LED2);
            } else if ((freetime_whole - starttime) >= 5 * (totalcooktime / 8)) {
                LEDS_SET(LED3);
            } else if ((freetime_whole - starttime) >= 4 * (totalcooktime / 8)) {
                LEDS_SET(LED4);
            } else if ((freetime_whole - starttime) >= 3 * (totalcooktime / 8)) {
                LEDS_SET(LED5);
            } else if ((freetime_whole - starttime) >= 2 * (totalcooktime / 8)) {
                LEDS_SET(LED6);
            } else if ((freetime_whole - starttime) >= 1 * (totalcooktime / 8)) {
                LEDS_SET(LED7);
            } else {
                LEDS_SET(LED8);
            }

            break;
        case RESET_PENDING:
            break;
    }
}

int main() {
    BOARD_Init(); //Must initialize all the necessary .h files
    AdcInit();
    OledInit();
    ButtonsInit();
    LEDS_INIT();

    //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>

    printf("Welcome to 1760640's Lab07 (Toaster Oven).  Compiled on %s %s.\n", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here

    updateOvenOLED(Oven); //Updating Oven one time outside of main loop to keep the process as quick as possible

    while (1) {
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()
        // clear event flags

        if (Oven.state != COOKING) { //If in cooking mode, the ADC should have no effect on the display
            if (Adc_Result.event == TRUE) {
                runOvenSM();
                Adc_Result.event = FALSE; //must update the event flag after the state machine has been ran
                updateOvenOLED(Oven);
            }
        }

        if (Buttons_Result.buttons != BUTTON_EVENT_NONE) {//if a button is pressed, we must run the state machine and update the event flag 
            runOvenSM();
            Buttons_Result.buttons = BUTTON_EVENT_NONE;
            updateOvenOLED(Oven);
        }

        if (second.event == TRUE) {
            runOvenSM();
            second.event = FALSE; //must update the event flag after the state machine has been ran
            updateOvenOLED(Oven);
        }


    };
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;
    freetime++;
    partial_second++;
    if (partial_second == WHOLE_SEC) { //After this timer has looped 5 times, we know that one second has passed
        partial_second = 0;
        second.event = TRUE;
    }
    if (freetime % 5 == 0) {
        freetime_whole++; //every 5 cycles of this timer, a whole second must be added to freetime_whole.
    }

    //add event-checking code here
}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;


    if (AdcChanged() == TRUE) {
        Adc_Result.event = TRUE; //toggling event flag if the Adc reading has changed
    }


    Buttons_Result.buttons = ButtonsCheckEvents(); //continuously updating Buttons_Result.buttons so we do not miss any potential input

    //add event-checking code here
}