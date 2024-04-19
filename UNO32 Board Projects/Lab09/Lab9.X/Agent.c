#include "Agent.h"
#include "Ascii.h"
#include "BOARD.h"
#include "BattleBoats.h"
#include "Buttons.h"
#include "CircularBuffer.h"
#include "Field.h"
#include "FieldOled.h"
#include "Message.h"
#include "Negotiation.h"
#include "Oled.h"
#include "OledDriver.h"
#include "Uart1.h"
#include "Math.h"
#include "stdio.h"

// make static variables

static AgentState CurrentState;
static int Turns;
static Field MyField = {};
static Field OpField = {};
static GuessData Guess = {};
static FieldOledTurn TurnDecider = FIELD_OLED_TURN_NONE;
static uint16_t A;
static uint16_t B;
static uint16_t hashA;
static uint16_t hashB;
char oled[100] = "";
static int ALL_BOATS_DESTROYED = 0;

/**
 * The Init() function for an Agent sets up everything necessary for an agent before the game
 * starts.  At a minimum, this requires:
 *   -setting the start state of the Agent SM.
 *   -setting turn counter to 0
 * If you are using any other persistent data in Agent SM, that should be reset as well.
 * 
 * It is not advised to call srand() inside of AgentInit.  
 *  */
void AgentInit(void) {
    Turns = 0;
    CurrentState = AGENT_STATE_START;
    A = (rand() & 0xFFFF);
    B = (rand() & 0xFFFF);
    hashA = NegotiationHash(A);
}

/**
 * AgentRun evolves the Agent state machine in response to an event.
 * 
 * @param  The most recently detected event
 * @return Message, a Message struct to send to the opponent. 
 * 
 * If the returned Message struct is a valid message
 * (that is, not of type MESSAGE_NONE), then it will be
 * passed to the transmission module and sent via UART.
 * This is handled at the top level! AgentRun is ONLY responsible 
 * for generating the Message struct, not for encoding or sending it.
 */
Message AgentRun(BB_Event event) {
    Message returnMessage = {MESSAGE_NONE, 0, 0, 0};

    if (event.type == BB_EVENT_RESET_BUTTON) {
        AgentInit();
        OledInit();
        OledClear(OLED_COLOR_BLACK);
        OledDrawString("Ready For a New Game?\nPress BTN4 to Begin.");
        OledUpdate();
    }

    if (event.type == BB_EVENT_ERROR) {
        returnMessage.type = MESSAGE_ERROR;
        return returnMessage;
    }

    switch (CurrentState) {
        case AGENT_STATE_START:
            if (event.type == BB_EVENT_START_BUTTON) {
                A = (rand() & 0xFFFF);
                hashA = NegotiationHash(A);
                CurrentState = AGENT_STATE_CHALLENGING;
                returnMessage.type = MESSAGE_CHA;
                returnMessage.param0 = hashA;
                FieldInit(&MyField, &OpField);
                FieldAIPlaceAllBoats(&MyField);
                event.type = BB_EVENT_NO_EVENT;
                OledClear(OLED_COLOR_BLACK);
                sprintf(oled, "CHALLENGING\n %d = A\n %d = hash_a", A, hashA);
                OledDrawString(oled);
                OledUpdate();
                return returnMessage;
            } else if (event.type == BB_EVENT_CHA_RECEIVED) {
                hashA = event.param0;
                B = (rand() & 0xFFFF);
                returnMessage.type = MESSAGE_ACC;
                returnMessage.param0 = B;
                FieldInit(&MyField, &OpField);
                FieldAIPlaceAllBoats(&MyField);
                CurrentState = AGENT_STATE_ACCEPTING;
                OledClear(OLED_COLOR_BLACK);
                sprintf(oled, "ACCEPTING\n %d = hash_a\n %d = B", hashA, B);
                OledDrawString(oled);
                OledUpdate();
                return returnMessage;
            }
            break;
        case AGENT_STATE_CHALLENGING:
            if (event.type == BB_EVENT_ACC_RECEIVED) {
                B = event.param0;
                returnMessage.type = MESSAGE_REV;
                returnMessage.param0 = A;
                if (NegotiateCoinFlip(A, B) == HEADS) {
                    CurrentState = AGENT_STATE_WAITING_TO_SEND;
                } else if (NegotiateCoinFlip(A, B) == TAILS) {
                    CurrentState = AGENT_STATE_DEFENDING;
                }
                FieldOledDrawScreen(&MyField, &OpField, TurnDecider, Turns);
                return returnMessage;
            }
            break;
        case AGENT_STATE_ACCEPTING:
            if (event.type == BB_EVENT_REV_RECEIVED) {
                A = event.param0;
                if (NegotiationVerify(A, hashA) == FALSE) {
                    CurrentState = AGENT_STATE_END_SCREEN;
                } else if (NegotiateCoinFlip(A, B) == TAILS) {
                    Guess = FieldAIDecideGuess(&OpField);
                    returnMessage.type = MESSAGE_SHO;
                    returnMessage.param0 = Guess.row;
                    returnMessage.param1 = Guess.col;
                    CurrentState = AGENT_STATE_ATTACKING;
                    FieldOledDrawScreen(&MyField, &OpField, TurnDecider, Turns);
                    return returnMessage;
                } else if (NegotiateCoinFlip(A, B) == HEADS) {
                    CurrentState = AGENT_STATE_DEFENDING;
                    FieldOledDrawScreen(&MyField, &OpField, TurnDecider, Turns);
                }
            }
            break;
        case AGENT_STATE_ATTACKING:
            if (event.type == BB_EVENT_RES_RECEIVED) {
                Guess.row = event.param0;
                Guess.col = event.param1;
                Guess.result = event.param2;
                FieldUpdateKnowledge(&OpField, &Guess);
                if (FieldGetBoatStates(&OpField) == ALL_BOATS_DESTROYED) {
                    CurrentState = AGENT_STATE_END_SCREEN;
                } else {
                    CurrentState = AGENT_STATE_DEFENDING;
                    TurnDecider = FIELD_OLED_TURN_THEIRS;
                }
                FieldOledDrawScreen(&MyField, &OpField, TurnDecider, Turns);
            }
            break;
        case AGENT_STATE_DEFENDING:
            if (event.type == BB_EVENT_SHO_RECEIVED) {
                Guess.row = event.param0;
                Guess.col = event.param1;
                TurnDecider = FIELD_OLED_TURN_MINE;
                FieldRegisterEnemyAttack(&MyField, &Guess);
                returnMessage.type = MESSAGE_RES;
                returnMessage.param0 = Guess.row;
                returnMessage.param1 = Guess.col;
                returnMessage.param2 = Guess.result;
                if (FieldGetBoatStates(&MyField) == ALL_BOATS_DESTROYED) {
                    CurrentState = AGENT_STATE_END_SCREEN;
                } else {
                    CurrentState = AGENT_STATE_WAITING_TO_SEND;
                    FieldOledDrawScreen(&MyField, &OpField, TurnDecider, Turns);
                    return returnMessage;
                }
            }
            break;
        case AGENT_STATE_WAITING_TO_SEND:
            if (event.type == BB_EVENT_MESSAGE_SENT) {
                Turns++;
                Guess = FieldAIDecideGuess(&OpField);
                returnMessage.type = MESSAGE_SHO;
                returnMessage.param0 = Guess.row;
                returnMessage.param1 = Guess.col;
                CurrentState = AGENT_STATE_ATTACKING;
                return returnMessage;
            }

            break;
        case AGENT_STATE_END_SCREEN:

            if ((NegotiationVerify(A, hashA) == FALSE)) {
                OledClear(OLED_COLOR_BLACK);
                OledDrawString("NO CHEATING ALLOWED!");
                OledUpdate();
            } else if (FieldGetBoatStates(&MyField) == ALL_BOATS_DESTROYED) {
                OledClear(OLED_COLOR_BLACK);
                OledDrawString("I Am Defeated");
                OledUpdate();
            } else if (FieldGetBoatStates(&OpField) == ALL_BOATS_DESTROYED) {
                OledClear(OLED_COLOR_BLACK);
                OledDrawString("Victory Is Mine!");
                OledUpdate();
            }
            break;
    }
    return returnMessage;
}

/** * 
 * @return Returns the current state that AgentGetState is in.  
 * 
 * This function is very useful for testing AgentRun.
 */
AgentState AgentGetState(void) {
    return CurrentState;
}

/** * 
 * @param Force the agent into the state given by AgentState
 * 
 * This function is very useful for testing AgentRun.
 */
void AgentSetState(AgentState newState) {
    CurrentState = newState;
}
