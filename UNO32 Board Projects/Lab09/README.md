Lab 9 README File
CSE 13E Spring 2021
Aidan Kammerman
1760640
6/6/2021

I had no partner for this lab. All the work that I am submitting is my own.

I would like you to grade this submission. The commit SHA that I turn in on canvas. I wrote all of this code myself.
I did not complete any of the extra credit portions for this lab. I did not collaborate with anyone but I did attend
a few of the lab sections to receive more clarification on a few things.

I spent the most time completing Agent.c. It functions mainly utilizing a state machine which changes states in accordance
with certain events being triggered. This allows the battleboats game to fluidly progress without getting stuck. AgentInit()
sets the current state to AGENT_STATE_START. The state remains constant until either Button 4 is pressed on the UNO32 or a 
challenge has been received by the UNO32. If Button 4 is pressed, the state will change to AGENT_STATE_CHALLENGING. If a 
challenge is received, the state will change to AGENT_STATE_ACCEPTING. From these next two states, a coinflip simulation will
be ran and verified to determine which side goes first. The side that attacks first will enter AGENT_STATE_ATTACKING while
the side that goes second enters AGENT_STATE_DEFENDING. The game can now progress with the state of each side swapping back and
forth with an intermediate state labelled AGENT_STATE_WAITING_TO_SEND. This state updates the number of turns and updates the 
GuessData with the next guess from the AI before changing the state to AGENT_STATE_ATTACKING. This cycle continues until 
FieldGetBoatStates() determines that all boats have been destroyed on one side or another. The state is then finally changed 
to AGENT_STATE_END_SCREEN, which determines which side has won and displays the appropriate message accordingly. It also displays
a message if cheating has been detected by the NegotiationVerify() Function.

The implementation of the state machine worked very well in the end. The creation of random numbers A and B also worked well. 
Figuring out where to return returnMessage did not work very well at first but I later realized that I had to have an additional
return returnMessage statement outside of the switch statement entirely which fixed my infinite looping problem. A testing strategy 
that worked well for me involved printing messages to the OLED display based on if certain BB EVENTS were triggered. This allowed me 
to determine which parts of my code were malfunctioning in a much easier way. I learned much more about the implementation of
state machines and their general functionality. I also learned how to debug parts of my code without having access to the UART IO
Output. I liked the final functionality of the battle boats game because it reminded me of my childhood when I used to play Hasbro's
version of battleship. I wouldn't change anything about this lab. Overall I am glad that I stuck with Agent.c long enough to finish it.  