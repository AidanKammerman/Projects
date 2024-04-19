#include "BOARD.h"

/**
 * This enum{} lists all of the possible button events that could occur. Each event constants were
 * chosen so that multiple button events can be recorded in a single call to ButtonsCheckEvents().
 * 
 * All possible event flags will also fit into a char datatype.  This is to handle the rare situation
 * where two buttons change state simultaneously (or at least, within the frequency of the timer
 * interrupt).  So, a single char could indicate that button 1 was released at the same time that
 * while button 2 was pressed with (BUTTON_EVENT_1UP | BUTTON_EVENT_2DOWN)
 *
 */
typedef enum {
    BUTTON_EVENT_NONE = 0x00,
    BUTTON_EVENT_1UP = 0x01, //0000 0000 0000 0001
    BUTTON_EVENT_1DOWN = 0x02, //0000 0000 0000 0010
    BUTTON_EVENT_2UP = 0x04, //0000 0000 0000 0100
    BUTTON_EVENT_2DOWN = 0x08, //0000 0000 0000 1000
    BUTTON_EVENT_3UP = 0x10, //0000 0001 0000 0000
    BUTTON_EVENT_3DOWN = 0x20,
    BUTTON_EVENT_4UP = 0x40,
    BUTTON_EVENT_4DOWN = 0x80
} ButtonEventFlags;

/**
 * This function initializes the proper pins such that the buttons 1-4 may be used by modifying
 * the necessary bits in TRISD/TRISF. Only the bits necessary to enable the 1-4 buttons are
 * modified, so that this library does not interfere with other libraries.
 */
void ButtonsInit(void) {
    TRISD |= 0x00E0;
    TRISF |= 0x0002;
}

/**
 * ButtonsCheckEvents function checks the current button states and returns
 *  any events that have occured since its last
 * call.  This function should be called repeatedly in a Timer ISR, though it can
 * be called in main() during testing.
 *
 * In normal use, this function should only be used after ButtonsInit().
 * 
 * This function should assume that the buttons start in an off state with 
 * value 0. Therefore if no buttons are
 * pressed when ButtonsCheckEvents() is first called, 
 * BUTTONS_EVENT_NONE should be returned. 
 * 
 * @return  Each bit of the return value corresponds to one ButtonEvent flag,
 *          as described in Buttons.h.  If no events are detected, BUTTONS_EVENT_NONE is returned.
 * 
 * Note that more than one event can occur simultaneously, though this situation is rare.
 * To handle this, the output should be a bitwise OR of all applicable event flags. 
 * For example, if button 1 was released at the same time that button 2 was pressed,
 * this function should return (BUTTON_EVENT_1UP | BUTTON_EVENT_2DOWN) 
 * 
 */

#define Mask_B1_Down 0x1111
#define Mask_B2_Down 0x2222
#define Mask_B3_Down 0x4444
#define Mask_B4_Down 0x8888
#define Shift_DB 4

static uint16_t prev_val = 0;
static uint8_t prevButton_1_Event = BUTTON_EVENT_1UP;
static uint8_t prevButton_2_Event = BUTTON_EVENT_2UP;
static uint8_t prevButton_3_Event = BUTTON_EVENT_3UP;
static uint8_t prevButton_4_Event = BUTTON_EVENT_4UP;

uint8_t ButtonsCheckEvents(void) {

    uint8_t returnButtonEvent = BUTTON_EVENT_NONE;  //resetting returnButtonEvent so it can accurately check for additional input

    prev_val = (prev_val << Shift_DB) | BUTTON_STATES(); // Must Check to see if multiple buttons are pressed at the same time

    if ((prev_val & Mask_B1_Down) && !(prevButton_1_Event & BUTTON_EVENT_1DOWN)) {
        returnButtonEvent |= BUTTON_EVENT_1DOWN;
        prevButton_1_Event = returnButtonEvent;
    }
    if (!(prev_val & Mask_B1_Down) && (prevButton_1_Event & BUTTON_EVENT_1DOWN)) {
        returnButtonEvent |= BUTTON_EVENT_1UP;
        prevButton_1_Event = returnButtonEvent;
    }

    if ((prev_val & Mask_B2_Down) && !(prevButton_2_Event & BUTTON_EVENT_2DOWN)) {
        returnButtonEvent |= BUTTON_EVENT_2DOWN;
        prevButton_2_Event = returnButtonEvent;
    }
    if (!(prev_val & Mask_B2_Down) && (prevButton_2_Event & BUTTON_EVENT_2DOWN)) {
        returnButtonEvent |= BUTTON_EVENT_2UP;
        prevButton_2_Event = returnButtonEvent;
    }

    if ((prev_val & Mask_B3_Down) && !(prevButton_3_Event & BUTTON_EVENT_3DOWN)) {
        returnButtonEvent |= BUTTON_EVENT_3DOWN;
        prevButton_3_Event = returnButtonEvent;
    }
    if (!(prev_val & Mask_B3_Down) && (prevButton_3_Event & BUTTON_EVENT_3DOWN)) {
        returnButtonEvent |= BUTTON_EVENT_3UP;
        prevButton_3_Event = returnButtonEvent;
    }

    if ((prev_val & Mask_B4_Down) && !(prevButton_4_Event & BUTTON_EVENT_4DOWN)) {
        returnButtonEvent |= BUTTON_EVENT_4DOWN;
        prevButton_4_Event = returnButtonEvent;
    }
    if (!(prev_val & Mask_B4_Down) && (prevButton_4_Event & BUTTON_EVENT_4DOWN)) {
        returnButtonEvent |= BUTTON_EVENT_4UP;
        prevButton_4_Event = returnButtonEvent;
    }
    return returnButtonEvent;
}
